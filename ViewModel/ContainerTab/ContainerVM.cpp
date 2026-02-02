#include "ContainerVM.h"
#include <qfile.h>
#include <QTextStream>
#include "Script/Config/config_application.h"
ContainerVM::ContainerVM(QObject *parent)
    : QObject{parent}
{
    // Dummy data // Фиктивные данные
    m_vectorListContainerData;
    m_vectorListContainerData.append(containerItem(m_vectorListContainerData.count(), tr("Average"), 305.82, 577.52, 24.85, 24.97, 27.18, 27.33));
    m_vectorListContainerData.append(containerItem(m_vectorListContainerData.count(), "10", 305.82, 577.52, 24.85, 24.97, 27.18, 27.33));
    m_vectorListContainerData.append(containerItem(m_vectorListContainerData.count(), "10", 305.82, 577.52, 24.85, 24.97, 27.18, 27.33));
    m_vectorListContainerData.append(containerItem(m_vectorListContainerData.count(), "10", 305.82, 577.52, 24.85, 24.97, 27.18, 27.33));
    m_vectorListContainerData.append(containerItem(m_vectorListContainerData.count(), "25", 305.82, 577.52, 24.85, 24.97, 27.18, 27.33));
    m_vectorListContainerData.append(containerItem(m_vectorListContainerData.count(), "25", 305.82, 577.52, 24.85, 24.97, 27.18, 27.33));
    m_vectorListContainerData.append(containerItem(m_vectorListContainerData.count(), "25", 305.82, 577.52, 24.85, 24.97, 27.18, 27.33));
    m_vectorListContainerData.append(containerItem(m_vectorListContainerData.count(), "25", 305.82, 577.52, 24.85, 24.97, 27.18, 27.33));

}

void ContainerVM::PopulateData()
{
    for (auto const& e : m_vectorListContainerData)
    {

        emit addData(e.index, 
            e.item, 
            QString::asprintf("%.2f", e.height),
            QString::asprintf("%.2f", e.weight), 
            QString::asprintf("%.2f", e.eMin),
            QString::asprintf("%.2f", e.eMax),
            QString::asprintf("%.2f", e.tMin),
            QString::asprintf("%.2f", e.tMax));
    }
}

void ContainerVM::saveDataContainer()
{

    QString fileName = ConfigApplication::instance()->m_strConfigPath + "/DataContainer.csv";
    QFile f(fileName);
    if (f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&f);

        out << "Item" << "," << "Height" << "," << "Weight" << "," << "E (min.)" << "," << "E (max.)" << "," << "T (min.)" << "," << "T (max.)" << "\n";
        
        for (const auto& infor : m_vectorListContainerData)
        {
            out << infor.item << ",";
            out << infor.height << ",";
            out << infor.weight << ",";
            out << infor.eMin << ",";
            out << infor.eMax << ",";
            out << infor.tMin << ",";
            out << infor.tMin << ",";
            out << "\n";
        }

        f.close();
    }
}

void ContainerVM::loadCompleted()
{
    PopulateData();
}
