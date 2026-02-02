#include "correction_vm.h"
#include "../master_app.h"

QScopedPointer<CorrectionVM> CorrectionVM::m_pInstance;

CorrectionVM::CorrectionVM(QObject *parent)
    : QObject{parent}
{

}

CorrectionVM::~CorrectionVM()
{

}

void CorrectionVM::Init(QObject *parent)
{
    m_pParentObject = reinterpret_cast<MasterApp*>(parent);
    currentDefectCorrection = BACKEND_RESULT::PASS;
    isWaitTableMoveComplete = false;

    connect(this, SIGNAL(sequenceLog_Signal(QString)), this, SLOT(sequenceLog_Slot(QString)));
    connect(this, SIGNAL(moveTable_Signal(double)), this, SLOT(moveTable_Slot(double)));
    connect(this, SIGNAL(moveTableHome_Signal()), this, SLOT(moveTableHome_Slot()));

}

void CorrectionVM::UpdateCurrentRecipeToCorrection()
{
    groupFinishDimensionInspect = EditRecipeVM::GetInstance()->groupFinishDimensionInspect;
    currentDefectChanged_Qml_Slot(currentDefectCorrection);
}

void CorrectionVM::UpdateCurrentDefectParameter(FinishDimensionInspect &vp)
{
    currentDefectParameter = QString("%1,%2,%3,%4")
                                .arg(vp.dimension)
                                .arg(vp.parameter1)
                                .arg(vp.parameter2)
                                .arg(vp.parameter3);
}

void CorrectionVM::sequenceLog_Slot(QString info)
{
    PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Correction", info, tr(""));
}

void CorrectionVM::moveTable_Slot(double dValue)
{
    MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_TABLE_ELEVATION_VALUE, dValue);
    QThread::msleep(60);
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_ELEVATION_COMMAND_GO, true);
}

void CorrectionVM::moveTableHome_Slot()
{
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_ELEVATION_COMMAND_HOME, true);
    QThread::msleep(60);
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_ELEVATION_COMMAND_HOME, true);
}

