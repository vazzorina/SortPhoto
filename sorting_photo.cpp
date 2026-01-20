#include "sorting_photo.h"
#include "getting_exifdata.h"
#include <QDirIterator>
#include <QDir>
#include <vector>
#include <QDateTime>
#include <algorithm>

sorting_photo::sorting_photo() {}

void sorting_photo::sort_photo(QString input_path, QString output_path, QTextEdit* te, QProgressBar* pb) {
    QDir dir(input_path);
    QStringList filters;
    filters << "*.jpg" << "*.png" << "*.jpeg";
    dir.setNameFilters(filters);
    pb->setMaximum(dir.entryList(QDir::Files).count());

    te->append("INFO: началась сортировка фотографий");
    QDirIterator input_catalog(input_path,
                               QStringList() << "*.png" << "*.jpg" << "*.jpeg",
                               QDir::Files,
                               QDirIterator::Subdirectories);
    QDir output_catalog;
    std::vector<QString> date_dirs;
    QString itemPath, outp_path, year;
    QDateTime date;

    while (input_catalog.hasNext()) {
        itemPath = input_catalog.next();
        date = exif_date->get_exif_date(itemPath, te);
        year = QString::number(date.date().year());
        outp_path = output_path + "/" + year + "/" + date.toString("dd.MM.yyyy HH-mm") + "." + input_catalog.fileInfo().suffix();
        if (!date.isNull() and std::find(date_dirs.begin(), date_dirs.end(), year) != date_dirs.end()) {
            if (QFile::copy(itemPath, outp_path)) {
                te->append("INFO: Файл успешно скопирован и переименован: " + outp_path);
            } else {
                te->append("WARN: Ошибка при копировании (возможно дубликат): " + itemPath);
            }
        }
        else if (!date.isNull() and std::find(date_dirs.begin(), date_dirs.end(), year) == date_dirs.end()) {
            date_dirs.push_back(year);
            if (output_catalog.mkpath(output_path + "/" + year)) {
                te->append("INFO:Папки успешно созданы: " + output_path + "/" + year);
                if (QFile::copy(itemPath, outp_path)) {
                    te->append("INFO: Файл успешно скопирован и переименован: " + outp_path);
                } else {
                    te->append("WARN: Ошибка при копировании (возможно дубликат): " + itemPath);
                }
            } else {
                te->append("WARN: Не удалось создать путь: " + output_path + "/" + year);
            }
        }
        pb->setValue(pb->value() + 1);
    }

    te->append("INFO: сортировка фотографий окончена");
}
