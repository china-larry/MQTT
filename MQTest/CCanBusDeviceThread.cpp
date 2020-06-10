#include "CCanBusDeviceThread.h"
#include <QCanBus>
#include <QVariant>
CCanBusDeviceThread::CCanBusDeviceThread()
{
    m_pCanBusDevice = NULL;
    m_iSendTimes = 3;// 重发3次
}

CCanBusDeviceThread::~CCanBusDeviceThread()
{

}

void CCanBusDeviceThread::run()
{
    while(m_pCanBusDevice != NULL)
    {
        if(m_qSendPortDataList.count() > 0 && m_iSendTimes > 0)
        {
            m_qPortDataByteArray = m_qSendPortDataList[0];
            m_qFrameForSend.setPayload(qDataByteArray);
            if(!m_pCanBusDevice->writeFrame(qFrame))
            {
                qDebug() << "write fram error" << m_pCanBusDevice->errorString();
            }
            m_iSendTimes--;
        }
        if(m_bFramesAvailableBuffer)
        {
            while(m_pCanBusDevice->framesAvailable())
            {
                m_qFrameForRead = m_pCanBusDevice->readFrame();
                emit SignalReadFramePayload(m_qFrameForRead.payload());
            }
            m_bFramesAvailableBuffer = false;
        }
        msleep(200);
    }
}

void CCanBusDeviceThread::SlotReadOneMqttMsg(QString strMsg)
{
    QStringList strMsgList = strMsg.split("//");
    // 分拆发送Can
    m_qLockerMutex.lock();
    m_qSendPortDataList.push_back(strMsg.toUtf8());
    m_qLockerMutex.unlock();
}

void CCanBusDeviceThread::SlotCanBusError(QCanBusDevice::CanBusError error)
{
    qDebug() << "CanBus Error" << error;
}

void CCanBusDeviceThread::SlotCanFramesReceived()
{
    m_qLockerMutex.lock();
    m_bFramesAvailableBuffer = true;
    m_qLockerMutex.unlock();
}

bool CCanBusDeviceThread::InitCanBusDevice(const SCanBusDeviceStruct sSCanBusDeviceStruct)
{
    m_sSCanBusDeviceStruct = sSCanBusDeviceStruct;
    QString strErrorString;
    m_pCanBusDevice = QCanBus::instance()->createDevice(
          m_sSCanBusDeviceStruct.strPlugin, m_sSCanBusDeviceStruct.strInterfaceName, &strErrorString);
    if (!m_pCanBusDevice)
    {
        qDebug() << strErrorString;
        emit SignalConnectError(m_sSCanBusDeviceStruct.strInterfaceName, strErrorString);
        return false;
    }
    connect(m_pCanBusDevice, &QCanBusDevice::errorOccurred, this, &CCanBusDeviceThread::SlotCanBusError);
    connect(m_pCanBusDevice, &QCanBusDevice::framesReceived, this, &CCanBusDeviceThread::SlotCanFramesReceived);
    m_pCanBusDevice->setConfigurationParameter(QCanBusDevice::BitRateKey,m_sSCanBusDeviceStruct.iBitRate);

    m_qFrameForSend.setFrameId(m_sSCanBusDeviceStruct.iCanId);
    if(!m_pCanBusDevice->connectDevice())
    {
        emit SignalConnectError(m_sSCanBusDeviceStruct.strInterfaceName, m_pCanBusDevice->errorString());
        delete m_pCanBusDevice;
        m_pCanBusDevice = NULL;
        return false;
    }
    else
    {
        QVariant qBitRate = m_pCanBusDevice->configurationParameter(QCanBusDevice::BitRateKey);
        if (qBitRate.isValid())
        {
            qDebug() << (QString("Backend: %1, connected to %2 at %3 kBit/s")
                    .arg(m_currentSettings.backendName).arg(m_currentSettings.deviceInterfaceName)
                    .arg(qBitRate.toInt()/1000));
            return true;
        }
        else
        {
            emit SignalConnectError(m_sSCanBusDeviceStruct.strInterfaceName, "bad BitRate");
            delete m_pCanBusDevice;
            m_pCanBusDevice = NULL;
            return false;
        }
    }
    return true;
}

void CCanBusDeviceThread::SendPortData(QByteArray qDataByteArray)
{
    m_qLockerMutex.lock();
    m_qSendPortDataList.push_back(qDataByteArray);
    m_qLockerMutex.unlock();
}

void CCanBusDeviceThread::GetSendACK()
{
    m_qLockerMutex.lock();
    m_iSendTimes = 3;
    m_qSendPortDataList.pop_front();
    m_qLockerMutex.unlock();

}
