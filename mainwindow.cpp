#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "doscyrillic.h"
#include <QtCore/QFileInfo>
#include <QtCore/QUrl>
#include <QtGui/QFileDialog>
#include <QtGui/QDragEnterEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonAddFiles_clicked()
{
    // Show the open file dialog.
    const QStringList &fileNames = QFileDialog::getOpenFileNames(this, "", "", "Assembly files (*.asm);;Text files (*.txt);;All files (*.*)");

    // Because full file paths look ugly, we add only the file name without the
    // path. The full file path can still be seen as a tooltip.
    foreach (const QString &fileName, fileNames) {
        addFileName(fileName);
    }
}

void MainWindow::on_pushButtonRemoveFiles_clicked()
{
    qDeleteAll(ui->listWidgetFileNames->selectedItems());
}

void MainWindow::on_pushButtonFromDos_clicked()
{
    for (int ii = 0; ii < ui->listWidgetFileNames->count(); ii++) {
        dosFileToUtf8(getFileName(ii));
    }
}

void MainWindow::on_pushButtonToDos_clicked()
{
    for (int ii = 0; ii < ui->listWidgetFileNames->count(); ii++) {
        utf8FileToDos(getFileName(ii));
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    } else {
        QMainWindow::dragEnterEvent(event);
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    foreach (const QUrl &url, event->mimeData()->urls()) {
        addFileName(url.toLocalFile());
    }
}

void MainWindow::addFileName(const QString &fileName)
{
    QListWidgetItem *item = new QListWidgetItem;
    item->setText(QFileInfo(fileName).fileName());
    item->setToolTip(fileName);
    ui->listWidgetFileNames->addItem(item);
}

QString MainWindow::getFileName(int index)
{
    // The full file path is contained in the tooltip.
    return ui->listWidgetFileNames->item(index)->toolTip();
}
