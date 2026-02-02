#ifndef SYSTEMVM_H
#define SYSTEMVM_H

#include <QObject>
#include <QDateTime>

class SystemVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int numberOfBottles READ numberOfBottles WRITE setNumberOfBottles NOTIFY numberOfBottlesChanged FINAL)
    Q_PROPERTY(QString lastBottleTime READ lastBottleTime WRITE setLastBottleTime NOTIFY lastBottleTimeChanged FINAL)

public:
    explicit SystemVM(QObject *parent = nullptr);

    // property //  Собственность
    int numberOfBottles();
    QString lastBottleTime();
    // end // конец

    void UpdateInspectInfo();

private:
    // property //  Собственность
    int _numberOfBottles;
    QString _lastBottleTime;
    // end // конец

signals:
    // property //  Собственность
    void numberOfBottlesChanged();
    void lastBottleTimeChanged();
    // end // конец

public slots:
    // property //  Собственность
    void setNumberOfBottles(int value);
    void setLastBottleTime(QString value);
    // end // конец

};

#endif // SYSTEMVM_H
