#ifndef VISION_PARAMETERS_H
#define VISION_PARAMETERS_H


#include <QVariant>
#include <QDebug>

#include "../../Script/Define/struct_def.h"

#define VAR_TO_STRING(var) (#var)


class VisonParamUtlity
{
public:
    static QString ConvertHeaderFormat(QString input)
    {
        #ifdef Q_OS_WIN
        return input;
        #elif defined(Q_OS_LINUX)
        input.replace(0, 2, "class ");
        return input;
        #endif
    }
};



class BottleDiameter
{
public:
    BottleDiameter(double _diameter)
        : diameter(_diameter)
    {
    }

    BottleDiameter()
    {
        ResetDefaulValues();
    }

public:
    double diameter;

    QList<QVariant> getValues()
    {
        return QList<QVariant> {diameter};
    }

    void SetValues(QList<QVariant> data)
    {
        int subIndex = -1;
        diameter = data[++subIndex].toDouble();
    }

    void ResetDefaulValues()
    {
        diameter = 80;
    }


    void ReadParam(QHash<QString, QVariant> hashValues)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        QString key;

        key = QString("%1 :: %2")
            .arg(header)
            .arg(VAR_TO_STRING(diameter));
        diameter = hashValues.contains(key) ? hashValues[key].toDouble() : diameter;
    }

    void WriteParam(QTextStream &stream)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                    .arg(VAR_TO_STRING(diameter))
                    .arg(diameter);
        stream << "\n";
    }


};

class HeightInspect
{
public:
    HeightInspect(bool _enable, double _height, double _minTolerance, double _maxTolerance)
        : enable(_enable)
        , height(_height)
        , minTolerance(_minTolerance)
        , maxTolerance(_maxTolerance)
    {
    }

    HeightInspect()
    {
        ResetDefaulValues();
    }

public:
    bool enable;
    double height;
    double minTolerance;
    double maxTolerance;
    QHash<INSPECT_SEQUENCE_CAMERA_POSITION, double> liftingMechanismPos;

    QList<QVariant> getValues()
    {
        // UI
        return QList<QVariant> {enable, height, minTolerance, maxTolerance};
    }

    void SetValues(QList<QVariant> data)
    {
        // UI
        int subIndex = -1;
        enable = data[++subIndex].toBool();
        height = data[++subIndex].toDouble();
        minTolerance = data[++subIndex].toDouble();
        maxTolerance = data[++subIndex].toDouble();
    }

    void ResetDefaulValues()
    {
        //
        enable = true;
        height = 197.5;
        minTolerance = 1.5;
        maxTolerance = 1.5;
        // for (int i = 0; i < TRACK_INDEX::TRACK_COUNT; ++i) {
        //     liftingMechanismPos[(TRACK_INDEX)i] = 0;
        // }
    }

    void ReadParam(QHash<QString, QVariant> hashValues)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        QString key;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(enable));
        enable = hashValues.contains(key) ? hashValues[key].toBool() : enable;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(height));
        height = hashValues.contains(key) ? hashValues[key].toDouble() : height;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minTolerance));
        minTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxTolerance));
        maxTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxTolerance;

        // for (int i = 0; i < TRACK_INDEX::TRACK_COUNT; ++i) {
        //     key = QString("%1 :: liftingMechanismPos%2")
        //               .arg(header)
        //               .arg(i+1);
        //     liftingMechanismPos[(TRACK_INDEX)i] = hashValues.contains(key) ? hashValues[key].toDouble() : liftingMechanismPos[(TRACK_INDEX)i];
        // }
    }

    void WriteParam(QTextStream &stream)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(enable))
                      .arg(enable);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(height))
                      .arg(height);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minTolerance))
                      .arg(minTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxTolerance))
                      .arg(maxTolerance);
        // for (int i = 0; i < TRACK_INDEX::TRACK_COUNT; ++i) {
        //     stream << QString("liftingMechanismPos%1=%2\n")
        //                   .arg(i+1)
        //                   .arg(liftingMechanismPos[(TRACK_INDEX)i]);
        // }
        stream << "\n";
    }
};

class WeightInspect
{
public:
    WeightInspect(bool _enable, double _weight, double _minTolerance, double _maxTolerance)
        : enable(_enable)
        , weight(_weight)
        , minTolerance(_minTolerance)
        , maxTolerance(_maxTolerance)
    {
    }

    WeightInspect()
    {
        ResetDefaulValues();
    }

public:
    bool enable;
    double weight;
    double minTolerance;
    double maxTolerance;

    QList<QVariant> getValues()
    {
        return QList<QVariant> {enable, weight, minTolerance, maxTolerance};
    }

    void SetValues(QList<QVariant> data)
    {
        int subIndex = -1;
        enable = data[++subIndex].toBool();
        weight = data[++subIndex].toDouble();
        minTolerance = data[++subIndex].toDouble();
        maxTolerance = data[++subIndex].toDouble();
    }

    void ResetDefaulValues()
    {
        enable = true;
        weight = 355;
        minTolerance = 10;
        maxTolerance = 10;
    }

    void ReadParam(QHash<QString, QVariant> hashValues)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        QString key;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(enable));
        enable = hashValues.contains(key) ? hashValues[key].toBool() : enable;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(weight));
        weight = hashValues.contains(key) ? hashValues[key].toDouble() : weight;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minTolerance));
        minTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxTolerance));
        maxTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxTolerance;
    }

    void WriteParam(QTextStream &stream)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(enable))
                      .arg(enable);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(weight))
                      .arg(weight);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minTolerance))
                      .arg(minTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxTolerance))
                      .arg(maxTolerance);
        stream << "\n";
    }
};

class NonRoundShapeInspectItem
{
public:
    NonRoundShapeInspectItem()
    {
        ResetDefaulValues();
    }

public:

    double rectParameter;
    double rectShrt;
    double minRectShrtTolerance;
    double maxRectShrtTolerance;
    double rectLong;
    double minRectLongTolerance;
    double maxRectLongTolerance;
    double rectDiag;
    double minRectDiagTolerance;
    double maxRectDiagTolerance;

    double sqrParameter;
    double sqrSide;
    double minSqrSideTolerance;
    double maxSqrSideTolerance;
    double sqrDiag;
    double minSqrDiagTolerance;
    double maxSqrDiagTolerance;

    double ovlParameter;
    double ovlShrt;
    double minOvlShrtTolerance;
    double maxOvlShrtTolerance;
    double ovlLong;
    double minOvlLongTolerance;
    double maxOvlLongTolerance;



