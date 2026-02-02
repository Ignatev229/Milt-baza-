#include "image_review_vm.h"

ImageReviewVM::ImageReviewVM(QObject *parent)
    : QObject{parent}
{}

ImageReviewVM::~ImageReviewVM()
{

}


QImage ImageReviewVM::image()
{
    return _image;
}

QImage ImageReviewVM::imageOverlay()
{
    return _imageOverlay;
}

QString ImageReviewVM::docName()
{
    return _docName;
}


void ImageReviewVM::setImage(QImage &image)
{
    _image = image;
    emit imageChanged();
}

void ImageReviewVM::setImageOverlay(QImage &image)
{
    _imageOverlay = image.copy();
    emit imageOverlayChanged();

}

void ImageReviewVM::setDocName(QString value)
{
    if(_docName == value)
        return;
    _docName = value;
    emit docNameChanged();
}

int ImageReviewVM::imageWidth()
{
    return _image.width();
}

int ImageReviewVM::imageHeight()
{
    return _image.height();
}

