#ifndef CMQTT2CANTHREAD_H
#define CMQTT2CANTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
class CMqtt2CanThread : public QThread
{
    Q_OBJECT

public:
    explicit CMqtt2CanThread();
    ~CMqtt2CanThread();

protected:
    virtual void run();

signals:
    void SignalOneSubscribeMsg(QString strMsg);
public:
    static CMqtt2CanThread* GetInstance();
    //
    void AddSubscribeMsg(QString strMsg);
private:
    static CMqtt2CanThread *sm_pInstance;

    QList<QString> m_strSubscribeMsgList;
    QString m_strCurrentSubscribeMsg;
    QMutex m_qLockerMutex;
};

#endif // CMQTT2CANTHREAD_H
