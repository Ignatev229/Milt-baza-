#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H

#include <QObject>
#include <QPainter>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include <QImage>


class ImageWriter: public QQuickPaintedItem
{
    Q_OBJECT
    // property zone // зона собственности
    Q_PROPERTY(QImage ui_image MEMBER image WRITE setImage)
    Q_PROPERTY(int ui_width READ ui_width WRITE setUi_width NOTIFY ui_widthChanged)
    Q_PROPERTY(int ui_height READ ui_height WRITE setUi_height NOTIFY ui_heightChanged)
    Q_PROPERTY(int ui_top READ ui_top WRITE setUi_top NOTIFY ui_topChanged)
    Q_PROPERTY(int ui_left READ ui_left WRITE setUi_left NOTIFY ui_leftChanged)
    Q_PROPERTY(int img_width READ img_width WRITE setImg_width NOTIFY img_widthChanged)
    Q_PROPERTY(int img_height READ img_height WRITE setImg_height NOTIFY img_heightChanged)

    // end // конец

public:
    ImageWriter(QQuickItem *parent = 0);
    ~ImageWriter();
    void UpdateDisconnectImage();


private:
    QImage image;

    //  property use in qml // использование свойств в qml
    int ui_width();
    int ui_height();
    int ui_top();
    int ui_left();
    int img_width();
    int img_height();
    // end // конец


    // variable property // свойство переменной
    int _ui_width;
    int _ui_height;
    int _ui_top;
    int _ui_left;
    int _img_width;
    int _img_height;
    //end // конец


    void paint(QPainter *painter) override;
    void setImage(QImage &image);

signals:
    // Notify property changed // Уведомить об изменении свойства
    void ui_widthChanged();
    void ui_heightChanged();
    void ui_topChanged();
    void ui_leftChanged();
    void img_widthChanged();
    void img_heightChanged();
    // end // конец


    void updateSourceImage();

public slots:
    // Set property zone // Установить зону собственности
    void setUi_width(int);
    void setUi_height(int);
    void setUi_top(int);
    void setUi_left(int);
    void setImg_width(int);
    void setImg_height(int);

    // end // конец

};

#endif // IMAGEWRITER_H
