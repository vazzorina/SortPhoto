#ifndef GETTING_EXIFDATA_H
#define GETTING_EXIFDATA_H

#include <exiv2/exiv2.hpp>
#include <QString>
#include <QDateTime>
#include <vector>
#include <string>

class getting_exifdata
{
public:
    std::vector<std::string> ID_photos;
    getting_exifdata();
    QDateTime get_exif_date(QString file);
};

#endif // GETTING_EXIFDATA_H
