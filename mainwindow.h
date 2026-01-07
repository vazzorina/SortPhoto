#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_rbtn_delete_dublicates_toggled(bool checked);

    void on_pbtn_start_clicked();

    void on_pbtn_stop_clicked();

    void on_pbtn_finish_clicked();

private:
    Ui::MainWindow *ui;
    QString path_get_photo = "";
    QString path_save_photo = "";
    bool is_delete_dublicates = true;
    void get_path();
};
#endif // MAINWINDOW_H
