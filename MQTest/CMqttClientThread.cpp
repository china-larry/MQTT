#include "CMqttClientThread.h"

CMqttClientThread::CMqttClientThread(QObject *parent) : QObject(parent)
{
//    qRegisterMetaType<ClientState>("ClientState");
    m_client = new QMqttClient();
    connect(m_client, &QMqttClient::stateChanged,
            this, &CMqttClientThread::SlotMqttConnectSuccess);
    connect(m_client, &QMqttClient::messageReceived,
            this, &CMqttClientThread::SlotMessageReceived);
}

void CMqttClientThread::SlotMqttConnectSuccess()
{
    QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(": State Change")
                    + QString::number(m_client->state())
                    + QLatin1Char('\n');

    emit SignalConnectState(content);
    qDebug() << "contet state " << content;
}

void CMqttClientThread::SlotMessageReceived(const QByteArray &message,
                                            const QMqttTopicName &topic)
{
    QString strTopicName = topic.name();
    QString strMsg = message;
    emit SignalSubScribeMsg(strTopicName, strMsg);
    qDebug() << "topic is " << topic.name()
             << "message is " << message;
}

void CMqttClientThread::SetHostPort(QString strHost, int iPort)
{
    m_client->setHostname(strHost);
    m_client->setPort(iPort);
}

void CMqttClientThread::SetUser(QString strUserName, QString strPassword)
{
    m_client->setUsername(strUserName);
    m_client->setPassword(strPassword);
}

void CMqttClientThread::ConnectHost()
{
    m_client->connectToHost();
}

void CMqttClientThread::DisConnectHost()
{
    m_client->disconnectFromHost();
}

void CMqttClientThread::SubScribeMsg(QString strTopic, int iQoS)
{
    m_client->subscribe(strTopic, iQoS);
}
