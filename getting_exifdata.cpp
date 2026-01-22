#include "getting_exifdata.h"
#include <exiv2/exiv2.hpp>
#include <QString>
#include <QDateTime>
#include <string>
#include <algorithm>
#include <QFileInfo>

getting_exifdata::getting_exifdata() {}

QDateTime getting_exifdata::get_exif_date(QString file) {
    std::string filePath = file.toLocal8Bit().constData();

    try {
        auto image = Exiv2::ImageFactory::open(filePath);
        image->readMetadata();
        Exiv2::ExifData& exifData = image->exifData();

        QFileInfo fileInfo(file);
        std::string dateStr = fileInfo.lastModified().toString("yyyy:MM:dd HH:mm:ss").toStdString();
        if(!exifData["Exif.Photo.DateTimeOriginal"].toString().empty()){
            dateStr = exifData["Exif.Photo.DateTimeOriginal"].toString();
        }
        std::string id_photo = exifData["Exif.Photo.ImageUniqueID"].toString();

        if (std::count(ID_photos.begin(), ID_photos.end(), id_photo) == 0) {
            ID_photos.push_back(id_photo);
        }
        return QDateTime::fromString(QString::fromStdString(dateStr), "yyyy:MM:dd HH:mm:ss");
    } catch (Exiv2::Error& e) {
        return QDateTime();
    }

    return QDateTime();
}
