#include <QFileSystemModel>
#include <QObject>
#include <fstream>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_tree_view();

    ui->selectButton->setDisabled(true);
    ui->cancelButton->setDisabled(true);
    ui->saveButton->setDisabled(true);

    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::folder_tree_model_item_clicked);
    connect(ui->selectButton, &QPushButton::clicked, this, &MainWindow::load_button_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_tree_view() {
    folder_tree_model = std::move(std::make_unique<QFileSystemModel>());
    QStringList filters;

    filters << "*.csv"; // nur .csv Dateien anzeigen

    folder_tree_model->setRootPath(QDir::currentPath());
    folder_tree_model->setNameFilters(filters); // Filter setzen
    folder_tree_model->setNameFilterDisables(false); // sichergehen dass NameFilter aktiviert ist

    ui->treeView->setModel(folder_tree_model.get());
//	^ von dem ui
//		^ bei diesen Element "treeView"
//				  ^ dieses Model setzen
}

void MainWindow::load_from_csv(const QString filepath) {
    if(QFileInfo::exists(filepath)) { // sanity check
        std::ifstream if_ss(filepath.toStdString());
        if(!if_ss.is_open()) {
            return;
        }

        std::string templ;
        while(!if_ss.eof()) {
            std::getline(if_ss, templ);
            ui->plainTextEdit->appendPlainText(templ.c_str());
        }
    }
}

void MainWindow::load_button_clicked(void) {
    this->load_from_csv(
        folder_tree_model->filePath(ui->treeView->currentIndex())
        );
}

void MainWindow::folder_tree_model_item_clicked(const QModelIndex& index) {
    QModelIndex current = ui->treeView->currentIndex();
    const QString filename = folder_tree_model->fileName(current);
    if(filename.endsWith(".csv")) {
        ui->selectButton->setEnabled(true);
    } else {
        ui->selectButton->setDisabled(true);
    }
}
