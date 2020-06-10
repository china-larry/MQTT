#include "CAnalyzeCanMsgThread.h"
CAnalyzeCanMsgThread * CAnalyzeCanMsgThread::sm_pInstance = NULL;
CAnalyzeCanMsgThread::CAnalyzeCanMsgThread()
{

}

CAnalyzeCanMsgThread::~CAnalyzeCanMsgThread()
{

}
CAnalyzeCanMsgThread *CAnalyzeCanMsgThread::GetInstance()
{
    if(NULL == sm_pInstance)
    {
        sm_pInstance = new CAnalyzeCanMsgThread();
    }
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


