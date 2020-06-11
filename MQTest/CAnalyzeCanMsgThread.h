#ifndef CANALYZECANMSGTHREAD_H
#define CANALYZECANMSGTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
class CAnalyzeCanMsgThread : public QThread
{
    Q_OBJECT

public:
    explicit CAnalyzeCanMsgThread();
    ~CAnalyzeCanMsgThread();

protected:
    virtual void run();

public slots:
    void SlotReadCanMsg(QByteArray qCanMsg);
public:
    static CAnalyzeCanMsgThread* GetInstance();
private:
    static CAnalyzeCanMsgThread *sm_pInstance;
    QMutex m_qLockerMutex;
    QByteArray m_qCanMsgByteArray;
    QList<QByteArray> m_qCanMsgList;
};

#endif // CANALYZECANMSGTHREAD_H
