#ifndef SORTING_PHOTO_H
#define SORTING_PHOTO_H

#include "getting_exifdata.h"
#include <QObject>
#include <QWaitCondition>
#include <atomic>
#include <QMutex>
/**
 * @brief Класс sorting_photo создает объект сортировки. Используется в отдельном потоке.
 */
class sorting_photo : public QObject
{
    Q_OBJECT
public:
    explicit sorting_photo(QObject *parent = nullptr);
    /**
     * @brief setPaused Устанавливает флаг паузы для сортировки
     * @param paused Значение флага
     */
    void setPaused(bool paused);
    /**
     * @brief stop Устанавливает флаг полной остановки на true
     */
    void stop();

public slots:
    /**
     * @brief sort_photo Запускает сортировку фотографий
     * @param input_path Путь к исходной директории
     * @param output_path Путь к директории, куда будут сохряняться отсортированные фотографии
     */
    void sort_photo(QString input_path, QString output_path);

signals:
    /**
     * @brief progressChanged Сигнализирует о смене значения прогресса сортировки
     * @param value Значение прогресса
     */
    void progressChanged(int value);
    /**
     * @brief maxProgressChanged Передает максимальное возможное значение прогресса
     * @param max Максимальное значение прогресса
     */
    void maxProgressChanged(int max);
    /**
     * @brief logMessage Передает сообщение для логирования
     * @param message Сообщение лога
     */
    void logMessage(QString message);
    /**
     * @brief finished Сигнализирует об окончании сортировки
     */
    void finished();

private:
    /**
     * @brief m_isPaused Флаг постановки потока сортировки на паузу
     */
    std::atomic<bool> m_isPaused{false};
    /**
     * @brief m_isStopped Флаг полной остановки сортировки
     */
    std::atomic<bool> m_isStopped{false};
    /**
     * @brief exif_date Объект для получения даты создания/изменения фотографии из EXIF-данных
     */
    getting_exifdata* exif_date;
    /**
     * @brief m_pauseMutex Мьютекс для синхронизации состояния паузы.
     */
    QMutex m_pauseMutex;
    /**
     * @brief m_pauseCondition Условие ожидания для приостановки фонового потока.
     */
    QWaitCondition m_pauseCondition;
};

#endif // SORTING_PHOTO_H
