/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_path_nosort_catalog;
    QLabel *label_path_sorted_catalog;
    QLabel *label_is_delete_duplicates;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rbtn_delete_dublicates;
    QRadioButton *rbtn_keep_dublicates;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *le_get_photo;
    QPushButton *pbtn_get_photo;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *le_save_photo;
    QPushButton *pbtn_save_photo;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pbtn_start;
    QPushButton *pbtn_stop;
    QPushButton *pbtn_finish;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *te_logger;
    QProgressBar *progress_bar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(585, 449);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_path_nosort_catalog = new QLabel(centralwidget);
        label_path_nosort_catalog->setObjectName("label_path_nosort_catalog");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_path_nosort_catalog);

        label_path_sorted_catalog = new QLabel(centralwidget);
        label_path_sorted_catalog->setObjectName("label_path_sorted_catalog");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_path_sorted_catalog);

        label_is_delete_duplicates = new QLabel(centralwidget);
        label_is_delete_duplicates->setObjectName("label_is_delete_duplicates");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_is_delete_duplicates);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        rbtn_delete_dublicates = new QRadioButton(centralwidget);
        rbtn_delete_dublicates->setObjectName("rbtn_delete_dublicates");

        horizontalLayout->addWidget(rbtn_delete_dublicates);

        rbtn_keep_dublicates = new QRadioButton(centralwidget);
        rbtn_keep_dublicates->setObjectName("rbtn_keep_dublicates");

        horizontalLayout->addWidget(rbtn_keep_dublicates);


        formLayout->setLayout(2, QFormLayout::ItemRole::FieldRole, horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        le_get_photo = new QLineEdit(centralwidget);
        le_get_photo->setObjectName("le_get_photo");

        horizontalLayout_3->addWidget(le_get_photo);

        pbtn_get_photo = new QPushButton(centralwidget);
        pbtn_get_photo->setObjectName("pbtn_get_photo");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::FolderOpen));
        pbtn_get_photo->setIcon(icon);

        horizontalLayout_3->addWidget(pbtn_get_photo);


        formLayout->setLayout(0, QFormLayout::ItemRole::FieldRole, horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        le_save_photo = new QLineEdit(centralwidget);
        le_save_photo->setObjectName("le_save_photo");

        horizontalLayout_4->addWidget(le_save_photo);

        pbtn_save_photo = new QPushButton(centralwidget);
        pbtn_save_photo->setObjectName("pbtn_save_photo");
        pbtn_save_photo->setIcon(icon);

        horizontalLayout_4->addWidget(pbtn_save_photo);


        formLayout->setLayout(1, QFormLayout::ItemRole::FieldRole, horizontalLayout_4);


        verticalLayout->addLayout(formLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        pbtn_start = new QPushButton(centralwidget);
        pbtn_start->setObjectName("pbtn_start");

        horizontalLayout_5->addWidget(pbtn_start);

        pbtn_stop = new QPushButton(centralwidget);
        pbtn_stop->setObjectName("pbtn_stop");

        horizontalLayout_5->addWidget(pbtn_stop);

        pbtn_finish = new QPushButton(centralwidget);
        pbtn_finish->setObjectName("pbtn_finish");

        horizontalLayout_5->addWidget(pbtn_finish);


        verticalLayout->addLayout(horizontalLayout_5);

        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 565, 228));
        horizontalLayout_2 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        te_logger = new QTextEdit(scrollAreaWidgetContents);
        te_logger->setObjectName("te_logger");

        horizontalLayout_2->addWidget(te_logger);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        progress_bar = new QProgressBar(centralwidget);
        progress_bar->setObjectName("progress_bar");
        progress_bar->setValue(24);

        verticalLayout->addWidget(progress_bar);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(2, 3);
        verticalLayout->setStretch(3, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 585, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_path_nosort_catalog->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\203\320\264\320\260 \320\261\321\200\320\260\321\202\321\214 \321\204\320\276\321\202\320\276\320\263\321\200\320\260\321\204\320\270\320\270:", nullptr));
        label_path_sorted_catalog->setText(QCoreApplication::translate("MainWindow", "\320\232\321\203\320\264\320\260 \321\201\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \321\204\320\276\321\202\320\276\320\263\321\200\320\260\321\204\320\270\320\270:", nullptr));
        label_is_delete_duplicates->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\321\217\321\202\321\214 \320\264\321\203\320\261\320\273\320\270\320\272\320\260\321\202\321\213 \321\204\320\276\321\202\320\276\320\263\321\200\320\260\321\204\320\270\320\271:", nullptr));
        rbtn_delete_dublicates->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        rbtn_keep_dublicates->setText(QCoreApplication::translate("MainWindow", "\320\236\321\201\321\202\320\260\320\262\320\270\321\202\321\214", nullptr));
        pbtn_get_photo->setText(QString());
        pbtn_save_photo->setText(QString());
        pbtn_start->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214 \321\201\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\272\321\203", nullptr));
        pbtn_stop->setText(QCoreApplication::translate("MainWindow", "\320\236\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        pbtn_finish->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\265\321\200\320\262\320\260\321\202\321\214 \320\277\320\276\320\273\320\275\320\276\321\201\321\202\321\214\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
