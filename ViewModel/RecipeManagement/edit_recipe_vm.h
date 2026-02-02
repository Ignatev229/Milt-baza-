#ifndef EDIT_RECIPE_VM_H
#define EDIT_RECIPE_VM_H

#include <QObject>
#include <QVariant>
#include <QDebug>

#include "vision_parameters.h"
#include "../../Script/Config/config_application.h"

struct VisionParamItem
{
    VisionParamItem(QString _groupName, QString _name, QString _type,
                    QVariant _minValue, QVariant _maxValue, QString _description)
        : groupName(_groupName)
        , name(_name)
        , type(_type)
        , minValue(_minValue)
        , maxValue(_maxValue)
        , description(_description)
    {
    }

    VisionParamItem()
    {
    }

    // name of group // название группы
    QString groupName;
    // name of variable // имя переменной
    QString name;
    // type of variable // тип переменной
    QString type;
    // value of variable // значение переменной
    QVariant minValue;
    // max value of variable // максимальное значение переменной
    QVariant maxValue;
    // description of group // описание группы
    QString description;


};


class EditRecipeVM : public QObject
{
    Q_OBJECT
public:
    explicit EditRecipeVM(QObject *parent = nullptr);
    virtual ~EditRecipeVM();

    inline static EditRecipeVM* GetInstance() {

        if (m_pInstance.isNull())
            m_pInstance.reset(new EditRecipeVM());

        return m_pInstance.data();
    }
    void ResetDefaultParameter();
    void LoadRecipe();
    void UpdateVisionParamToUI();
    void ReadVisionParam();
    void WriteVisionParam();
    void CreateDefaultValidationRecipe();

    void CalculateLiftingMechanismPos();

    BottleDiameter bottleDiameter;
    HeightInspect heightInspect;
    WeightInspect weightInspect;
    NonRoundShapeInspect noneRoundShapeInspect;
    BodyRInspect bodyRInspect;
    LeanInspect leanInspect;
    // BentNeckInspect bentNeckInspect;
    TiltInspect tiltInspect;
    GroupFinishDimensionInspect groupFinishDimensionInspect;
    FlangeInspect flangeInspect;
    KnockoutInspect knockoutInspect;
    PushupBodyInspect pushupBodyInspect;
    InsideNeckInspect insideNeckInspect;
    WallThicknessInspect wallThicknessInspect;
    NumberCodeDecode numberCodeDecode;
    // SeamInspect seamInspect;

private:
    static QScopedPointer<EditRecipeVM> m_pInstance;

protected:

public slots:
    void saveVisionParam_Slot(QList<QList<QVariant>>);

signals:
    void updateVisionParamToUI_Signal(QList<QList<QVariant>>);
    void editRecipe_Signal();
    void changeLanguage_Signal();

};

#endif // EDIT_RECIPE_VM_H
