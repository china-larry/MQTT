#ifndef CMQTTCLIENTTHREAD_H
#define CMQTTCLIENTTHREAD_H

#include <QObject>
#include "QtMqtt/qmqttclient.h"
class CMqttClientThread : public QObject
{
    Q_OBJECT
public:
    explicit CMqttClientThread(QObject *parent = nullptr);

signals:
    void SignalConnectState(QString strState);
    void SignalSubScribeMsg(QString strTopic, QString strMsg);
public slots:
    void SlotMqttConnectSuccess();
    void SlotMessageReceived(const QByteArray &message, const QMqttTopicName &topic);
public:
    void SetHostPort(QString strHost, int iPort);
    void SetUser(QString strUserName, QString strPassword);
    void ConnectHost();
    void DisConnectHost();
    void SubScribeMsg(QString strTopic, int iQoS);


private:
    QMqttClient *m_client;
};

#endif // CMQTTCLIENTTHREAD_H
