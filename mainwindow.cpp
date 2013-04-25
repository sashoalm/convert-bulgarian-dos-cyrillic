#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "doscyrillic.h"
#include <QtGui/QFileDialog>
#include <QFileInfo>

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

void MainWindow::on_pushButton_clicked()
{
    // Show the open file dialog.
    const QStringList &fileNames = QFileDialog::getOpenFileNames(this, "", "", "Assembly files (*.asm);;Text files (*.txt);;All files (*.*)");

    // Because full file paths look ugly, we add only the file name without the
    // path. The full file path can still be seen as a tooltip.
    foreach (const QString &fileName, fileNames) {
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(QFileInfo(fileName).fileName());
        item->setToolTip(fileName);
        ui->listWidget->addItem(item);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    qDeleteAll(ui->listWidget->selectedItems());
}

void MainWindow::on_pushButton_3_clicked()
{
    // The full file path is contained in the tooltip.
    for (int ii = 0; ii < ui->listWidget->count(); ii++)
        dosFileToUtf8(ui->listWidget->item(ii)->toolTip());
}

void MainWindow::on_pushButton_4_clicked()
{
    // The full file path is contained in the tooltip.
    for (int ii = 0; ii < ui->listWidget->count(); ii++)
        utf8FileToDos(ui->listWidget->item(ii)->toolTip());
}
