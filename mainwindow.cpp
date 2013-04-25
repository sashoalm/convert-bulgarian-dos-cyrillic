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

// Converts a single character from DOS Cyrillic encoding to Unicode.
static wchar_t dosCharToUnicode(unsigned char ch)
{
    wchar_t wch = ch;
    if (wch >= dos_A && wch < dos_A + 2 * lettersCount)
        wch += unicode_A - dos_A;

    return wch;
}

// Converts a single character from Unicode to DOS Cyrillic encoding.
static unsigned char unicodeCharToDos(wchar_t wch)
{
    if (wch >= unicode_A && wch < unicode_A + 2 * lettersCount)
        wch += dos_A - unicode_A;
    return wch;
}

// Converts a string from DOS Cyrillic encoding to Unicode.
static QString dosTextToUnicode(const QByteArray &text)
{
    std::wstring output;
    foreach (unsigned char ch, text)
        output += dosCharToUnicode(ch);
    return QString::fromStdWString(output);
}

// Converts a string from Unicode to DOS Cyrillic encoding.
// Note that we don't append a zero terminator.
static QByteArray unicodeTextToDos(const QString &text)
{
    QByteArray ret;
    foreach (QChar ch, text)
        ret.append(unicodeCharToDos(ch.unicode()));
    return ret;
}

// Converts a file from DOS Cyrillic encoding to UTF-8.
static void dosFileToUtf8(const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QString converted = dosTextToUnicode(file.readAll());
    file.close();
    file.open(QIODevice::WriteOnly);
    file.write(converted.toUtf8());
}

// Converts a file from UTF-8 to DOS Cyrillic encoding.
static void utf8FileToDos(const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QString converted = QString::fromUtf8(file.readAll());
    file.close();
    file.open(QIODevice::WriteOnly);
    file.write(unicodeTextToDos(converted));
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
