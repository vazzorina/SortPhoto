#include "checking_paths.h"


checking_paths::checking_paths() {

}

QString checking_paths::get_path(QMainWindow* mainwindow, QString check_path) {
    if (check_path == "NONE") {
        path = QFileDialog::getExistingDirectory(mainwindow, "Выберите нужный каталог", "/Pictures");
    }
}
