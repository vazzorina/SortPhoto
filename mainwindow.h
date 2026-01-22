#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "sorting_photo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbtn_get_photo_clicked();
    void on_pbtn_save_photo_clicked();
    void on_pbtn_start_clicked();

    void on_pbtn_stop_toggled(bool checked);

    void on_pbtn_finish_clicked();

private:
    Ui::MainWindow *ui;
    sorting_photo* sorting = nullptr;
    QString path_get_photo = "";
    QString path_save_photo = "";
    void get_path();
    void clear_ui();
};
#endif // MAINWINDOW_H