    QList<QVariant> getValues()
    {
        return QList<QVariant> {
                               rectParameter, rectShrt, minRectShrtTolerance, maxRectShrtTolerance,
                               rectLong, minRectLongTolerance, maxRectLongTolerance,
                               rectDiag, minRectDiagTolerance, maxRectDiagTolerance,
                               sqrParameter, sqrSide, minSqrSideTolerance, maxSqrSideTolerance,
                               sqrDiag, minSqrDiagTolerance, maxSqrDiagTolerance,
                               ovlParameter, ovlShrt, minOvlShrtTolerance, maxOvlShrtTolerance,
                               ovlLong, minOvlLongTolerance, maxOvlLongTolerance};
    }

    void SetValues(QList<QVariant> data, int &subIndex)
    {
        rectParameter = data[++subIndex].toDouble();
        rectShrt = data[++subIndex].toDouble();
        minRectShrtTolerance = data[++subIndex].toDouble();
        maxRectShrtTolerance = data[++subIndex].toDouble();
        rectLong = data[++subIndex].toDouble();
        minRectLongTolerance = data[++subIndex].toDouble();
        maxRectLongTolerance = data[++subIndex].toDouble();
        rectDiag = data[++subIndex].toDouble();
        minRectDiagTolerance = data[++subIndex].toDouble();
        maxRectDiagTolerance = data[++subIndex].toDouble();

        sqrParameter = data[++subIndex].toDouble();
        sqrSide = data[++subIndex].toDouble();
        minSqrSideTolerance = data[++subIndex].toDouble();
        maxSqrSideTolerance = data[++subIndex].toDouble();
        sqrDiag = data[++subIndex].toDouble();
        minSqrDiagTolerance = data[++subIndex].toDouble();
        maxSqrDiagTolerance = data[++subIndex].toDouble();

        ovlParameter = data[++subIndex].toDouble();
        ovlShrt = data[++subIndex].toDouble();
        minOvlShrtTolerance = data[++subIndex].toDouble();
        maxOvlShrtTolerance = data[++subIndex].toDouble();
        ovlLong = data[++subIndex].toDouble();
        minOvlLongTolerance = data[++subIndex].toDouble();
        maxOvlLongTolerance = data[++subIndex].toDouble();
    }

    void ResetDefaulValues()
    {
        rectParameter = 200;
        rectShrt = 60;
        minRectShrtTolerance = 1.5;
        maxRectShrtTolerance = 1.5;
        rectLong = 60;
        minRectLongTolerance = 1.5;
        maxRectLongTolerance = 1.5;
        rectDiag = 60;
        minRectDiagTolerance = 1.5;
        maxRectDiagTolerance = 1.5;

        sqrParameter = 200;
        sqrSide = 60;
        minSqrSideTolerance = 1.5;
        maxSqrSideTolerance = 1.5;
        sqrDiag = 60;
        minSqrDiagTolerance = 1.5;
        maxSqrDiagTolerance = 1.5;

        ovlParameter = 200;
        ovlShrt = 60;
        minOvlShrtTolerance = 1.5;
        maxOvlShrtTolerance = 1.5;
        ovlLong = 60;
        minOvlLongTolerance = 1.5;
        maxOvlLongTolerance = 1.5;
    }

    void ReadParam(QString header, QHash<QString, QVariant> hashValues)
    {
        QString key;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(rectParameter));
        rectParameter = hashValues.contains(key) ? hashValues[key].toDouble() : rectParameter;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(rectShrt));
        rectShrt = hashValues.contains(key) ? hashValues[key].toDouble() : rectShrt;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minRectShrtTolerance));
        minRectShrtTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minRectShrtTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxRectShrtTolerance));
        maxRectShrtTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxRectShrtTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(rectLong));
        rectLong = hashValues.contains(key) ? hashValues[key].toDouble() : rectLong;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minRectLongTolerance));
        minRectLongTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minRectLongTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxRectLongTolerance));
        maxRectLongTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxRectLongTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(rectDiag));
        rectDiag = hashValues.contains(key) ? hashValues[key].toDouble() : rectDiag;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minRectDiagTolerance));
        minRectDiagTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minRectDiagTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxRectDiagTolerance));
        maxRectDiagTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxRectDiagTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(sqrParameter));
        sqrParameter = hashValues.contains(key) ? hashValues[key].toDouble() : sqrParameter;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(sqrSide));
        sqrSide = hashValues.contains(key) ? hashValues[key].toDouble() : sqrSide;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minSqrSideTolerance));
        minSqrSideTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minSqrSideTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxSqrSideTolerance));
        maxSqrSideTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxSqrSideTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(sqrDiag));
        sqrDiag = hashValues.contains(key) ? hashValues[key].toDouble() : sqrDiag;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minSqrDiagTolerance));
        minSqrDiagTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minSqrDiagTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxSqrDiagTolerance));
        maxSqrDiagTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxSqrDiagTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(ovlParameter));
        ovlParameter = hashValues.contains(key) ? hashValues[key].toDouble() : ovlParameter;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(ovlShrt));
        ovlShrt = hashValues.contains(key) ? hashValues[key].toDouble() : ovlShrt;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minOvlShrtTolerance));
        minOvlShrtTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minOvlShrtTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxOvlShrtTolerance));
        maxOvlShrtTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxOvlShrtTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(ovlLong));
        ovlLong = hashValues.contains(key) ? hashValues[key].toDouble() : ovlLong;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minOvlLongTolerance));
        minOvlLongTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minOvlLongTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxOvlLongTolerance));
        maxOvlLongTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxOvlLongTolerance;

    }

    void WriteParam(QString header, QTextStream &stream)
    {

        stream << QString("[%1]\n").arg(header);

        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(rectParameter))
                      .arg(rectParameter);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(rectShrt))
                      .arg(rectShrt);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minRectShrtTolerance))
                      .arg(minRectShrtTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxRectShrtTolerance))
                      .arg(maxRectShrtTolerance);

        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(rectLong))
                      .arg(rectLong);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minRectLongTolerance))
                      .arg(minRectLongTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxRectLongTolerance))
                      .arg(maxRectLongTolerance);

        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(rectDiag))
                      .arg(rectDiag);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minRectDiagTolerance))
                      .arg(minRectDiagTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxRectDiagTolerance))
                      .arg(maxRectDiagTolerance);

        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(sqrParameter))
                      .arg(sqrParameter);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(sqrSide))
                      .arg(sqrSide);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minSqrSideTolerance))
                      .arg(minSqrSideTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxSqrSideTolerance))
                      .arg(maxSqrSideTolerance);

        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(sqrDiag))
                      .arg(sqrDiag);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minSqrDiagTolerance))
                      .arg(minSqrDiagTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxSqrDiagTolerance))
                      .arg(maxSqrDiagTolerance);


        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(ovlParameter))
                      .arg(ovlParameter);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(ovlShrt))
                      .arg(ovlShrt);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minOvlShrtTolerance))
                      .arg(minOvlShrtTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxOvlShrtTolerance))
                      .arg(maxOvlShrtTolerance);

        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(ovlLong))
                      .arg(ovlLong);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minOvlLongTolerance))
                      .arg(minOvlLongTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxOvlLongTolerance))
                      .arg(maxOvlLongTolerance);

        stream << "\n";
    }
};

