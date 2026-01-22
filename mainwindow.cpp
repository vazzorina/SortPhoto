#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sorting_photo.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QThread>
#include <QTimer>

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


void MainWindow::on_pbtn_start_clicked()
{
    if (path_get_photo.isEmpty() and path_save_photo.isEmpty()) {
        QMessageBox::warning(this, "Ошибка!", "Не указаны пути каталогов!");
    }
    else {
        ui->pbtn_start->setEnabled(false);
        ui->pbtn_finish->setEnabled(true);
        ui->pbtn_stop->setEnabled(true);

        sorting = new sorting_photo();
        QThread* thread = new QThread();

        //запуск сортировки в отдельном процессе
        connect(thread, &QThread::started, sorting, [=](){
            sorting->sort_photo(path_get_photo, path_save_photo);
        });

        connect(sorting, &sorting_photo::logMessage, ui->te_logger, &QTextEdit::append);
        connect(sorting, &sorting_photo::progressChanged, ui->progress_bar, &QProgressBar::setValue);
        connect(sorting, &sorting_photo::maxProgressChanged, ui->progress_bar, &QProgressBar::setMaximum);
        // connect(ui->pbtn_stop, &QPushButton::toggled, sorting, [=](bool checked){

        // });

         // connect(ui->pbtn_finish, &QPushButton::clicked, sorting, [=](){

         // });

        // Очистка памяти
        connect(sorting, &sorting_photo::finished, thread, &QThread::quit);
        connect(thread, &QThread::finished, sorting, &QObject::deleteLater);
        connect(thread, &QThread::finished, thread, &QObject::deleteLater);

        connect(sorting, &sorting_photo::finished, this, [this](){
            ui->pbtn_finish->setText("Начать новую сортировку");
        });

        sorting->moveToThread(thread);
        thread->start();
    }
}

void MainWindow::clear_ui() {
    ui->pbtn_stop->setText("Остановить");
    ui->pbtn_finish->setText("Прервать полностью");
    path_get_photo = "";
    path_save_photo = "";
    ui->le_save_photo->clear();
    ui->le_get_photo->clear();
    ui->te_logger->clear();
    ui->pbtn_start->setEnabled(true);
    ui->pbtn_finish->setEnabled(false);
    ui->pbtn_stop->setEnabled(false);
    ui->progress_bar->setValue(0);
    ui->pbtn_stop->setChecked(false);
    sorting = nullptr;
}





void MainWindow::on_pbtn_stop_toggled(bool checked)
{
    if (sorting) {
        if (checked) {
            ui->pbtn_stop->setText("Продолжить");
            sorting->setPaused(true);
        } else {
            ui->pbtn_stop->setText("Остановить");
            sorting->setPaused(false);
        }
    }
}


void MainWindow::on_pbtn_finish_clicked()
{
    if (sorting and ui->pbtn_finish->text() != "Начать новую сортировку") {
        sorting->stop();
        sorting->setPaused(false);
    }
    QTimer::singleShot(500, this, &MainWindow::clear_ui);
}

