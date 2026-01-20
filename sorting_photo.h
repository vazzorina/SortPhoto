#ifndef SORTING_PHOTO_H
#define SORTING_PHOTO_H

#include "getting_exifdata.h"
#include <QObject>
#include <QWaitCondition>
#include <atomic>
#include <QMutex>

class sorting_photo : public QObject
{
    Q_OBJECT
public:
    explicit sorting_photo(QObject *parent = nullptr);

    // Геттеры для управления извне
    void setPaused(bool paused);
    void stop();

public slots:
    // Теперь параметры передаются строками, а не виджетами
    void sort_photo(QString input_path, QString output_path);

signals:
    void progressChanged(int value);
    void maxProgressChanged(int max);
    void logMessage(QString message);
    void finished();

private:
    std::atomic<bool> m_isPaused{false};
    std::atomic<bool> m_isStopped{false};
    getting_exifdata* exif_date;
    QMutex m_pauseMutex;
    QWaitCondition m_pauseCondition;
};

#endif // SORTING_PHOTO_H
