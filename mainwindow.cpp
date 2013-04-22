#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    ui->listWidget->addItems(QFileDialog::getOpenFileNames(this, "", "", "Assembly files (*.asm);;All files (*.*)"));
}

void MainWindow::on_pushButton_2_clicked()
{
    qDeleteAll(ui->listWidget->selectedItems());
}

wchar_t fromCyrCom(unsigned char ch)
{
    const int cyr_a = 0xA0;
    const int dist = L'Я'-L'А';
    const int cyr_A = 0x90-L'Р'+L'А';

    wchar_t wch = ch;
    if (wch >= cyr_a && wch <= cyr_a + dist) {
        wch += L'а' - cyr_a;
    } else if (ch >= cyr_A && ch <= cyr_A + dist) {
        wch += L'А' - cyr_A;
    }

    return wch;
}

QString cyrComToUtf8(const QByteArray &text)
{
    std::wstring output;
    foreach (unsigned char ch, text)
        output += fromCyrCom(ch);
    return QString::fromStdWString(output);
}

void cyrComFileToUtf8File(const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QString converted = cyrComToUtf8(file.readAll());
    file.close();
    file.open(QIODevice::WriteOnly);
    file.write(converted.toUtf8());
}

void MainWindow::on_pushButton_3_clicked()
{
    for (int ii = 0; ii < ui->listWidget->count(); ii++)
        cyrComFileToUtf8File(ui->listWidget->item(ii)->text());
}