class NonRoundShapeInspect
{
public:
    NonRoundShapeInspect()
    {
        maxNumberDimension = 8;
        for (int i = 0; i < maxNumberDimension; ++i) {
            dimensions.append(NonRoundShapeInspectItem());
        }
        ResetDefaulValues();
    }

public:
    bool enable;
    int shape;
    int numberDimension;
    int maxNumberDimension;

    QList<NonRoundShapeInspectItem> dimensions;



    QList<QVariant> getValues()
    {
        QList<QVariant> values = {enable, shape, numberDimension};
        for (int i = 0; i < dimensions.count(); ++i) {
            values.append(dimensions[i].getValues());
        }
        return values;
    }

    void SetValues(QList<QVariant> data)
    {
        int subIndex = -1;
        enable = data[++subIndex].toBool();
        shape = data[++subIndex].toInt();
        numberDimension = data[++subIndex].toInt();

        for (int i = 0; i < dimensions.count(); ++i) {
            dimensions[i].SetValues(data, subIndex);
        }
    }

    void ResetDefaulValues()
    {
        enable = true;
        shape = 0;
        numberDimension = 1;
        for (int i = 0; i < dimensions.count(); ++i) {
            dimensions[i].ResetDefaulValues();
        }
    }

    void ReadParam(QHash<QString, QVariant> hashValues)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        QString key;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(enable));
        enable = hashValues.contains(key) ? hashValues[key].toBool() : enable;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(shape));
        shape = hashValues.contains(key) ? hashValues[key].toInt() : shape;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(numberDimension));
        numberDimension = hashValues.contains(key) ? hashValues[key].toInt() : numberDimension;

        for (int i = 0; i < dimensions.count(); ++i) {
            dimensions[i].ReadParam(QString("%1 :: dimension%2").arg(header).arg(i+1), hashValues);
        }

    }

    void WriteParam(QTextStream &stream)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(enable))
                      .arg(enable);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(shape))
                      .arg(shape);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(numberDimension))
                      .arg(numberDimension);
        stream << "\n";
        for (int i = 0; i < dimensions.count(); ++i) {
            dimensions[i].WriteParam(QString("%1 :: dimension%2").arg(header).arg(i+1), stream);
        }
    }
};

class BodyRItem
{
public:
    BodyRItem(double _height, double _dimension, double _minTolerance, double _maxTolerance)
        : height(_height)
        , dimension(_dimension)
        , minTolerance(_minTolerance)
        , maxTolerance(_maxTolerance)
    {
    }

    BodyRItem()
    {
        ResetDefaulValues();
    }

public:
    double height;
    double dimension;
    double minTolerance;
    double maxTolerance;

    QList<QVariant> getValues()
    {
        return QList<QVariant> {height, dimension, minTolerance, maxTolerance};
    }

    void SetValues(QList<QVariant> data, int &subIndex)
    {
        // enable = data[++subIndex].toBool();
        height = data[++subIndex].toDouble();
        dimension = data[++subIndex].toDouble();
        minTolerance = data[++subIndex].toDouble();
        maxTolerance = data[++subIndex].toDouble();
    }

    void ResetDefaulValues()
    {
        // enable = true; // Подключить = true;
        height = 100;
        dimension = 79.3,
        minTolerance = 1.5;
        maxTolerance = 1.5;
    }

    void ReadParam(QString header, QHash<QString, QVariant> hashValues)
    {
        QString key;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(height));
        height = hashValues.contains(key) ? hashValues[key].toDouble() : height;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(dimension));
        dimension = hashValues.contains(key) ? hashValues[key].toDouble() : dimension;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minTolerance));
        minTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxTolerance));
        maxTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxTolerance;

    }

    void WriteParam(QString header, QTextStream &stream)
    {
        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(height))
                      .arg(height);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(dimension))
                      .arg(dimension);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minTolerance))
                      .arg(minTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxTolerance))
                      .arg(maxTolerance);
        stream << "\n";
    }
};

class BodyRInspect
{
public:

    BodyRInspect()
    {
        ResetDefaulValues();
    }

public:
    bool enable;
    int numberDimension;
    BodyRItem dimension5;
    BodyRItem dimension6;
    BodyRItem dimension7;
    BodyRItem dimension8;
    BodyRItem dimension57;
    BodyRItem dimension58;
    BodyRItem dimension59;
    BodyRItem dimension60;
    BodyRItem dimension61;
    BodyRItem dimension62;
    BodyRItem dimension63;
    BodyRItem dimension64;
    BodyRItem dimension71;
    BodyRItem dimension72;
    BodyRItem dimension73;
    BodyRItem dimension74;
    BodyRItem dimension75;
    BodyRItem dimension76;
    BodyRItem dimension77;
    BodyRItem dimension78;
    BodyRItem dimension79;
    BodyRItem dimension80;
    BodyRItem dimension81;

    QList<QVariant> getValues()
    {
        QList<QVariant> values = {enable, numberDimension};
        values.append(dimension5.getValues());
        values.append(dimension6.getValues());
        values.append(dimension7.getValues());
        values.append(dimension8.getValues());
        values.append(dimension57.getValues());
        values.append(dimension58.getValues());
        values.append(dimension59.getValues());
        values.append(dimension60.getValues());
        values.append(dimension61.getValues());
        values.append(dimension62.getValues());
        values.append(dimension63.getValues());
        values.append(dimension64.getValues());
        values.append(dimension71.getValues());
        values.append(dimension72.getValues());
        values.append(dimension73.getValues());
        values.append(dimension74.getValues());
        values.append(dimension75.getValues());
        values.append(dimension76.getValues());
        values.append(dimension77.getValues());
        values.append(dimension78.getValues());
        values.append(dimension79.getValues());
        values.append(dimension80.getValues());
        values.append(dimension81.getValues());

        return values;
    }

