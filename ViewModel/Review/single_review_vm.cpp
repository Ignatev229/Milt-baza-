#include "single_review_vm.h"

SingleReviewVM::SingleReviewVM(QObject *parent)
    : QObject{parent}
{
    setInfo("None");
    defaultImage = QImage(QString(":/Resources/NoneCamera.png"));
}

SingleReviewVM::~SingleReviewVM()
{

}

QList<QImage> SingleReviewVM::listImage()
{
    return _listImage;
}

QString SingleReviewVM::info()
{
    return _info;
}

QImage SingleReviewVM::listImageListAt(int index) const
{
    if (index<0 || index>= _listImage.size())
        return QImage();
    return _listImage[index];
}

void SingleReviewVM::UpdateImage(QImage &image, int docIndex)
{
    if(docIndex >= _listImage.size())
    {
        qDebug() << "Doc index bigger than num doc of this track";
        return;
    }
    _listImage[docIndex] = image;
    setListImage(_listImage);
}

void SingleReviewVM::UpdateAllImage(QList<QImage> &images)
{
    for(int i = 0; i < ConfigApplication::instance()->m_nReviewDoc; i++)
    {
        UpdateImage(images[i], i);
    }
}

void SingleReviewVM::ClearSingleReview()
{
    _listImage.clear();
    for (int i = 0; i < ConfigApplication::instance()->m_nReviewDoc; ++i) {
        _listImage.append(defaultImage);
    }
    setListImage(_listImage);
    setInfo("None");
}

void SingleReviewVM::setListImage(QList<QImage> &value)
{
    _listImage = value;
    emit listImageChanged();
}

void SingleReviewVM::setInfo(QString value)
{
    if(_info != value){_info = value; emit infoChanged();}

}


