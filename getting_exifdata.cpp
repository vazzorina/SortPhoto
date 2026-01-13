#include "getting_exifdata.h"
#include <exiv2/exiv2.hpp>
#include <QString>
#include <QTextEdit>
#include <QDate>
#include <string>
#include <algorithm>

getting_exifdata::getting_exifdata() {}

QDate getting_exifdata::get_exif_date(QString file, QTextEdit* te) {
    std::string filePath = file.toLocal8Bit().constData();

    try {
        auto image = Exiv2::ImageFactory::open(filePath);
        image->readMetadata();
        Exiv2::ExifData& exifData = image->exifData();

        if (exifData.empty()) {
            te->append("ERROR: exif-данные фотографии отсутствуют");
            return QDate();
        }
        std::string dateStr = exifData["Exif.Image.DateTime"].toString();
        if(!exifData["Exif.Photo.DateTimeOriginal"].toString().empty()){
            dateStr = exifData["Exif.Photo.DateTimeOriginal"].toString();
        }
        std::string id_photo = exifData["Exif.Photo.ImageUniqueID"].toString();

        if (std::count(ID_photos.begin(), ID_photos.end(), id_photo) != 0) {
            te->append("WARN: дубликат фотографии");
            return QDate();
        }
        else {
            ID_photos.push_back(id_photo);
            return QDate::fromString(QString::fromStdString(dateStr).left(10), "yyyy:MM:dd");
        }

    } catch (Exiv2::Error& e) {
        return QDate();
    }

    return QDate();
}
