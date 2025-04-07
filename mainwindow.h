#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QFileSystemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    std::unique_ptr<QFileSystemModel> folder_tree_model{nullptr};

protected slots:
    /**
     * @brief load_button_clicked
     */
    void load_button_clicked(void);

    /**
     * @brief folder_tree_model_item_clicked
     * @param index
     */
    void folder_tree_model_item_clicked(const QModelIndex& index);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    /**
     * @brief MainWindow::init_tree_view
     * Initialisiert den Dateiexplorer mit speziellen Eigenschaften und fügt ihn dem `ui` zu
     */
    void init_tree_view(void);

    /**
     * @brief render_csv
     * Extrahiert den Inhalt einer .csv und zeigt ihn als plain text an
     * @param path Dateipfad
     * @param element Textfeld ptr auf dem csv Inhatl angezeigt wird
     */
    void load_from_csv(const QString filepath);
};
#endif // MAINWINDOW_H
