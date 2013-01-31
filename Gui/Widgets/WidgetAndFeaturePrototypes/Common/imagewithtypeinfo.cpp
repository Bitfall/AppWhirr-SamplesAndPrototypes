#include "imagewithtypeinfo.h"

ImageWithTypeInfo::ImageWithTypeInfo(QString imagePath, ImageTypesEnum imageType):
    _imagePath(imagePath),
    _imageType(imageType)
{
}

QString ImageWithTypeInfo::getImagePath() const
{
    return this->_imagePath;
}

ImageTypesEnum ImageWithTypeInfo::getImageType() const
{
    return this->_imageType;
}
