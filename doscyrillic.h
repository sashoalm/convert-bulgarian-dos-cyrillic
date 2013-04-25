#ifndef DOSCYRILLIC_H
#define DOSCYRILLIC_H

class QString;

// Converts a file from DOS Cyrillic encoding to UTF-8.
void dosFileToUtf8(const QString &fileName);

// Converts a file from UTF-8 to DOS Cyrillic encoding.
void utf8FileToDos(const QString &fileName);

#endif // DOSCYRILLIC_H