void CorrectionVM::currentDefectChanged_Qml_Slot(int index)
{
    qDebug() << "[CorrectionVM]" << "Current defect index: " << index;

    // update vision to UI
    currentDefectCorrection = (BACKEND_RESULT)index;
    double min = 0, max = 0, goal = 0, distanceBottomRegion = 0, heightRegion = 0;
    if(index == BACKEND_RESULT::F_DIMENSION)
    {
        goal = groupFinishDimensionInspect.dimensionF.dimension;
        min = goal - groupFinishDimensionInspect.dimensionF.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionF.maxTolerance;
        distanceBottomRegion = groupFinishDimensionInspect.dimensionF.parameter1;
        heightRegion = groupFinishDimensionInspect.dimensionF.parameter1;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionF);
    }
    else if(index == BACKEND_RESULT::A_DIMENSION)
    {
        goal = groupFinishDimensionInspect.dimensionA.dimension;
        min = goal - groupFinishDimensionInspect.dimensionA.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionA.maxTolerance;
        distanceBottomRegion = groupFinishDimensionInspect.dimensionA.parameter1;
        heightRegion = groupFinishDimensionInspect.dimensionA.parameter1;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionA);
    }
    else if(index == BACKEND_RESULT::T_DIMENSION)
    {
        goal = groupFinishDimensionInspect.dimensionT.dimension;
        min = goal - groupFinishDimensionInspect.dimensionT.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionT.maxTolerance;
        distanceBottomRegion = groupFinishDimensionInspect.dimensionT.parameter1;
        heightRegion = groupFinishDimensionInspect.dimensionT.parameter2;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionT);
    }
    else if(index == BACKEND_RESULT::E_DIMENSION)
    {
        goal = groupFinishDimensionInspect.dimensionE.dimension;
        min = goal - groupFinishDimensionInspect.dimensionE.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionE.maxTolerance;
        distanceBottomRegion = groupFinishDimensionInspect.dimensionE.parameter1;
        heightRegion = groupFinishDimensionInspect.dimensionE.parameter2;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionE);
    }
    else if(index == BACKEND_RESULT::D_DIMENSION)
    {
        goal = groupFinishDimensionInspect.dimensionD.dimension;
        min = goal - groupFinishDimensionInspect.dimensionD.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionD.maxTolerance;
        distanceBottomRegion = groupFinishDimensionInspect.dimensionD.parameter1;
        heightRegion = groupFinishDimensionInspect.dimensionD.parameter3; // special
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionD);
    }
    else if(index == BACKEND_RESULT::B_DIMENSION)
    {
        goal = groupFinishDimensionInspect.dimensionB.dimension;
        min = goal - groupFinishDimensionInspect.dimensionB.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionB.maxTolerance;
        distanceBottomRegion = groupFinishDimensionInspect.dimensionB.parameter1;
        heightRegion = groupFinishDimensionInspect.dimensionB.parameter2;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionB);
    }
    else if(index == BACKEND_RESULT::S_DIMENSION)
    {
        goal = groupFinishDimensionInspect.dimensionS1.dimension;
        min = goal - groupFinishDimensionInspect.dimensionS1.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionS1.maxTolerance;
        distanceBottomRegion = groupFinishDimensionInspect.dimensionS1.parameter1;
        heightRegion = groupFinishDimensionInspect.dimensionS1.parameter2;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionS1);
    }
    else if(index == BACKEND_RESULT::H_DIMENSION)
    {
        // special
        goal = groupFinishDimensionInspect.dimensionH.dimension;
        min = groupFinishDimensionInspect.dimensionH.parameter2 - groupFinishDimensionInspect.dimensionH.minTolerance;
        max = groupFinishDimensionInspect.dimensionH.parameter2 + groupFinishDimensionInspect.dimensionH.maxTolerance;
        distanceBottomRegion = groupFinishDimensionInspect.dimensionH.parameter2;
        heightRegion = groupFinishDimensionInspect.dimensionH.parameter1;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionH);
    }
    else if(index == BACKEND_RESULT::LUGT_DIMENSION)
    {
        goal = groupFinishDimensionInspect.dimensionLugT.dimension;
        min = goal - groupFinishDimensionInspect.dimensionLugT.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionLugT.maxTolerance;
        distanceBottomRegion = groupFinishDimensionInspect.dimensionLugT.parameter1;
        heightRegion = groupFinishDimensionInspect.dimensionLugT.parameter2;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionLugT);
    }
    else if(index == BACKEND_RESULT::LUGT1_DIMENSION)
    {
        goal = groupFinishDimensionInspect.dimensionLugT1.dimension;
        min = goal - groupFinishDimensionInspect.dimensionLugT1.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionLugT1.maxTolerance;
        distanceBottomRegion = groupFinishDimensionInspect.dimensionLugT1.parameter1;
        heightRegion = groupFinishDimensionInspect.dimensionLugT1.parameter2;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionLugT1);
    }
    else if(index == BACKEND_RESULT::D_ANGLE_DIMENSION)
    {
        goal = groupFinishDimensionInspect.dimensionDAngle.dimension;
        min = goal - groupFinishDimensionInspect.dimensionDAngle.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionDAngle.maxTolerance;
        distanceBottomRegion = groupFinishDimensionInspect.dimensionDAngle.parameter1;
        heightRegion = groupFinishDimensionInspect.dimensionDAngle.parameter3; // special
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionDAngle);
    }
    else
    {
        return;
    }

    emit updateDataUI(min, max, goal, distanceBottomRegion, heightRegion);

}

