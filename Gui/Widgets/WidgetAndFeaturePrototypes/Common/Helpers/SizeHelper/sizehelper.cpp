#include "sizehelper.h"

#include "math.h"

inline double _roundd(double x) { return floor(x + 0.5); }

SizeHelper::SizeHelper()
{
}

QSize SizeHelper::normalizedIntBasedSizeFromFloatBasedSize(QSizeF floatBasedSize, bool isRoundIt)
{
    int w = (isRoundIt ? _roundd(floatBasedSize.width()) : floatBasedSize.width());
    int h = (isRoundIt ? _roundd(floatBasedSize.height()) : floatBasedSize.height());
    return QSize((w < 0 ? 0 : w), (h < 0 ? 0 : h));
}
