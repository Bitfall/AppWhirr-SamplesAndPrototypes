#ifndef IMAGETOPIXMAPCONVERTER_H
#define IMAGETOPIXMAPCONVERTER_H

#include <QPixmap>
#include <QImage>

class ImageToPixmapConverter
{
private:
    ImageToPixmapConverter();

public:
    static QPixmap convertImageToPixmap(QImage image);
};

#endif // IMAGETOPIXMAPCONVERTER_H
