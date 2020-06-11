#include "CAnalyzeCanMsgThread.h"

#include <QDebug>
// 饿汉模式，多线程安全
CAnalyzeCanMsgThread * CAnalyzeCanMsgThread::sm_pInstance = new CAnalyzeCanMsgThread();
CAnalyzeCanMsgThread::CAnalyzeCanMsgThread()
{

}

CAnalyzeCanMsgThread::~CAnalyzeCanMsgThread()
{
    if(sm_pInstance != NULL)
    {
        delete sm_pInstance;
        sm_pInstance = NULL;
    }
}
CAnalyzeCanMsgThread *CAnalyzeCanMsgThread::GetInstance()
{
    return sm_pInstance;
}
void CAnalyzeCanMsgThread::run()
{
    while(true)
    {
        if(m_qCanMsgList.count() > 0)
        {
            m_qLockerMutex.lock();
            m_qCanMsgByteArray = m_qCanMsgList.at(0);
            m_qCanMsgList.pop_front();
            m_qLockerMutex.unlock();
            //
            qDebug() << "can msg " << m_qCanMsgByteArray;
        }
    }
}

void CAnalyzeCanMsgThread::SlotReadCanMsg(QByteArray qCanMsg)
{
    m_qLockerMutex.lock();
    m_qCanMsgList.push_back(qCanMsg);
    m_qLockerMutex.unlock();
}


