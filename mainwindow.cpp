#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbtn_get_photo_clicked()
{
    path_get_photo = "";
    get_path();
}


void MainWindow::on_pbtn_save_photo_clicked()
{
    path_save_photo = "";
    get_path();
}

void MainWindow::get_path() {
    QString pictures_path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    if (path_get_photo.isEmpty()) {
        path_get_photo = QFileDialog::getExistingDirectory(this, "Выберите нужный каталог", pictures_path);
        path_save_photo = "";
        ui->le_save_photo->setText(path_save_photo);
        ui->le_get_photo->setText(path_get_photo);
    }
    else if (path_save_photo.isEmpty()){
        path_save_photo = QFileDialog::getExistingDirectory(this, "Выберите нужный каталог", pictures_path);
        while(path_get_photo == path_save_photo) {
            QMessageBox::warning(this, "Ошибка!", "Невозможно сохранить фотографии в тот же каталог, "
                                                        "в котором они расположены изначально! "
                                                        "Выберите другой каталог.");
            path_save_photo = QFileDialog::getExistingDirectory(this, "Выберите нужный каталог", pictures_path);
        }
        ui->le_save_photo->setText(path_save_photo);
    }
}

void MainWindow::on_rbtn_delete_dublicates_toggled(bool checked)
{
    is_delete_dublicates = checked;
}


void MainWindow::on_pbtn_start_clicked()
{
    if (path_get_photo.isEmpty() and path_save_photo.isEmpty()) {
        QMessageBox::warning(this, "Ошибка!", "Не указаны пути каталогов!");
    }
    else {
        ui->pbtn_start->setEnabled(false);
        ui->pbtn_finish->setEnabled(true);
        //фукция запуска сортировки
    }
}


void MainWindow::on_pbtn_stop_clicked()
{
    if(ui->pbtn_stop->text() == "Остановить"){
        ui->pbtn_stop->setText("Продолжить");
        //здесь будет функция остановки сортировки
    }
    else {
        ui->pbtn_stop->setText("Остановить");
        //здесь будет функция возобновления сортировки
    }
}


void MainWindow::on_pbtn_finish_clicked()
{
    ui->pbtn_start->setEnabled(true);
    ui->pbtn_finish->setEnabled(false);
    //функция полного прекращения сортировки
}

