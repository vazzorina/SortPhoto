#ifndef CHECKING_PATHS_H
#define CHECKING_PATHS_H
#include <QFileDialog>
#include <QString>
#include <QMainWindow>
class checking_paths
{
public:
    checking_paths();
    QFileDialog* file_dialog;
    QString path;
    QString get_path(QMainWindow* mainwindow, QString check_path = "NONE");
};

#endif // CHECKING_PATHS_H