void CorrectionVM::test_Qml_Slot(QList<int> defectIdx)
{
    qDebug() << "[CorrectionVM]" << "Test function index: " << defectIdx;

    QFuture<void> future = QtConcurrent::run([=]() {
        /*Code in this block will run in another thread*/

        try {
            // Move table to camera
            // send move to top pos
            double dValue = m_pParentObject->GetTablePositionNeedToMove(INSPECT_SEQUENCE_CAMERA_POSITION::TOP);
            emit moveTable_Signal(dValue);
            emit sequenceLog_Signal("Move Table to Top camera");

            // wait table move complete
            isWaitTableMoveComplete = true;
            int count = 500;
            while (isWaitTableMoveComplete && count > 0)
            {
                dValue = m_pParentObject->GetTablePositionNeedToMove(INSPECT_SEQUENCE_CAMERA_POSITION::TOP);
                if(m_pParentObject->scopedTableVM.data()->tableElevationValue() == dValue)
                {
                    emit sequenceLog_Signal("Move Table to Top camera complete");
                    break;
                }
                QThread::msleep(20);
                count--;
            }
            if(isWaitTableMoveComplete)
            {
                // call snap
                m_pParentObject->scopedMainHomeVM.data()->Snap(
                    m_pParentObject->GetTablePositionCamera(INSPECT_SEQUENCE_CAMERA_POSITION::TOP));

                // call inspect current defect selected
                // call correction inspection
                m_pParentObject->scopedMainHomeVM.data()->Inspect(BACKEND_FUNCTION::CORRECTION_FIRST_INSPECT);
            }

            // // move table to home
            // emit moveTableHome_Signal();
            // emit sequenceLog_Signal("Move Table to Home");
        }
        catch (...) {

        }

        emit closeWaitTableMoveComplete();
    });
}

