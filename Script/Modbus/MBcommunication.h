#ifndef MBCOMMUNICATION_H
#define MBCOMMUNICATION_H

#include <QObject>
#include <QTimer>
#include <QHash>


class MBKeyData {

public:
    MBKeyData();
    MBKeyData(int _address, int _table);
    virtual ~MBKeyData();
public:
    inline int getAddress() const { return address; }
    inline int getTable() const { return table; }
private:
    int address;
    int table;
};

inline bool operator==(const MBKeyData& rhs, const MBKeyData& lhs)
{
    return rhs.getAddress() == lhs.getAddress() &&
           rhs.getTable() == lhs.getTable();
}

// do this to make sure generate unique value in vhash table  // сделайте это, чтобы убедиться, что сгенерировано уникальное значение в vhash-таблице
inline uint qHash(const MBKeyData& key, uint seed)
{
    return qHash(key.getAddress(), seed) ^
           qHash(key.getTable(), seed);
}



class MBCommunication : public QObject
{
    Q_OBJECT
private:
    explicit MBCommunication(QObject *parent = nullptr);
public:
    virtual ~MBCommunication();
public:
    inline static MBCommunication* GetInstance() {

        if (m_pInstance.isNull())
            m_pInstance.reset(new MBCommunication());

        return m_pInstance.data();
    }

    bool Setup();
    bool Start();
    void StartPollingTimer();
    void StopPollingTimer();

    inline const QHash<MBKeyData, quint16>& GetMBData() const { return m_mbDataAggregation; }

    void WriteData(int table, int address, int val);
    void WriteBitData(int table, int address, int bitValue, bool val);
    void WriteFloatData(int table, int address, float val);
    void WriteUint32Data(int table, int address, quint32 val);

    void ReadFloatData(int table, int address, float &val);
    void ReadUnit16Data(int table, int address, quint16& val);
    void ReadUint32Data(int table, int address, quint32& val);

    static void ConvertFloatTo2Registers(float value, quint16 &reg1, quint16 &reg2);

    static void ConnectionChangedCallback(int connectState);
    static void ErrorOccurCallback(int error);
    static void DataWriteCompleteCallback(int table, int address, int val, bool isSuccess);
    static void DataReadCompleteCallback(int table, int address, int totalCount, const QVector<quint16>& val, bool isSuccess);
private:
    void ReadData();
    void AccumulateData(int table, int address, quint16 value);
private:
    QString m_ipAddress;
    QString m_port;
    QString m_serverAddress;
    bool m_isConnectedState;
    int m_mode;
    void* m_pDevice;

    QHash<MBKeyData, quint16> m_mbDataAggregation;
    QScopedPointer<QTimer> m_pPollingDataUpdate;
    static QScopedPointer<MBCommunication> m_pInstance;

    uint64_t m_groupAdressIndex;
signals:
    void populateDataSignal();

};

#endif // MBCOMMUNICATION_H
