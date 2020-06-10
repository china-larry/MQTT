#include "CMqtt2CanThread.h"

CMqtt2CanThread * CMqtt2CanThread::sm_pInstance = NULL;

CMqtt2CanThread::CMqtt2CanThread()
{

}

CMqtt2CanThread::~CMqtt2CanThread()
{

}

void CMqtt2CanThread::run()
{
    while(true)
    {
        if(m_strSubscribeMsgList.count() > 0)
        {
            m_qLockerMutex.lock();
            m_strCurrentSubscribeMsg = m_strSubscribeMsgList.at(0);
            m_strSubscribeMsgList.pop_front();
            m_qLockerMutex.unlock();

            emit SignalOneSubscribeMsg(m_strCurrentSubscribeMsg);
        }
        msleep(100);
    }
}

CMqtt2CanThread* CMqtt2CanThread::GetInstance()
{
    if(NULL == sm_pInstance)
    {
        sm_pInstance = new CMqtt2CanThread();
    }
    return sm_pInstance;
}

void CMqtt2CanThread::AddSubscribeMsg(QString strMsg)
{
    m_qLockerMutex.lock();
    m_strSubscribeMsgList.push_back(strMsg);
    m_qLockerMutex.unlock();
}