    void SetValues(QList<QVariant> data)
    {
        int subIndex = -1;
        enable = data[++subIndex].toBool();
        numberDimension = data[++subIndex].toInt();
        dimension5.SetValues(data, subIndex);
        dimension6.SetValues(data, subIndex);
        dimension7.SetValues(data, subIndex);
        dimension8.SetValues(data, subIndex);
        dimension57.SetValues(data, subIndex);
        dimension58.SetValues(data, subIndex);
        dimension59.SetValues(data, subIndex);
        dimension60.SetValues(data, subIndex);
        dimension61.SetValues(data, subIndex);
        dimension62.SetValues(data, subIndex);
        dimension63.SetValues(data, subIndex);
        dimension64.SetValues(data, subIndex);
        dimension71.SetValues(data, subIndex);
        dimension72.SetValues(data, subIndex);
        dimension73.SetValues(data, subIndex);
        dimension74.SetValues(data, subIndex);
        dimension75.SetValues(data, subIndex);
        dimension76.SetValues(data, subIndex);
        dimension77.SetValues(data, subIndex);
        dimension78.SetValues(data, subIndex);
        dimension79.SetValues(data, subIndex);
        dimension80.SetValues(data, subIndex);
        dimension81.SetValues(data, subIndex);
    }

    void ResetDefaulValues()
    {
        enable = true;
        numberDimension = 1;
        dimension5.ResetDefaulValues();
        dimension6.ResetDefaulValues();
        dimension7.ResetDefaulValues();
        dimension8.ResetDefaulValues();
        dimension57.ResetDefaulValues();
        dimension58.ResetDefaulValues();
        dimension59.ResetDefaulValues();
        dimension60.ResetDefaulValues();
        dimension61.ResetDefaulValues();
        dimension62.ResetDefaulValues();
        dimension63.ResetDefaulValues();
        dimension64.ResetDefaulValues();
        dimension71.ResetDefaulValues();
        dimension72.ResetDefaulValues();
        dimension73.ResetDefaulValues();
        dimension74.ResetDefaulValues();
        dimension75.ResetDefaulValues();
        dimension76.ResetDefaulValues();
        dimension77.ResetDefaulValues();
        dimension78.ResetDefaulValues();
        dimension79.ResetDefaulValues();
        dimension80.ResetDefaulValues();
        dimension81.ResetDefaulValues();
    }

    void ReadParam(QHash<QString, QVariant> hashValues)
    {

        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        QString key;
        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(enable));
        enable = hashValues.contains(key) ? hashValues[key].toBool() : enable;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(numberDimension));
        numberDimension = hashValues.contains(key) ? hashValues[key].toInt() : numberDimension;

        dimension5.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension5)), hashValues);
        dimension6.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension6)), hashValues);
        dimension7.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension7)), hashValues);
        dimension8.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension8)), hashValues);
        dimension57.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension57)), hashValues);
        dimension58.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension58)), hashValues);
        dimension59.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension59)), hashValues);
        dimension60.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension60)), hashValues);
        dimension61.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension61)), hashValues);
        dimension62.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension62)), hashValues);
        dimension63.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension63)), hashValues);
        dimension64.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension64)), hashValues);
        dimension71.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension71)), hashValues);
        dimension72.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension72)), hashValues);
        dimension73.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension73)), hashValues);
        dimension74.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension74)), hashValues);
        dimension75.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension75)), hashValues);
        dimension76.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension76)), hashValues);
        dimension77.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension77)), hashValues);
        dimension78.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension78)), hashValues);
        dimension79.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension79)), hashValues);
        dimension80.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension80)), hashValues);
        dimension81.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension81)), hashValues);
    }

    void WriteParam(QTextStream &stream)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());

        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(enable))
                      .arg(enable);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(numberDimension))
                      .arg(numberDimension);
        stream << "\n";

        dimension5.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension5)), stream);
        dimension6.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension6)), stream);
        dimension7.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension7)), stream);
        dimension8.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension8)), stream);
        dimension57.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension57)), stream);
        dimension58.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension58)), stream);
        dimension59.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension59)), stream);
        dimension60.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension60)), stream);
        dimension61.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension61)), stream);
        dimension62.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension62)), stream);
        dimension63.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension63)), stream);
        dimension64.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension64)), stream);
        dimension71.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension71)), stream);
        dimension72.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension72)), stream);
        dimension73.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension73)), stream);
        dimension74.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension74)), stream);
        dimension75.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension75)), stream);
        dimension76.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension76)), stream);
        dimension77.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension77)), stream);
        dimension78.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension78)), stream);
        dimension79.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension79)), stream);
        dimension80.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension80)), stream);
        dimension81.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimension81)), stream);
    }

};

class LeanInspect
{
public:
    // LeanInspect(bool _enable, double _parameter1, double _parameter2, double _minAngle)
    //     : enable(_enable)
    //     , parameter1(_parameter1)
    //     , parameter2(_parameter2)
    //     , minAngle(_minAngle)
    // {
    // }

    LeanInspect()
    {
        ResetDefaulValues();
    }

public:
    bool enable;
    double parameter1;
    double parameter2;
    double minDeviation;

    QList<QVariant> getValues()
    {
        return QList<QVariant> {enable, parameter1, parameter2, minDeviation};
    }

    void SetValues(QList<QVariant> data)
    {
        int subIndex = -1;
        enable = data[++subIndex].toBool();
        parameter1 = data[++subIndex].toDouble();
        parameter2 = data[++subIndex].toDouble();
        minDeviation = data[++subIndex].toDouble();
    }

    void ResetDefaulValues()
    {
        enable = true;
        parameter1 = 35;
        parameter2 = 35;
        minDeviation = 1;
    }

    void ReadParam(QHash<QString, QVariant> hashValues)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        QString key;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(enable));
        enable = hashValues.contains(key) ? hashValues[key].toBool() : enable;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(parameter1));
        parameter1 = hashValues.contains(key) ? hashValues[key].toDouble() : parameter1;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(parameter2));
        parameter2 = hashValues.contains(key) ? hashValues[key].toDouble() : parameter2;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minDeviation));
        minDeviation = hashValues.contains(key) ? hashValues[key].toDouble() : minDeviation;
    }

    void WriteParam(QTextStream &stream)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(enable))
                      .arg(enable);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(parameter1))
                      .arg(parameter1);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(parameter2))
                      .arg(parameter2);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minDeviation))
                      .arg(minDeviation);
        stream << "\n";
    }
};

