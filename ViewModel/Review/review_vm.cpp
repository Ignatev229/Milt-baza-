#include "review_vm.h"

ReviewVM::ReviewVM(QObject *parent)
    : QObject{parent}
{

    QList<SingleReviewVM*> view;
    for (int i = 0; i < ConfigApplication::instance()->m_nReviewTrack; ++i)
    {
        view.append(new SingleReviewVM());
    }
    setListSingleReviewVM(view);

    ImageReviewVM *imageReview = new ImageReviewVM();
    setImageReviewVM(imageReview);


    SetTotalPageNumber();
    currentPageShowedIndex = 0; // page show in left // страница отображается слева
    currentPageChoosedIndex = 0; // page show in right // страница отображается справа
    currentSingleReviewChoosedIndex = 0; // new is 0 // новый равен 0
    currentDocChoosedIndex = 0; // 0->3
    reviewPageNumberChanged_Qml_Slot(0);
    setTrackChoosedIndex(-1); // not choosed // не выбран
}

ReviewVM::~ReviewVM()
{
    // not attempt do delete the new variable that binding to ui
    //for (int i = 0; i < ConfigApplication::instance()->m_nReviewTrack; ++i)
    //{
    //    delete _listSingleReviewVM[i];
    //}
    //delete imageReviewVM();
}

QList<SingleReviewVM *> ReviewVM::listSingleReviewVM()
{
    return _listSingleReviewVM;
}

ImageReviewVM* ReviewVM::imageReviewVM()
{
    return _imageReviewVM;
}

int ReviewVM::pageNumber()
{
    return _pageNumber;
}

int ReviewVM::trackChoosedIndex()
{
    return _trackChoosedIndex;
}

QObject *ReviewVM::singleReviewListAt(int index) const
{
    if (index<0 || index>= _listSingleReviewVM.size())
        return nullptr;
    return _listSingleReviewVM[index];
}

void ReviewVM::AddSingleReviewData(QString info, QHash<TRACK_INDEX, QString> &imagePaths, QHash<TRACK_INDEX, QImage> &images)
{
    SingleReviewData value;
    value.info = info;
    value.images.clear();
    value.imagePaths.clear();
    for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i) {
        value.images.append(images[(TRACK_INDEX)i]);
        value.imagePaths.append(imagePaths[(TRACK_INDEX)i]);
    }
    listSingleReviewData.insert(0, value);
    if(listSingleReviewData.length() > ConfigApplication::instance()->m_nMaxSingleReviewReloaded)
    {
        listSingleReviewData[ConfigApplication::instance()->m_nMaxSingleReviewReloaded].images.clear(); // release image to except overload
    }
    SetTotalPageNumber();
    // calculate page choosed //  Рассчитать выбранную страницу
    currentSingleReviewChoosedIndex++; // SingleReviewChoosed increase 1 // Для одного просмотра выберите увеличение на 1
    currentPageChoosedIndex = currentSingleReviewChoosedIndex/ConfigApplication::instance()->m_nReviewTrack;
    setTrackChoosedIndex(currentSingleReviewChoosedIndex%ConfigApplication::instance()->m_nReviewTrack);
    //
    reviewPageNumberChanged_Qml_Slot(currentPageShowedIndex);
}

void ReviewVM::ClearSingleReviewData()
{
    listSingleReviewData.clear();
}

void ReviewVM::SetTotalPageNumber()
{
    setPageNumber(int((listSingleReviewData.length() - 1)/ConfigApplication::instance()->m_nReviewTrack));
}

void ReviewVM::setListSingleReviewVM(QList<SingleReviewVM *> &value)
{
    if(_listSingleReviewVM != value)
    {
        _listSingleReviewVM = value;
        emit listSingleReviewVMChanged();
    }
}

void ReviewVM::setImageReviewVM(ImageReviewVM* &value)
{
    if(_imageReviewVM != value)
    {
        _imageReviewVM = value;
        emit imageReviewVMChanged();
    }
}

void ReviewVM::setPageNumber(int value)
{
    if(_pageNumber != value)
    {
        _pageNumber = value;
        emit pageNumberChanged();
    }
}

void ReviewVM::setTrackChoosedIndex(int value)
{
    if(_trackChoosedIndex != value)
    {
        _trackChoosedIndex = value;
        emit trackChoosedIndexChanged();
    }
}

void ReviewVM::reviewPageNumberChanged_Qml_Slot(int page)
{
    currentPageShowedIndex = page;
    if(currentPageChoosedIndex == page)
    {
        setTrackChoosedIndex(currentSingleReviewChoosedIndex%ConfigApplication::instance()->m_nReviewTrack); // not choosed // не выбран
    }
    else
    {
        setTrackChoosedIndex(-1); // not choosed // не выбран
    }
    int start = (page)*ConfigApplication::instance()->m_nReviewTrack;
    int index;
    for (int i = 0; i < ConfigApplication::instance()->m_nReviewTrack; ++i)
    {
        index = start + i;
        if(index < listSingleReviewData.length())
        {

            if(listSingleReviewData[index].images.length() == ConfigApplication::instance()->m_nReviewDoc)
            {
                listSingleReviewVM()[i]->setListImage(listSingleReviewData[index].images);
                listSingleReviewVM()[i]->setInfo(listSingleReviewData[index].info);
            }
            else
            {
                // read image // считывание изображения
                QList<QImage> listImage;
                for (int j = 0; j < ConfigApplication::instance()->m_nReviewDoc; ++j)
                {
                    QImage image(listSingleReviewData[index].imagePaths[j]);
                    listImage.append(image);
                }
                listSingleReviewVM()[i]->setListImage(listImage);
                listSingleReviewVM()[i]->setInfo(listSingleReviewData[index].info);
            }
        }
        else
        {
            listSingleReviewVM()[i]->ClearSingleReview();
        }
    }
}

void ReviewVM::docChoosedChanged_Qml_Slot(int pageIndex, int trackIndex, int docIndex)
{
    // update index // обновить индекс
    currentPageChoosedIndex = pageIndex;
    currentSingleReviewChoosedIndex = currentPageChoosedIndex * ConfigApplication::instance()->m_nReviewTrack + trackIndex; // new is 0
    currentDocChoosedIndex = docIndex;

    // update image and info // обновить изображение и информацию
    QImage image = listSingleReviewVM()[trackIndex]->listImage()[docIndex].copy();
    imageReviewVM()->setImage(image);
    imageReviewVM()->setImageOverlay(image);
    QString info = QString::number(listSingleReviewData.length() - currentSingleReviewChoosedIndex) + "/" + QString::number(docIndex + 1);
    imageReviewVM()->setDocName(info);

    // update choose overlay // обновить выберите  Оверлей
    setTrackChoosedIndex(trackIndex);
}
