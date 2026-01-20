#ifndef SORTING_PHOTO_H
#define SORTING_PHOTO_H

#include "getting_exifdata.h"
#include <QTextEdit>
class sorting_photo
{
public:
    sorting_photo();
    getting_exifdata *exif_date = new getting_exifdata();
    void sort_photo(QString input_path, QString output_path, QTextEdit* te);
};

#endif // SORTING_PHOTO_H
