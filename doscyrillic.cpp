#include "doscyrillic.h"
#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtCore/QFile>

// There are 32 letters (it is actually the russian alphabet it seems).
static const int lettersCount = 32;

// The Unicode code of the Cyrillic A.
static const int unicode_A = 1040;

// The DOS code of the Cyrillic A.
static const int dos_A = 128;

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

void dosFileToUtf8(const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QString converted = dosTextToUnicode(file.readAll());
    file.close();
    file.open(QIODevice::WriteOnly);
    file.write(converted.toUtf8());
}

void utf8FileToDos(const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QString converted = QString::fromUtf8(file.readAll());
    file.close();
    file.open(QIODevice::WriteOnly);
    file.write(unicodeTextToDos(converted));
}
