#ifndef UNCOMPRESSOR_H
#define UNCOMPRESSOR_H

#include <QString>

class Uncompressor
{
private:
    Uncompressor();

public:
    static bool uncompress(QString targetZipFilePath, QString targetOutputDirectoryPath);
};

#endif // UNCOMPRESSOR_H
