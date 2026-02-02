#ifndef LIMIT_VM_H
#define LIMIT_VM_H

#include <QObject>
#include "Model/limit_table_model.h"


class LimitTabVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(limit_table_model *tableDataModel READ tableDataModel WRITE setTableDataModel NOTIFY tableDataModelChanged FINAL)


public:
    explicit LimitTabVM(QObject *parent = nullptr);

    inline static LimitTabVM* GetInstance() {

        if (m_pInstance.isNull())
            m_pInstance.reset(new LimitTabVM());

        return m_pInstance.data();
    }

    limit_table_model *tableDataModel() const;
    void setTableDataModel(limit_table_model *newTableDataModel);


    void SaveDataToFile();
    void LoadDataFromFile();


private:
    limit_table_model* m_tableDataModel;
    static QScopedPointer<LimitTabVM> m_pInstance;

public slots:
    void saveDataTableSlot();
signals:
    void tableDataModelChanged();
    void loadRecipe_Signal();
};

#endif // LIMIT_VM_H
