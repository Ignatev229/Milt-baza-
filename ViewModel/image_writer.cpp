#include "image_writer.h"

ImageWriter::ImageWriter(QQuickItem *parent): QQuickPaintedItem(parent), image{}
{
    // UpdateDisconnectImage();
}
ImageWriter::~ImageWriter()
{

}

void ImageWriter::UpdateDisconnectImage()
{
    this->image = QImage(QString(":/Resources/NoneCamera.png"));
}

// Get property // Получить  Собственность
int ImageWriter::ui_width()
{
    return _ui_width;
}

int ImageWriter::ui_height()
{
    return _ui_height;
}

int ImageWriter::ui_top()
{
    return _ui_top;
}

int ImageWriter::ui_left()
{
    return _ui_left;
}

int ImageWriter::img_width()
{
    return _img_width;
}

int ImageWriter::img_height()
{
    return _img_height;
}


// end // конец

// Set property // Установить свойство
void ImageWriter::setImage(QImage &_image)
{
    this->image = _image;
    this->update();
    emit updateSourceImage();
}
void ImageWriter::setUi_width(int value)
{
    if (_ui_width != value){
        _ui_width = value;
        emit ui_widthChanged();
    }
}
void ImageWriter::setUi_height(int value)
{
    if (_ui_height != value){
        _ui_height = value;
        emit ui_heightChanged();
    }
}
void ImageWriter::setUi_top(int value)
{
    if (_ui_top!= value){
        _ui_top = value;
        emit ui_topChanged();
    }
}

void ImageWriter::setUi_left(int value)
{
    if (_ui_left != value){
        _ui_left = value;
        emit ui_leftChanged();
    }
}
void ImageWriter::setImg_width(int value)
{
    if (_img_width != value){
        _img_width = value;
        emit img_widthChanged();
    }
}
void ImageWriter::setImg_height(int value)
{
    if (_img_height != value){
        _img_height = value;
        emit img_heightChanged();
    }
}

//end // конец


void ImageWriter::paint(QPainter *painter)
{
    QRectF bouding_rect = boundingRect();
    //check null image //проверьте нулевое изображение
    if(this->image.isNull()){
        UpdateDisconnectImage();
    }

//    QPainter paint(&this->image);
//    paint.begin(&this->image);
//    paint.setPen(Qt::blue);
//    paint.drawLine(150,150,100,100);
//    paint.end();

    // scale image fit square // масштабировать изображение по квадрату
    QImage scaled = this->image.scaled(bouding_rect.width(), bouding_rect.height(), Qt::KeepAspectRatio);
    // Get center image // Получить центральное изображение
    QPointF center = bouding_rect.center() - scaled.rect().center();
    // Check center //  Проверка центра
    if(center.x() < 0)
        center.setX(0);
    if(center.y() < 0)
        center.setY(0);
    // Binding top, left to ui // Привязка сверху, слева к пользовательскому интерфейсу
    setUi_width(scaled.width());
    setUi_height(scaled.height());
    setUi_left(center.x());
    setUi_top(center.y());
    setImg_width(image.width());
    setImg_height(image.height());

    // Paint image to ui // Перенести изображение в пользовательский интерфейс
    //painter->drawImage(center, scaled);
    painter->drawPixmap(center, QPixmap::fromImage(scaled));
}




