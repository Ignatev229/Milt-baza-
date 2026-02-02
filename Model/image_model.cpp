#include "image_model.h"

ImageModel::ImageModel(QObject *parent) : QAbstractListModel(parent)
{

}

ImageModel::~ImageModel()
{
    for (int i = 0; i < _model.size(); i++)
    {
        delete[] _model[i].imageViewVM;
    }
}

void ImageModel::addData(const ImageViewFeature& entry)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _model << entry;
    endInsertRows();
}

int ImageModel::rowCount(const QModelIndex &parent) const
{
    parent.isValid();
    return _model.count();
}

QVariant ImageModel::data(const QModelIndex & index, int role) const
{
    if ( !index.isValid() || index.row() < 0 || index.row() >= _model.count() )
        return QVariant();
    ImageViewFeature modelEntry = _model[index.row()];
    if (role == imageViewVMRole) {return QVariant::fromValue(modelEntry.imageViewVM);}
    return QVariant();
}

// roleNames() method for QAbstractListModel: //Метод roleNames() для QAbstractListModel:
QHash<int, QByteArray> ImageModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[imageViewVMRole] = "imageViewVM";
    return roles;
}

void ImageModel::editInputData(int row, const QVariant &value, int role)
{
    QModelIndex index = this->index(row, 0);
    if ( !index.isValid() || index.row() < 0 || index.row() >= _model.count() )
        return ;
    if (role == imageViewVMRole) {_model[index.row()].imageViewVM = value.value<ImageViewVM*>();}
    emit dataChanged(index, index, {role});
}


void ImageModel::createData(QList<ImageViewFeature> data)
{
//    ImageViewFeature ;// = new ImageViewFeature[data.size()]; //особенность просмотра изображений ;// = новое особенность просмотра изображений[data.size()];
    for (int i = 0; i < data.size(); i++)
    {
        ImageViewFeature imageViewFeature;
        imageViewFeature.imageViewVM = data[i].imageViewVM;
        _model<<imageViewFeature;
    }
}