class BentNeckInspect
{
public:
    BentNeckInspect(bool _enable, double _angle, double _minTolerance, double _maxTolerance)
        : enable(_enable)
        , angle(_angle)
        , minTolerance(_minTolerance)
        , maxTolerance(_maxTolerance)
    {
    }

    BentNeckInspect()
    {
        ResetDefaulValues();
    }

public:
    bool enable;
    double angle;
    double minTolerance;
    double maxTolerance;


    QList<QVariant> getValues()
    {
        return QList<QVariant> {enable, angle, minTolerance, maxTolerance};
    }

    void SetValues(QList<QVariant> data)
    {
        int subIndex = -1;
        enable = data[++subIndex].toBool();
        angle = data[++subIndex].toDouble();
        minTolerance = data[++subIndex].toDouble();
        maxTolerance = data[++subIndex].toDouble();
    }

    void ResetDefaulValues()
    {
        enable = true;
        angle = 45;
        minTolerance = 5;
        maxTolerance = 5;
    }

    void ReadParam(QHash<QString, QVariant> hashValues)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        QString key;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(enable));
        enable = hashValues.contains(key) ? hashValues[key].toBool() : enable;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(angle));
        angle = hashValues.contains(key) ? hashValues[key].toDouble() : angle;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minTolerance));
        minTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxTolerance));
        maxTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxTolerance;
    }

    void WriteParam(QTextStream &stream)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(enable))
                      .arg(enable);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(angle))
                      .arg(angle);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minTolerance))
                      .arg(minTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxTolerance))
                      .arg(maxTolerance);
        stream << "\n";
    }
};

class TiltInspect
{
public:
    TiltInspect(bool _enable, double _parameter1, double _parameter2, double _minHeight)
        : enable(_enable)
        , parameter1(_parameter1)
        , parameter2(_parameter2)
        , minHeight(_minHeight)
    {
    }

    TiltInspect()
    {
        ResetDefaulValues();
    }

public:
    bool enable;
    double parameter1;
    double parameter2;
    double minHeight;

    QList<QVariant> getValues()
    {
        return QList<QVariant> {enable, parameter1, parameter2, minHeight};
    }


    void SetValues(QList<QVariant> data)
    {
        int subIndex = -1;
        enable = data[++subIndex].toBool();
        parameter1 = data[++subIndex].toDouble();
        parameter2 = data[++subIndex].toDouble();
        minHeight = data[++subIndex].toDouble();
    }

    void ResetDefaulValues()
    {
        enable = true;
        parameter1 = 85;
        parameter2 = 10;
        minHeight = 0.3;
    }

    void ReadParam(QHash<QString, QVariant> hashValues)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        QString key;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(enable));
        enable = hashValues.contains(key) ? hashValues[key].toBool() : enable;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(parameter1));
        parameter1 = hashValues.contains(key) ? hashValues[key].toDouble() : parameter1;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(parameter2));
        parameter2 = hashValues.contains(key) ? hashValues[key].toDouble() : parameter2;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minHeight));
        minHeight = hashValues.contains(key) ? hashValues[key].toDouble() : minHeight;
    }

    void WriteParam(QTextStream &stream)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(enable))
                      .arg(enable);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(parameter1))
                      .arg(parameter1);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(parameter2))
                      .arg(parameter2);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minHeight))
                      .arg(minHeight);
        stream << "\n";
    }
};

class FinishDimensionInspect
{
public:
    FinishDimensionInspect(bool _enable, double _parameter1, double _parameter2,
                           double _parameter3, double _dimension, double _minTolerance, double _maxTolerance)
        : enable(_enable)
        , parameter1(_parameter1)
        , parameter2(_parameter2)
        , parameter3(_parameter3)
        , dimension(_dimension)
        , minTolerance(_minTolerance)
        , maxTolerance(_maxTolerance)    {
    }

    FinishDimensionInspect()
    {
        ResetDefaulValues(true, 0, 0, 0, 0, 0,0);
    }

public:
    bool enable;
    double parameter1;
    double parameter2;
    double parameter3;
    double dimension;
    double minTolerance;
    double maxTolerance;
    int numberParameter;

    QList<QVariant> getValues()
    {
        if(numberParameter == 0)
            return QList<QVariant> {enable, dimension, minTolerance, maxTolerance};
        if(numberParameter == 1)
            return QList<QVariant> {enable, parameter1, dimension, minTolerance, maxTolerance};
        if(numberParameter == 2)
            return QList<QVariant> {enable, parameter1, parameter2, dimension, minTolerance, maxTolerance};
        if(numberParameter == 3)
            return QList<QVariant> {enable, parameter1, parameter2, parameter3, dimension, minTolerance, maxTolerance};
    }

    void SetValues(QList<QVariant> data, int &subIndex)
    {
        enable = data[++subIndex].toBool();
        if(numberParameter > 0)
            parameter1 = data[++subIndex].toDouble();
        if(numberParameter > 1)
            parameter2 = data[++subIndex].toDouble();
        if(numberParameter > 2)
            parameter3 = data[++subIndex].toDouble();
        dimension = data[++subIndex].toDouble();
        minTolerance = data[++subIndex].toDouble();
        maxTolerance = data[++subIndex].toDouble();    }

    void ResetDefaulValues(bool _enable, double _parameter1, double _parameter2,
                           double _parameter3, double _dimension, double _minTolerance, double _maxTolerance)
    {
        enable = _enable;
        parameter1 = _parameter1;
        parameter2 = _parameter2;
        parameter3 = _parameter3;
        dimension = _dimension;
        minTolerance = _minTolerance;
        maxTolerance = _maxTolerance;
    }

    void ReadParam(QString header, QHash<QString, QVariant> hashValues)
    {
        QString key;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(enable));
        enable = hashValues.contains(key) ? hashValues[key].toBool() : enable;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(parameter1));
        parameter1 = hashValues.contains(key) ? hashValues[key].toDouble() : parameter1;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(parameter2));
        parameter2 = hashValues.contains(key) ? hashValues[key].toDouble() : parameter2;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(parameter3));
        parameter3 = hashValues.contains(key) ? hashValues[key].toDouble() : parameter3;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(dimension));
        dimension = hashValues.contains(key) ? hashValues[key].toDouble() : dimension;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minTolerance));
        minTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxTolerance));
        maxTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxTolerance;


    }

    void WriteParam(QString header, QTextStream &stream)
    {
        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(enable))
                      .arg(enable);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(parameter1))
                      .arg(parameter1);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(parameter2))
                      .arg(parameter2);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(parameter3))
                      .arg(parameter3);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(dimension))
                      .arg(dimension);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minTolerance))
                      .arg(minTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxTolerance))
                      .arg(maxTolerance);

        stream << "\n";
    }
};

