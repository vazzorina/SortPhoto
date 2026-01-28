#ifndef GETTING_EXIFDATA_H
#define GETTING_EXIFDATA_H

#include <QObject>
#include <exiv2/exiv2.hpp>
#include <QString>
#include <QDateTime>
/**
 * @brief Класс getting_exifdata для получения даты создания/изменения фотографии из EXIF-данных
 */
class getting_exifdata : public QObject
{
    Q_OBJECT
public:
    explicit getting_exifdata(QObject *parent = nullptr);
    /**
     * @brief get_exif_date Достает дату создания фотографии из EXIF-данных, либо дату изменения из QFileInfo, в случае если EXIF-данные отсутсвуют
     * @param file Путь до фотографии
     * @return Дата создания/изменения фотографии
     */
    QDateTime get_exif_date(QString file);
};

#endif // GETTING_EXIFDATA_H
