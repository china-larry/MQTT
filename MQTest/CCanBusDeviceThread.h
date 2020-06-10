#ifndef CCANBUSDEVICETHREAD_H
#define CCANBUSDEVICETHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QCanBusDevice>
#include "configdate.h"
class CCanBusDeviceThread : public QThread
{

    Q_OBJECT
public:
   explicit CCanBusDeviceThread();
    ~CCanBusDeviceThread();

protected:
    virtual void run();

signals:
    void SignalConnectError(QString strInterfaceName, QString strErrorCode);
    void SignalReadFramePayload(QByteArray qPayload);
public slots:
    void SlotReadOneMqttMsg(QString strMsg);
    void SlotCanBusError(QCanBusDevice::CanBusError error);
    void SlotCanFramesReceived();
public:
    bool InitCanBusDevice(const SCanBusDeviceStruct sSCanBusDeviceStruct);
    void SendPortData(QByteArray qDataByteArray);

    void GetSendACK();
private:
    QCanBusDevice *m_pCanBusDevice;
    SCanBusDeviceStruct m_sSCanBusDeviceStruct;
    QMutex m_qLockerMutex;
    QCanBusFrame m_qFrameForSend;
    QCanBusFrame m_qFrameForRead;
    QList<QByteArray> m_qSendPortDataList;
    QByteArray m_qPortDataByteArray;
    int m_iSendTimes;// can 发送是否成功，决定是否发送下一帧
    bool m_bFramesAvailableBuffer;
};

#endif // CCANBUSDEVICETHREAD_H
