#include "imagetopixmapconverter.h"

ImageToPixmapConverter::ImageToPixmapConverter()
{
}

QPixmap ImageToPixmapConverter::convertImageToPixmap(QImage image)
{
    return  QPixmap::fromImage(image);
}
