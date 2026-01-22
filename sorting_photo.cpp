#include "sorting_photo.h"
#include "getting_exifdata.h"
#include <QDirIterator>
#include <QDir>
#include <vector>
#include <QDateTime>
#include <algorithm>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

sorting_photo::sorting_photo(QObject *parent) : QObject(parent) {}

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
    QDirIterator count_it(input_path,
                          QStringList() << "*.png" << "*.jpg" << "*.jpeg",
                          QDir::Files,
                          QDirIterator::Subdirectories);
    while (count_it.hasNext()) {
        count_it.next();
        totalFiles++;
    }

    emit maxProgressChanged(totalFiles); // Теперь максимум верный
    emit logMessage("INFO: началась сортировка фотографий");

    QDirIterator input_catalog(input_path,
                               QStringList() << "*.png" << "*.jpg" << "*.jpeg",
                               QDir::Files,
                               QDirIterator::Subdirectories);
    QDir output_catalog;
    std::vector<QString> date_dirs;
    QString itemPath, outp_path, year;
    QDateTime date;
    int currentProgress = 0;

    while (input_catalog.hasNext()) {
        if (m_isStopped) break;
        m_pauseMutex.lock();
        while (m_isPaused) {
            m_pauseCondition.wait(&m_pauseMutex);
        }
        m_pauseMutex.unlock();

        itemPath = input_catalog.next();
        date = exif_date->get_exif_date(itemPath);
        year = QString::number(date.date().year());
        outp_path = output_path + "/" + year + "/" + date.toString("dd.MM.yyyy HH-mm-ss") + "." + input_catalog.fileInfo().suffix();
        if (!date.isNull() and std::find(date_dirs.begin(), date_dirs.end(), year) != date_dirs.end()) {
            if (QFile::copy(itemPath, outp_path)) {
                emit logMessage("INFO: Файл успешно скопирован и переименован: " + outp_path);
            } else {
                emit logMessage("WARN: Ошибка при копировании (возможно дубликат): " + itemPath);
            }
        }
        else if (!date.isNull() and std::find(date_dirs.begin(), date_dirs.end(), year) == date_dirs.end()) {
            date_dirs.push_back(year);
            if (output_catalog.mkpath(output_path + "/" + year)) {
                emit logMessage("INFO: Папки успешно созданы: " + output_path + "/" + year);
                if (QFile::copy(itemPath, outp_path)) {
                    emit logMessage("INFO: Файл успешно скопирован и переименован: " + outp_path);
                } else {
                    emit logMessage("WARN: Ошибка при копировании (возможно дубликат): " + itemPath);
                }
            } else {
                emit logMessage("WARN: Не удалось создать путь: " + output_path + "/" + year);
            }
        }
        currentProgress++;
        emit progressChanged(currentProgress);
    }

    emit logMessage("INFO: сортировка фотографий окончена");
    emit finished();
}