void CorrectionVM::parameterChanged_Qml_Slot(double goal, double distanceBottomRegion, double heightRegion)
{
    qDebug() << "[CorrectionVM]" << "Parameter changed";

    //
    double min = 0, max = 0;
    if(currentDefectCorrection == BACKEND_RESULT::F_DIMENSION)
    {
        groupFinishDimensionInspect.dimensionF.dimension = goal;
        min = goal - groupFinishDimensionInspect.dimensionF.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionF.maxTolerance;
        groupFinishDimensionInspect.dimensionF.parameter1 = distanceBottomRegion;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionF);
    }
    else if(currentDefectCorrection == BACKEND_RESULT::A_DIMENSION)
    {
        groupFinishDimensionInspect.dimensionA.dimension = goal;
        min = goal - groupFinishDimensionInspect.dimensionA.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionA.maxTolerance;
        groupFinishDimensionInspect.dimensionA.parameter1 = distanceBottomRegion;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionA);
    }
    else if(currentDefectCorrection == BACKEND_RESULT::T_DIMENSION)
    {
        groupFinishDimensionInspect.dimensionT.dimension = goal;
        min = goal - groupFinishDimensionInspect.dimensionT.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionT.maxTolerance;
        groupFinishDimensionInspect.dimensionT.parameter1 = distanceBottomRegion;
        groupFinishDimensionInspect.dimensionT.parameter2 = heightRegion;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionT);
    }
    else if(currentDefectCorrection == BACKEND_RESULT::E_DIMENSION)
    {
        groupFinishDimensionInspect.dimensionE.dimension = goal;
        min = goal - groupFinishDimensionInspect.dimensionE.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionE.maxTolerance;
        groupFinishDimensionInspect.dimensionE.parameter1 = distanceBottomRegion;
        groupFinishDimensionInspect.dimensionE.parameter2 = heightRegion;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionE);
    }
    else if(currentDefectCorrection == BACKEND_RESULT::D_DIMENSION)
    {
        groupFinishDimensionInspect.dimensionD.dimension = goal;
        min = goal - groupFinishDimensionInspect.dimensionD.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionD.maxTolerance;
        groupFinishDimensionInspect.dimensionD.parameter1 = distanceBottomRegion;
        groupFinishDimensionInspect.dimensionD.parameter3 = heightRegion; // special
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionD);
    }
    else if(currentDefectCorrection == BACKEND_RESULT::B_DIMENSION)
    {
        groupFinishDimensionInspect.dimensionB.dimension = goal;
        min = goal - groupFinishDimensionInspect.dimensionB.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionB.maxTolerance;
        groupFinishDimensionInspect.dimensionB.parameter1 = distanceBottomRegion;
        groupFinishDimensionInspect.dimensionB.parameter2 = heightRegion;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionB);
    }
    else if(currentDefectCorrection == BACKEND_RESULT::S_DIMENSION)
    {
        groupFinishDimensionInspect.dimensionS1.dimension = goal;
        min = goal - groupFinishDimensionInspect.dimensionS1.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionS1.maxTolerance;
        groupFinishDimensionInspect.dimensionS1.parameter1 = distanceBottomRegion;
        groupFinishDimensionInspect.dimensionS1.parameter2 = heightRegion;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionS1);
    }
    else if(currentDefectCorrection == BACKEND_RESULT::H_DIMENSION)
    {
        groupFinishDimensionInspect.dimensionH.dimension = goal;
        groupFinishDimensionInspect.dimensionH.parameter2 = distanceBottomRegion;
        groupFinishDimensionInspect.dimensionH.parameter1 = heightRegion;
        min = groupFinishDimensionInspect.dimensionH.parameter2 - groupFinishDimensionInspect.dimensionH.minTolerance;
        max = groupFinishDimensionInspect.dimensionH.parameter2 + groupFinishDimensionInspect.dimensionH.maxTolerance;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionH);
    }
    else if(currentDefectCorrection == BACKEND_RESULT::LUGT_DIMENSION)
    {

        groupFinishDimensionInspect.dimensionLugT.dimension = goal;
        min = goal - groupFinishDimensionInspect.dimensionLugT.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionLugT.maxTolerance;
        groupFinishDimensionInspect.dimensionLugT.parameter1 = distanceBottomRegion;
        groupFinishDimensionInspect.dimensionLugT.parameter2 = heightRegion;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionLugT);
    }
    else if(currentDefectCorrection == BACKEND_RESULT::LUGT1_DIMENSION)
    {
        groupFinishDimensionInspect.dimensionLugT1.dimension = goal;
        min = goal - groupFinishDimensionInspect.dimensionLugT1.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionLugT1.maxTolerance;
        groupFinishDimensionInspect.dimensionLugT1.parameter1 = distanceBottomRegion;
        groupFinishDimensionInspect.dimensionLugT1.parameter2 = heightRegion;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionLugT1);
    }
    else if(currentDefectCorrection == BACKEND_RESULT::D_ANGLE_DIMENSION)
    {
        groupFinishDimensionInspect.dimensionDAngle.dimension = goal;
        min = goal - groupFinishDimensionInspect.dimensionDAngle.minTolerance;
        max = goal + groupFinishDimensionInspect.dimensionDAngle.maxTolerance;
        groupFinishDimensionInspect.dimensionDAngle.parameter1 = distanceBottomRegion;
        groupFinishDimensionInspect.dimensionDAngle.parameter3 = heightRegion;
        UpdateCurrentDefectParameter(groupFinishDimensionInspect.dimensionDAngle);
    }
    else
    {
        return;
    }

    emit updateDataUI(min, max, goal, distanceBottomRegion, heightRegion);
    // call inspect current defect selected
    // call correction inspection
    m_pParentObject->scopedMainHomeVM.data()->Inspect(BACKEND_FUNCTION::CORRECTION_INSPECT);
}

void CorrectionVM::saveSetting_Qml_Slot(bool isSave)
{
    qDebug() << "[CorrectionVM]" << "Save setting: " << isSave;

    if(isSave)
    {
        // update temp to vision param
        EditRecipeVM::GetInstance()->groupFinishDimensionInspect = groupFinishDimensionInspect;
        EditRecipeVM::GetInstance()->WriteVisionParam();

    }
    else
    {
        // update vision param to temp
        UpdateCurrentRecipeToCorrection();
    }
    moveTableHome_Slot();
    sequenceLog_Slot("Move Table to Home");

}

void CorrectionVM::cancelWaitTableMoveComplete()
{
    qDebug() << "[CorrectionVM]" << "Cancel move table to complete";
    isWaitTableMoveComplete = false;
    moveTableHome_Slot();
    sequenceLog_Slot("Move Table to Home");
}













