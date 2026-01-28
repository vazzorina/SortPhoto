#include "getting_exifdata.h"
#include <exiv2/exiv2.hpp>
#include <QString>
#include <QDateTime>
#include <string>
#include <QFileInfo>

getting_exifdata::getting_exifdata(QObject *parent) : QObject(parent) {}

QDateTime getting_exifdata::get_exif_date(QString file) {
    std::string filePath = file.toLocal8Bit().constData();

    try {
        auto image = Exiv2::ImageFactory::open(filePath);
        image->readMetadata();
        Exiv2::ExifData& exifData = image->exifData();
        QFileInfo fileInfo(file);

        //Сначала читаем дату послденего изменения из информации о файле, так как она всегда существует
        std::string dateStr = fileInfo.lastModified().toString("yyyy:MM:dd HH:mm:ss").toStdString();

        //Проверяем тег Exif.Photo.DateTimeOriginal, так как в нем хранится дата съемки
        //Если тег не пустой, то dateStr изменится на дату съемки
        if(!exifData["Exif.Photo.DateTimeOriginal"].toString().empty()){
            dateStr = exifData["Exif.Photo.DateTimeOriginal"].toString();
        }

        // Превращаем строку EXIF-формата в объект QDateTime для удобной сортировки
        return QDateTime::fromString(QString::fromStdString(dateStr), "yyyy:MM:dd HH:mm:ss");

    } catch (Exiv2::Error& e) {
        //При ошибке чтения файла возвращаем пустую дату, чтобы вызывающий код проигнорировал данный файл
        return QDateTime();
    }
}
