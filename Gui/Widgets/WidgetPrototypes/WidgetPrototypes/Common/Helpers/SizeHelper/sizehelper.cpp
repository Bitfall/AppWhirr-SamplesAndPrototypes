#include "sizehelper.h"

#include "math.h"

SizeHelper::SizeHelper()
{
}

QSize SizeHelper::normalizedIntBasedSizeFromFloatBasedSize(QSizeF floatBasedSize, bool isRoundIt)
{
    int w = (isRoundIt ? round(floatBasedSize.width()) : floatBasedSize.width());
    int h = (isRoundIt ? round(floatBasedSize.height()) : floatBasedSize.height());
    return QSize((w < 0 ? 0 : w), (h < 0 ? 0 : h));
}
