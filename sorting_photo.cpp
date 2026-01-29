#include "sorting_photo.h"
#include "getting_exifdata.h"
#include <QDirIterator>
#include <QDir>
#include <set>
#include <QDateTime>
#include <algorithm>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

sorting_photo::sorting_photo(QObject *parent) : QObject(parent) {
    exif_date = new getting_exifdata(this);
}

void sorting_photo::setPaused(bool paused) {
    m_isPaused = paused;
    if (!paused) m_pauseCondition.wakeAll();
}

void sorting_photo::stop() {
    m_isStopped = true;
    m_isPaused = false;
    m_pauseCondition.wakeAll();
}

void sorting_photo::sort_photo(QString input_path, QString output_path) {
    int totalFiles = 0;
    // Подсчет общего количества файлов для инициализации ProgressBar
    QDirIterator count_it(input_path,
                          QStringList() << "*.png" << "*.jpg" << "*.jpeg",
                          QDir::Files,
                          QDirIterator::Subdirectories);
    while (count_it.hasNext()) {
        count_it.next();
        totalFiles++;
    }

    emit maxProgressChanged(totalFiles);
    emit logMessage("INFO: началась сортировка фотографий");

    QDirIterator input_catalog(input_path,
                               QStringList() << "*.png" << "*.jpg" << "*.jpeg",
                               QDir::Files,
                               QDirIterator::Subdirectories);
    QDir output_catalog;
    std::set<QString> date_dirs; //Хранение годов, для которых уже созданы каталоги
    QString itemPath, outp_path, year;
    QDateTime date;
    int currentProgress = 0;

    while (input_catalog.hasNext()) {
        // Механизм управления состоянием потока:
        // 1. Сначала блокируемся на паузе (wait), если m_isPaused == true.
        //    Это позволяет потоку "уснуть" и не потреблять ресурсы процессора.
        // 2. После пробуждения или если паузы не было, проверяем m_isStopped.
        //    Такой порядок гарантирует, что если пользователь нажал "Прервать полностью" во время паузы,
        //    поток корректно проснется (через wakeAll) и сразу завершит работу,
        //    не выполняя следующую итерацию копирования.
        m_pauseMutex.lock();
        if(m_isPaused) emit logMessage("INFO: Сортировка приостановлена. Для продолжения нажмите \"Продолжить\"");
        while (m_isPaused) {
            m_pauseCondition.wait(&m_pauseMutex);
        }
        m_pauseMutex.unlock();

        if (m_isStopped) {
            emit logMessage("INFO: Сортировка полностью прервана.");
            break;
        }

        itemPath = input_catalog.next();
        date = exif_date->get_exif_date(itemPath);
        year = QString::number(date.date().year());
        outp_path = output_path + "/" + year + "/" + date.toString("dd.MM.yyyy HH-mm-ss") + "." + input_catalog.fileInfo().suffix();

        //Проверяем, создавали ли мы уже папку для этого года, чтобы не вызывать mkpath лишний раз
        if (!date.isNull() and !date_dirs.count(year)) {
            date_dirs.insert(year);
            if (output_catalog.mkpath(output_path + "/" + year)) {
                emit logMessage("INFO: Папки успешно созданы: " + output_path + "/" + year);
            } else {
                emit logMessage("WARN: Не удалось создать путь: " + output_path + "/" + year);
            }
        }

        int cnt = 1;
        //Запускаем цикл для нумерации дубликатов
        while(QFile::exists(outp_path)) {
            outp_path = output_path + "/" + year + "/" + date.toString("dd.MM.yyyy HH-mm-ss") + " (" + QString::number(cnt)+ ")" + "." + input_catalog.fileInfo().suffix();
            cnt++;
            if (cnt == 100) break;
            emit logMessage("WARN: Ошибка при копировании (возможно дубликат): " + outp_path);
        }
        if (QFile::copy(itemPath, outp_path)) {
            emit logMessage("INFO: Файл успешно скопирован и переименован: " + outp_path);
        } else {
            emit logMessage("ERROR: Не удалось скопировать файл (проверьте место на диске или права): " + outp_path);
        }

        currentProgress++;
        emit progressChanged(currentProgress);
    }

    emit logMessage("INFO: сортировка фотографий окончена");
    emit finished();
}
