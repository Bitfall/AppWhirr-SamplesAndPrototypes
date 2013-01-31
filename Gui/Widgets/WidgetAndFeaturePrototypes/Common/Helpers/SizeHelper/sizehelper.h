#ifndef SIZEHELPER_H
#define SIZEHELPER_H

#include <QSize>
#include <QSizeF>

class SizeHelper
{
private:
    SizeHelper();

public:
    static QSize normalizedIntBasedSizeFromFloatBasedSize(QSizeF floatBasedSize, bool isRoundIt = true);
};

#endif // SIZEHELPER_H