class GroupFinishDimensionInspect
{
public:

    GroupFinishDimensionInspect()
    {
        dimensionF.numberParameter = 1;
        dimensionA.numberParameter = 1;
        dimensionT.numberParameter = 2;
        dimensionE.numberParameter = 2;
        dimensionD.numberParameter = 3;
        dimensionB.numberParameter = 2;
        dimensionS1.numberParameter = 2;
        dimensionH.numberParameter = 2;
        dimensionLugT.numberParameter = 2;
        dimensionLugT1.numberParameter = 2;
        dimensionDAngle.numberParameter = 3;
        ResetDefaulValues();
    }

public:
    bool enable;
    FinishDimensionInspect dimensionF;
    FinishDimensionInspect dimensionA;
    FinishDimensionInspect dimensionT;
    FinishDimensionInspect dimensionE;
    FinishDimensionInspect dimensionD;
    FinishDimensionInspect dimensionB;
    FinishDimensionInspect dimensionS1;
    FinishDimensionInspect dimensionH;
    FinishDimensionInspect dimensionLugT;
    FinishDimensionInspect dimensionLugT1;
    FinishDimensionInspect dimensionDAngle;

    QList<QVariant> getValues()
    {
        QList<QVariant> values = QList<QVariant> {enable};
        values.append(dimensionF.getValues());
        values.append(dimensionA.getValues());
        values.append(dimensionT.getValues());
        values.append(dimensionE.getValues());
        values.append(dimensionD.getValues());
        values.append(dimensionB.getValues());
        values.append(dimensionS1.getValues());
        values.append(dimensionH.getValues());
        values.append(dimensionLugT.getValues());
        values.append(dimensionLugT1.getValues());
        values.append(dimensionDAngle.getValues());
        return values;
    }

    void SetValues(QList<QVariant> data)
    {
        int subIndex = -1;
        enable = data[++subIndex].toBool();
        dimensionF.SetValues(data, subIndex);
        dimensionA.SetValues(data, subIndex);
        dimensionT.SetValues(data, subIndex);
        dimensionE.SetValues(data, subIndex);
        dimensionD.SetValues(data, subIndex);
        dimensionB.SetValues(data, subIndex);
        dimensionS1.SetValues(data, subIndex);
        dimensionH.SetValues(data, subIndex);
        dimensionLugT.SetValues(data, subIndex);
        dimensionLugT1.SetValues(data, subIndex);
        dimensionDAngle.SetValues(data, subIndex);
    }

    void ResetDefaulValues()
    {
        enable = true;
        dimensionF.ResetDefaulValues(true, 10, 0, 0, 24.9, 0.3, 0.3);
        dimensionA.ResetDefaulValues(true, 17.4, 0, 0, 27.7, 0.3, 0.3);
        dimensionT.ResetDefaulValues(true, 15.4, 10, 0, 27.1, 0.3, 0.3);
        dimensionE.ResetDefaulValues(true, 17.4, 10, 0, 25.5, 0.3, 0.3);
        dimensionD.ResetDefaulValues(true, 18, 1, 5, 15.4, 0.25, 0.25);
        dimensionB.ResetDefaulValues(true, 18, 5, 0, 27, 0.3, 0.3);
        dimensionS1.ResetDefaulValues(true, 2.2, 0.8, 0, 5, 0.3, 0.3);
        dimensionH.ResetDefaulValues(true, 10, 28, 0, 28.3, 0.3, 0.3);
        dimensionLugT.ResetDefaulValues(true, 17, 8, 1, 27, 0.3, 0.3);
        dimensionLugT1.ResetDefaulValues(true, 18, 28, 0, 26, 0.3, 0.3);
        dimensionDAngle.ResetDefaulValues(true, 17.5, 2, 5, 0, 5, 5);
    }

    void ReadParam(QHash<QString, QVariant> hashValues)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        QString key;
        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(enable));
        enable = hashValues.contains(key) ? hashValues[key].toBool() : enable;

        dimensionF.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionF)), hashValues);
        dimensionA.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionA)), hashValues);
        dimensionT.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionT)), hashValues);
        dimensionE.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionE)), hashValues);
        dimensionD.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionD)), hashValues);
        dimensionB.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionB)), hashValues);
        dimensionS1.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionS1)), hashValues);
        dimensionH.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionH)), hashValues);
        dimensionLugT.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionLugT)), hashValues);
        dimensionLugT1.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionLugT1)), hashValues);
        dimensionDAngle.ReadParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionDAngle)), hashValues);
    }

    void WriteParam(QTextStream &stream)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());

        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(enable))
                      .arg(enable);
        stream << "\n";

        dimensionF.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionF)), stream);
        dimensionA.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionA)), stream);
        dimensionT.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionT)), stream);
        dimensionE.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionE)), stream);
        dimensionD.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionD)), stream);
        dimensionB.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionB)), stream);
        dimensionS1.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionS1)), stream);
        dimensionH.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionH)), stream);
        dimensionLugT.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionLugT)), stream);
        dimensionLugT1.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionLugT1)), stream);
        dimensionDAngle.WriteParam(QString("%1 :: %2").arg(header).arg(VAR_TO_STRING(dimensionDAngle)), stream);
    }
};

class FlangeInspect
{
public:
    // FlangeInspect(bool _enable, double _minFlange)
    //     : enable(_enable)
    //     , minFlange(_minFlange)
    // {
    // }

    FlangeInspect()
    {
        ResetDefaulValues();
    }

public:
    bool enable;
    double parameter1;
    double parameter2; // number
    double parameter3;
    double parameter4;

    QList<QVariant> getValues()
    {
        return QList<QVariant> {enable, parameter1, parameter2, parameter3, parameter4};
    }

    void SetValues(QList<QVariant> data)
    {
        int subIndex = -1;
        enable = data[++subIndex].toBool();
        parameter1 = data[++subIndex].toDouble();
        parameter2 = data[++subIndex].toDouble();
        parameter3 = data[++subIndex].toDouble();
        parameter4 = data[++subIndex].toDouble();
    }

    void ResetDefaulValues()
    {
        enable = true;
        parameter1 = 0.3;
        parameter2 = 2;
        parameter3 = 12;
        parameter4 = 9;
    }

