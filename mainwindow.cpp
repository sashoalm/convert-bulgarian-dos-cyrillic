#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "doscyrillic.h"
#include <QtGui/QFileDialog>

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
    ui->listWidget->addItems(QFileDialog::getOpenFileNames(this, "", "", "Assembly files (*.asm);;Text files (*.txt);;All files (*.*)"));
}

void MainWindow::on_pushButton_2_clicked()
{
    qDeleteAll(ui->listWidget->selectedItems());
}

void MainWindow::on_pushButton_3_clicked()
{
    for (int ii = 0; ii < ui->listWidget->count(); ii++)
        dosFileToUtf8(ui->listWidget->item(ii)->text());
}

void MainWindow::on_pushButton_4_clicked()
{
    for (int ii = 0; ii < ui->listWidget->count(); ii++)
        utf8FileToDos(ui->listWidget->item(ii)->text());
}
