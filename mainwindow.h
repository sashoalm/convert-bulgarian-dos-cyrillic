#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButtonAddFiles_clicked();

    void on_pushButtonRemoveFiles_clicked();

    void on_pushButtonFromDos_clicked();

    void on_pushButtonToDos_clicked();

private:
    Ui::MainWindow *ui;
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void addFileName(const QString &fileName);
    QString getFileName(int index);
};

#endif // MAINWINDOW_H
