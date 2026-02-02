#ifndef REVIEWVM_H
#define REVIEWVM_H

#include <QObject>

#include "single_review_vm.h"
#include "../../Script/Define/struct_def.h"
#include "image_review_vm.h"

class ReviewVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<SingleReviewVM*> listSingleReviewVM READ listSingleReviewVM WRITE setListSingleReviewVM NOTIFY listSingleReviewVMChanged FINAL)
    Q_PROPERTY(ImageReviewVM* imageReviewVM READ imageReviewVM WRITE setImageReviewVM NOTIFY imageReviewVMChanged FINAL)
    Q_PROPERTY(int pageNumber READ pageNumber WRITE setPageNumber NOTIFY pageNumberChanged FINAL)
    Q_PROPERTY(int trackChoosedIndex READ trackChoosedIndex WRITE setTrackChoosedIndex NOTIFY trackChoosedIndexChanged FINAL)


public:
    explicit ReviewVM(QObject *parent = nullptr);
    ~ReviewVM();


    // property //  Собственность
    QList<SingleReviewVM*> listSingleReviewVM();
    ImageReviewVM *imageReviewVM();
    int pageNumber();
    int trackChoosedIndex(); // -1,0,1,2,3
    // end // конец


    Q_INVOKABLE QObject* singleReviewListAt(int index) const;
    void AddSingleReviewData(QString info, QHash<TRACK_INDEX, QString> &imagePaths, QHash<TRACK_INDEX, QImage> &images);
    void ClearSingleReviewData();
    void SetTotalPageNumber();


    QList<SingleReviewData> listSingleReviewData;



private:

    // property //  Собственность
    QList<SingleReviewVM*> _listSingleReviewVM;
    ImageReviewVM *_imageReviewVM;
    int _pageNumber;
    int _trackChoosedIndex;
    // end // конец

    int currentPageShowedIndex;
    // for choose doc overlay // для выбора оверлея документа
    int currentPageChoosedIndex;
    int currentSingleReviewChoosedIndex;
    int currentDocChoosedIndex; // 0->3

signals:

    // property //  Собственность
    void listSingleReviewVMChanged();
    void imageReviewVMChanged();
    void pageNumberChanged();
    void trackChoosedIndexChanged();

    // end // конец

public slots:

    // property //  Собственность
    void setListSingleReviewVM(QList<SingleReviewVM*> &value);
    void setImageReviewVM(ImageReviewVM* &);
    void setPageNumber(int);
    void setTrackChoosedIndex(int);
    // end // конец

    void reviewPageNumberChanged_Qml_Slot(int);
    void docChoosedChanged_Qml_Slot(int pageIndex, int trackIndex, int docIndex);

};

#endif // REVIEWVM_H
