#include <QApplication>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtGui/QFileDialog>

QString cyrComToUtf8(const QByteArray &text)
{
    std::wstring output;
    const int cyr_a = 0xA0;
    const int dist = L'Я'-L'А';
    const int cyr_A = 0x90-L'Р'+L'А';
    foreach (unsigned char ch, text) {
        wchar_t wch = ch;
        if (wch >= cyr_a && wch <= cyr_a + dist) {
            wch += L'а' - cyr_a;
        } else if (ch >= cyr_A && ch <= cyr_A + dist) {
            wch += L'А' - cyr_A;
        }

        output += wch;
    }

    return QString::fromStdWString(output);
}

void cyrComFileToUtf8(const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QString converted = cyrComToUtf8(file.readAll());
    file.close();
    file.open(QIODevice::WriteOnly);
    file.write(converted.toUtf8());
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    const QString &fileName = QFileDialog::getOpenFileName(0, "", "", "ASM Files (*.asm)");
    if (!fileName.isEmpty())
        cyrComFileToUtf8(fileName);
    
    return 0;
}
