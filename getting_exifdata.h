#ifndef GETTING_EXIFDATA_H
#define GETTING_EXIFDATA_H

#include <exiv2/exiv2.hpp>
#include <QString>
#include <QTextEdit>
#include <QDate>
#include <vector>
#include <string>

class getting_exifdata
{
public:
    std::vector<std::string> ID_photos;
    getting_exifdata();
    QDate get_exif_date(QString file, QTextEdit* te, bool is_delete_dupli);
};

#endif // GETTING_EXIFDATA_H
