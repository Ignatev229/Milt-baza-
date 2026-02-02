#include "statistics_vm.h"

StatisticsVM::StatisticsVM(QObject *parent)
    : QObject{parent}
{
    mItems.clear();
}
QVector<StatisticsItem> StatisticsVM::items() const
{
    return mItems;
}

void StatisticsVM::InitStatisticsTable()
{
    removeCompletedItems();
    StatisticsItem item1("Total Inspection", tr("Total Inspection"), 0);
    appendItem(item1);
    StatisticsItem item2("Total Fail", tr("Total Fail"), 0);
    appendItem(item2);
    // -1 process error
    for (int i = BACKEND_RESULT::PROCESS_ERROR; i < BACKEND_RESULT::TOTAL_DEFECT; ++i)
    {
        StatisticsItem item(ConfigApplication::instance()->ConvertDefectCodeToString((BACKEND_RESULT)i),
                            ConvertDefectCodeToStringTranslate((BACKEND_RESULT)i),
                            0);
        appendItem(item);
    }

    setYeilPass(100);
}


void StatisticsVM::ResetStatisticsTable()
{
    for(int i = 0; i < items().length(); i++)
    {
        auto& item = mItems[i];
        item.value = 0;
        emit dataContexDataChangedSignal(i);
    }
    setYeilPass(100);
}

void StatisticsVM::UpdateStatisticsTable(BACKEND_RESULT defectCode)
{
    if(items().length() == 0)
    {
        InitStatisticsTable();
        return;
    }
    // update total //  Обновить  Итого
    auto& item = mItems[0];
    item.value++;
    emit dataContexDataChangedSignal(0);

    // update defect //  Обновить дефект
    int index = defectCode + DEFECT_START_INDEX;
    auto& item1 = mItems[index];
    item1.value++;
    emit dataContexDataChangedSignal(index);
    // update fail //  Обновление завершилось неудачей
    if(defectCode != BACKEND_RESULT::PASS && defectCode != BACKEND_RESULT::PROCESS_ERROR)
    {
        auto& item2 = mItems[1];
        item2.value++;
        emit dataContexDataChangedSignal(1);
    }

    // update yield // обновить доходность
    if(mItems[0].value > 0)
    {
        double yield = QString::number((1-mItems[1].value*1.0/mItems[0].value)*100, 'f', 2).toDouble();
        setYeilPass(yield);
    }
}

bool StatisticsVM::setItemAt(int index, const StatisticsItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    removeItems(index);
    insertItem(index, item);
    return true;
}

int StatisticsVM::getLength()
{
    return mItems.size();
}

double StatisticsVM::yieldPass()
{
    return _yieldPass;
}

void StatisticsVM::appendItem(StatisticsItem &item)
{
    emit preItemAppended();
    mItems.append(item);
    emit postItemAppended();
    return;
}

void StatisticsVM::insertItem(int index, StatisticsItem item)
{
    emit preItemInserted(index);
    mItems.insert(index, item);
    emit postItemInserted();
    return;
}

void StatisticsVM::removeItems(int index)
{
    if (index < 0 || index >= mItems.size())
        return;
    emit preItemRemoved(index);
    mItems.removeAt(index);
    emit postItemRemoved();
}

void StatisticsVM::removeCompletedItems()
{
    while(mItems.size() > 0){
        for (int i = 0; i < mItems.size(); i++) {
            emit preItemRemoved(i);
            mItems.removeAt(i);
            emit postItemRemoved();
        }
    }
    return;
}

void StatisticsVM::resetStatistics_Qml_Slot()
{
    qDebug() << "[StatisticsVM]" << "Reset statistics";
    ResetStatisticsTable();
}

void StatisticsVM::setYeilPass(double value)
{
    if(_yieldPass != value)
    {
        _yieldPass = value;
        emit yieldPassChanged();
    }
}


QString StatisticsVM::ConvertDefectCodeToStringTranslate(BACKEND_RESULT value)
{
    if(value == BACKEND_RESULT::PROCESS_ERROR)
    {
        return tr("Process Error");
    }
    else if(value == BACKEND_RESULT::PASS)
    {
        return tr("Pass");
    }
    else if(value == BACKEND_RESULT::HEIGHT)
    {
        return tr("Height");
    }
    else if(value == BACKEND_RESULT::WEIGHT)
    {
        return tr("Weight");
    }
    else if(value == BACKEND_RESULT::NON_ROUND_SHAPE)
    {
        return tr("Non-round Shape");
    }
    else if(value == BACKEND_RESULT::BODYR_DIMENSION)
    {
        return tr("BodyR Dimension");
    }
    else if(value == BACKEND_RESULT::LEAN)
    {
        return tr("Lean");
    }
    else if(value == BACKEND_RESULT::TILT)
    {
        return tr("Tilt");
    }
    else if(value == BACKEND_RESULT::F_DIMENSION)
    {
        return tr("F Dimension");
    }
    else if(value == BACKEND_RESULT::A_DIMENSION)
    {
        return tr("A Dimension");
    }
    else if(value == BACKEND_RESULT::T_DIMENSION)
    {
        return tr("T Dimension");
    }
    else if(value == BACKEND_RESULT::E_DIMENSION)
    {
        return tr("E Dimension");
    }
    else if(value == BACKEND_RESULT::D_DIMENSION)
    {
        return tr("D Dimension");
    }
    else if(value == BACKEND_RESULT::B_DIMENSION)
    {
        return tr("B Dimension");
    }
    else if(value == BACKEND_RESULT::S_DIMENSION)
    {
        return tr("S Dimension");
    }
    else if(value == BACKEND_RESULT::H_DIMENSION)
    {
        return tr("H Dimension");
    }
    else if(value == BACKEND_RESULT::LUGT_DIMENSION)
    {
        return tr("LugT Dimension");
    }
    else if(value == BACKEND_RESULT::LUGT1_DIMENSION)
    {
        return tr("LugT1 Dimension");
    }
    else if(value == BACKEND_RESULT::D_ANGLE_DIMENSION)
    {
        return tr("D Angle");
    }
    else if(value == BACKEND_RESULT::FLANGE_DIMENSION)
    {
        return tr("Flange Dimension");
    }
    else if(value == BACKEND_RESULT::KNOCKOUT_DIMENSION)
    {
        return tr("Knockout Dimension");
    }
    else if(value == BACKEND_RESULT::PUSHUP_DIMENSION)
    {
        return tr("Pushup Dimension");
    }
    else if(value == BACKEND_RESULT::INSIDE_NECK)
    {
        return tr("Inside Neck");
    }
    else if(value == BACKEND_RESULT::WALL_THICKNESS)
    {
        return tr("Wall Thickness");
    }
    else if(value == BACKEND_RESULT::CODE_NUMBER)
    {
        return tr("Code Number");
    }
    // else if(value == BACKEND_RESULT::SEAM)
    // {
    //     return tr("Seam");
    // }
    return "";
}
