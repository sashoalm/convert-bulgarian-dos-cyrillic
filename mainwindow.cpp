#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui/QFileDialog>

// There are 32 letters (it is actually the russian alphabet it seems).
static const int lettersCount = 32;
// The Unicode code of the Cyrillic A.
static const int unicode_A = 1040;
// The DOS code of the Cyrillic A.
static const int dos_A = 128;

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
    wchar_t wch = ch;
    if (wch >= dos_A && wch < dos_A + 2 * lettersCount)
        wch += unicode_A - dos_A;

    return wch;
}

unsigned char toCyrCom(wchar_t wch)
{
    if (wch >= unicode_A && wch < unicode_A + 2 * lettersCount)
        wch += dos_A - unicode_A;
    return wch;
}

QString cyrComToUtf8(const QByteArray &text)
{
    std::wstring output;
    foreach (unsigned char ch, text)
        output += fromCyrCom(ch);
    return QString::fromStdWString(output);
}

QByteArray toCyrCom(const QString &text)
{
    QByteArray ret;
    foreach (QChar ch, text)
        ret.append(toCyrCom(ch.unicode()));
    return ret;
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

void utf8FileToCyrComFile(const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QString converted = QString::fromUtf8(file.readAll());
    file.close();
    file.open(QIODevice::WriteOnly);
    file.write(toCyrCom(converted));
}

void MainWindow::on_pushButton_3_clicked()
{
    for (int ii = 0; ii < ui->listWidget->count(); ii++)
        cyrComFileToUtf8File(ui->listWidget->item(ii)->text());
}

void MainWindow::on_pushButton_4_clicked()
{
    for (int ii = 0; ii < ui->listWidget->count(); ii++)
        utf8FileToCyrComFile(ui->listWidget->item(ii)->text());
}