    void ReadParam(QHash<QString, QVariant> hashValues)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        QString key;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(enable));
        enable = hashValues.contains(key) ? hashValues[key].toBool() : enable;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(parameter1));
        parameter1 = hashValues.contains(key) ? hashValues[key].toDouble() : parameter1;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(parameter2));
        parameter2 = hashValues.contains(key) ? hashValues[key].toDouble() : parameter2;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(parameter3));
        parameter3 = hashValues.contains(key) ? hashValues[key].toDouble() : parameter3;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(parameter4));
        parameter4 = hashValues.contains(key) ? hashValues[key].toDouble() : parameter4;
    }

    void WriteParam(QTextStream &stream)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(enable))
                      .arg(enable);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(parameter1))
                      .arg(parameter1);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(parameter2))
                      .arg(parameter2);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(parameter3))
                      .arg(parameter3);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(parameter4))
                      .arg(parameter4);
        stream << "\n";
    }
};

class KnockoutInspect
{
public:
    // KnockoutInspect(bool _enable, double _parameter1)
    //     : enable(_enable)
    //     , parameter1(_parameter1)
    // {
    // }

    KnockoutInspect()
    {
        ResetDefaulValues();
    }

public:
    bool enable;
    double parameter1;
    double parameter2; // number
    double parameter3;
    double parameter4;

    QList<QVariant> getValues()
    {
        return QList<QVariant> {enable, parameter1, parameter2, parameter3, parameter4};
    }

    void SetValues(QList<QVariant> data)
    {
        int subIndex = -1;
        enable = data[++subIndex].toBool();
        parameter1 = data[++subIndex].toDouble();
        parameter2 = data[++subIndex].toDouble();
        parameter3 = data[++subIndex].toDouble();
        parameter4 = data[++subIndex].toDouble();
    }

    void ResetDefaulValues()
    {
        enable = true;
        parameter1 = 0.3;
        parameter2 = 2;
        parameter3 = 12;
        parameter4 = 9;
    }

    void ReadParam(QHash<QString, QVariant> hashValues)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        QString key;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(enable));
        enable = hashValues.contains(key) ? hashValues[key].toBool() : enable;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(parameter1));
        parameter1 = hashValues.contains(key) ? hashValues[key].toDouble() : parameter1;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(parameter2));
        parameter2 = hashValues.contains(key) ? hashValues[key].toDouble() : parameter2;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(parameter3));
        parameter3 = hashValues.contains(key) ? hashValues[key].toDouble() : parameter3;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(parameter4));
        parameter4 = hashValues.contains(key) ? hashValues[key].toDouble() : parameter4;
    }

    void WriteParam(QTextStream &stream)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(enable))
                      .arg(enable);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(parameter1))
                      .arg(parameter1);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(parameter2))
                      .arg(parameter2);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(parameter3))
                      .arg(parameter3);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(parameter4))
                      .arg(parameter4);
        stream << "\n";
    }
};

class PushupBodyInspect
{
public:
    PushupBodyInspect(bool _enable, double _pushup, double _minTolerance, double _maxTolerance)
        : enable(_enable)
        , pushup(_pushup)
        , minTolerance(_minTolerance)
        , maxTolerance(_maxTolerance)
    {
    }

    PushupBodyInspect()
    {
        ResetDefaulValues();
    }

public:
    bool enable;
    double pushup;
    double minTolerance;
    double maxTolerance;

    QList<QVariant> getValues()
    {
        return QList<QVariant> {enable, pushup, minTolerance, maxTolerance};
    }

    void SetValues(QList<QVariant> data)
    {
        int subIndex = -1;
        enable = data[++subIndex].toBool();
        pushup = data[++subIndex].toDouble();
        minTolerance = data[++subIndex].toDouble();
        maxTolerance = data[++subIndex].toDouble();
    }

    void ResetDefaulValues()
    {
        enable = true;
        pushup = 3;
        minTolerance = 0.3;
        maxTolerance = 0.3;
    }

    void ReadParam(QHash<QString, QVariant> hashValues)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        QString key;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(enable));
        enable = hashValues.contains(key) ? hashValues[key].toBool() : enable;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(pushup));
        pushup = hashValues.contains(key) ? hashValues[key].toDouble() : pushup;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minTolerance));
        minTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxTolerance));
        maxTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxTolerance;

    }

    void WriteParam(QTextStream &stream)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(enable))
                      .arg(enable);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(pushup))
                      .arg(pushup);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minTolerance))
                      .arg(minTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxTolerance))
                      .arg(maxTolerance);
        stream << "\n";
    }
};

class InsideNeckInspect
{
public:
    // InsideNeckInspect(bool _enable, double _diameter, double _minTolerance, double _maxTolerance)
    //     : enable(_enable)
    //     , diameter(_diameter)
    //     , minTolerance(_minTolerance)
    //     , maxTolerance(_maxTolerance)
    // {
    // }

    InsideNeckInspect()
    {
        ResetDefaulValues();
    }

public:
    bool enable;
    double parameter1;
    double diameter;
    double minTolerance;
    double maxTolerance;

    QList<QVariant> getValues()
    {
        return QList<QVariant> {enable, parameter1, diameter, minTolerance, maxTolerance};
    }
    void SetValues(QList<QVariant> data)
    {
        int subIndex = -1;
        enable = data[++subIndex].toBool();
        parameter1 = data[++subIndex].toDouble();
        diameter = data[++subIndex].toDouble();
        minTolerance = data[++subIndex].toDouble();
        maxTolerance = data[++subIndex].toDouble();
    }

    void ResetDefaulValues()
    {
        enable = true;
        parameter1 = 20;
        diameter = 24;
        minTolerance = 0.3;
        maxTolerance = 0.3;
    }

    void ReadParam(QHash<QString, QVariant> hashValues)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        QString key;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(enable));
        enable = hashValues.contains(key) ? hashValues[key].toBool() : enable;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(parameter1));
        parameter1 = hashValues.contains(key) ? hashValues[key].toDouble() : parameter1;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(diameter));
        diameter = hashValues.contains(key) ? hashValues[key].toDouble() : diameter;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minTolerance));
        minTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxTolerance));
        maxTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxTolerance;

    }

    void WriteParam(QTextStream &stream)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(enable))
                      .arg(enable);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(parameter1))
                      .arg(parameter1);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(diameter))
                      .arg(diameter);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minTolerance))
                      .arg(minTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxTolerance))
                      .arg(maxTolerance);
        stream << "\n";
    }
};

class WallThicknessInspect
{
public:
    WallThicknessInspect(bool _enable, double _thickness,  double _minTolerance, double _maxTolerance)
        : enable(_enable)
        , thickness(_thickness)
        , minTolerance(_minTolerance)
        , maxTolerance(_maxTolerance)
    {
    }

