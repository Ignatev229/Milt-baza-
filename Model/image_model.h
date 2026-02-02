#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "ViewModel/image_view_vm.h"

struct ImageViewFeature{
    ImageViewVM *imageViewVM;
};

class ImageModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ImageModel(QObject *parent = nullptr);
    ~ImageModel();

    // Enum for custom roles in the list model // Перечисление для пользовательских ролей в модели списка
    enum DataRoles {
        imageViewVMRole = Qt::UserRole + 1
    };

    // Adds data to the model // Добавляет данные в модель
    void addData(const ImageViewFeature& entry);

    // Returns the number of rows in the model // Возвращает количество строк в модели
    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    // Returns data for a given index and role // Возвращает данные для заданного индекса и роли
    QVariant data(const QModelIndex & index, int role) const;

    // Returns a hash of role names used in the model // Возвращает хэш имен ролей, используемых в модели
    QHash<int, QByteArray> roleNames() const;

    // Edits input data for a given row // Редактирует входные данные для данной ряда
    void editInputData(int row, const QVariant &value, int role = Qt::EditRole);

    // Creates data from a list of image view features // Создает данные из списка объектов для просмотра изображений
    void createData(QList<ImageViewFeature> data);

    // List of image view features managed by this model // Список функций просмотра изображений, управляемых этой моделью
    QList<ImageViewFeature> _model;


signals:

};

#endif // IMAGEMODEL_H
