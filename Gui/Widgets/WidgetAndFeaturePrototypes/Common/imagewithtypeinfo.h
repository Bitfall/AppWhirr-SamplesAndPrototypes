#ifndef IMAGEWITHTYPEINFO_H
#define IMAGEWITHTYPEINFO_H

#include <QString>
#include "imagetypesenum.h"

class ImageWithTypeInfo
{
public:
    ImageWithTypeInfo(QString imagePath, ImageTypesEnum imageType);

    QString getImagePath() const;
    ImageTypesEnum getImageType() const;

private:
    QString _imagePath;
    ImageTypesEnum _imageType;
};

#endif // IMAGEWITHTYPEINFO_H