    WallThicknessInspect()
    {
        ResetDefaulValues();
    }

public:
    bool enable;
    double thickness;
    double minTolerance;
    double maxTolerance;

    QList<QVariant> getValues()
    {
        return QList<QVariant> {enable, thickness,  minTolerance, maxTolerance};
    }

    void SetValues(QList<QVariant> data)
    {
        int subIndex = -1;
        enable = data[++subIndex].toBool();
        thickness = data[++subIndex].toDouble();
        minTolerance = data[++subIndex].toDouble();
        maxTolerance = data[++subIndex].toDouble();    }

    void ResetDefaulValues()
    {
        enable = true;
        thickness = 1;
        minTolerance = 0.3;
        maxTolerance = 0.3;
    }

    void ReadParam(QHash<QString, QVariant> hashValues)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        QString key;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(enable));
        enable = hashValues.contains(key) ? hashValues[key].toBool() : enable;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(thickness));
        thickness = hashValues.contains(key) ? hashValues[key].toDouble() : thickness;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minTolerance));
        minTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxTolerance));
        maxTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxTolerance;

    }

    void WriteParam(QTextStream &stream)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(enable))
                      .arg(enable);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(thickness))
                      .arg(thickness);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minTolerance))
                      .arg(minTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxTolerance))
                      .arg(maxTolerance);
        stream << "\n";
    }
};

class SeamInspect
{
public:
    SeamInspect(bool _enable, double _bodyHeight, double _minBodyHeightTolerance, double _maxBodyHeightTolerance,
                double _bottomHeight, double _minBottomHeightTolerance, double _maxBottomHeightTolerance)
        : enable(_enable)
        , bodyHeight(_bodyHeight)
        , minBodyHeightTolerance(_minBodyHeightTolerance)
        , maxBodyHeightTolerance(_maxBodyHeightTolerance)
        , bottomHeight(_bottomHeight)
        , minBottomHeightTolerance(_minBottomHeightTolerance)
    {
    }

    SeamInspect()
    {
        ResetDefaulValues();
    }

public:
    bool enable;
    double bodyHeight;
    double minBodyHeightTolerance;
    double maxBodyHeightTolerance;
    double bottomHeight;
    double minBottomHeightTolerance;
    double maxBottomHeightTolerance;


    QList<QVariant> getValues()
    {
        return QList<QVariant> {enable, bodyHeight, minBodyHeightTolerance, maxBodyHeightTolerance,
                               bottomHeight, minBottomHeightTolerance, maxBottomHeightTolerance};
    }

    void SetValues(QList<QVariant> data)
    {
        int subIndex = -1;
        enable = data[++subIndex].toBool();
        bodyHeight = data[++subIndex].toDouble();
        minBodyHeightTolerance = data[++subIndex].toDouble();
        maxBodyHeightTolerance = data[++subIndex].toDouble();
        bottomHeight = data[++subIndex].toDouble();
        minBottomHeightTolerance = data[++subIndex].toDouble();
        maxBottomHeightTolerance = data[++subIndex].toDouble();
    }

    void ResetDefaulValues()
    {
        enable = true;
        bodyHeight = 90;
        minBodyHeightTolerance = 1;
        maxBodyHeightTolerance = 1;
        bottomHeight = 50;
        minBottomHeightTolerance = 1;
        maxBottomHeightTolerance = 1;
    }

    void ReadParam(QHash<QString, QVariant> hashValues)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        QString key;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(enable));
        enable = hashValues.contains(key) ? hashValues[key].toBool() : enable;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(bodyHeight));
        bodyHeight = hashValues.contains(key) ? hashValues[key].toDouble() : bodyHeight;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minBodyHeightTolerance));
        minBodyHeightTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minBodyHeightTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxBodyHeightTolerance));
        maxBodyHeightTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxBodyHeightTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(bottomHeight));
        bottomHeight = hashValues.contains(key) ? hashValues[key].toDouble() : bottomHeight;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(minBottomHeightTolerance));
        minBottomHeightTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : minBottomHeightTolerance;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(maxBottomHeightTolerance));
        maxBottomHeightTolerance = hashValues.contains(key) ? hashValues[key].toDouble() : maxBottomHeightTolerance;

    }

    void WriteParam(QTextStream &stream)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(enable))
                      .arg(enable);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(bodyHeight))
                      .arg(bodyHeight);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minBodyHeightTolerance))
                      .arg(minBodyHeightTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxBodyHeightTolerance))
                      .arg(maxBodyHeightTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(bottomHeight))
                      .arg(bottomHeight);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(minBottomHeightTolerance))
                      .arg(minBottomHeightTolerance);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(maxBottomHeightTolerance))
                      .arg(maxBottomHeightTolerance);
        stream << "\n";
    }
};

class NumberCodeDecode
{
public:
    NumberCodeDecode()
    {
        ResetDefaulValues();
    }

public:
    bool enable;
    int codeNumber;
    double bottomROI;
    double heightROI;

    QList<QVariant> getValues()
    {
        return QList<QVariant> {enable, codeNumber, bottomROI, heightROI};
    }

    void SetValues(QList<QVariant> data)
    {
        int subIndex = -1;
        enable = data[++subIndex].toBool();
        codeNumber = data[++subIndex].toInt();
        bottomROI = data[++subIndex].toDouble();
        heightROI = data[++subIndex].toDouble();
    }

    void ResetDefaulValues()
    {
        enable = true;
        codeNumber = 1;
        bottomROI = 5;
        heightROI = 20;
    }

    void ReadParam(QHash<QString, QVariant> hashValues)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        QString key;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(enable));
        enable = hashValues.contains(key) ? hashValues[key].toBool() : enable;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(codeNumber));
        codeNumber = hashValues.contains(key) ? hashValues[key].toInt() : codeNumber;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(bottomROI));
        bottomROI = hashValues.contains(key) ? hashValues[key].toDouble() : bottomROI;

        key = QString("%1 :: %2")
                  .arg(header)
                  .arg(VAR_TO_STRING(heightROI));
        heightROI = hashValues.contains(key) ? hashValues[key].toDouble() : heightROI;
    }

    void WriteParam(QTextStream &stream)
    {
        QString header = VisonParamUtlity::ConvertHeaderFormat(typeid(*this).name());
        stream << QString("[%1]\n").arg(header);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(enable))
                      .arg(enable);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(codeNumber))
                      .arg(codeNumber);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(bottomROI))
                      .arg(bottomROI);
        stream << QString("%1=%2\n")
                      .arg(VAR_TO_STRING(heightROI))
                      .arg(heightROI);
        stream << "\n";
    }
};



#endif // VISION_PARAMETERS_H
