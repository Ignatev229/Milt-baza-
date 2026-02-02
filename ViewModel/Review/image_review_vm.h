#ifndef IMAGEREVIEWVM_H
#define IMAGEREVIEWVM_H

#include <QObject>
#include <QPainter>
#include <QQuickItem>
#include <QQuickPaintedItem>

class ImageReviewVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QImage image MEMBER _image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(QImage imageOverlay MEMBER _imageOverlay READ imageOverlay WRITE setImageOverlay NOTIFY imageOverlayChanged)
    Q_PROPERTY(QString docName READ docName WRITE setDocName NOTIFY docNameChanged)

public:
    explicit ImageReviewVM(QObject *parent = nullptr);
    ~ImageReviewVM();
    //
    QImage image();
    QImage imageOverlay();
    QString docName();
    //

private:
    // Property //  Собственность
    QImage _image;
    QImage _imageOverlay;
    QString _docName;
    // End property // Конечное свойство

signals:
    // Property //  Собственность
    void imageChanged();
    void imageOverlayChanged();
    void docNameChanged();
    // End property // Конечное свойство

public slots:
    // Property //  Собственность
    void setImage(QImage &image);
    void setImageOverlay(QImage &image);
    void setDocName(QString value);
    // End property // Конечное свойство

    int imageWidth();
    int imageHeight();

};

#endif // IMAGEREVIEWVM_H
