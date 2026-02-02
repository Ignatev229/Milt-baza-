#ifndef SingleReviewVM_H
#define SingleReviewVM_H

#include <QObject>
#include <QImage>
#include "../../Script/Config/config_application.h"

class SingleReviewVM : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QImage> listImage READ listImage WRITE setListImage NOTIFY listImageChanged FINAL)
    Q_PROPERTY(QString info READ info WRITE setInfo NOTIFY infoChanged FINAL)


public:
    explicit SingleReviewVM(QObject *parent = nullptr);
    ~SingleReviewVM();

    //
    QList<QImage> listImage();
    QString info();
    //
    Q_INVOKABLE QImage listImageListAt(int index) const;


    void UpdateImage(QImage &image, int docIndex);
    void UpdateAllImage(QList<QImage> &images);
    void ClearSingleReview();
private:
    QList<QImage> _listImage;
    QString _info;

    QImage defaultImage;

signals:
    //
    void listImageChanged();
    void infoChanged();


public slots:
    //
    void setListImage(QList<QImage> &value);
    void setInfo(QString);


};

#endif // SingleReviewVM_H
