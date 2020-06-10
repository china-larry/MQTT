#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QCanBus>
#include "CMqtt2CanThread.h"

#include "CAnalyzeCanMsgThread.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    m_pMqttThread = new QThread();
     m_pCMqttClientThread = new QMqttClient;
//    m_pCMqttClientThread->moveToThread(m_pMqttThread);
    QObject::connect(m_pCMqttClientThread, &QMqttClient::stateChanged,
            this, &MainWindow::mqtt_connect_success);
    QObject::connect(m_pCMqttClientThread, &QMqttClient::messageReceived,
            this, &MainWindow::SlotSubscribeMsg);
    // can 线程开启
    QList<QCanBusDeviceInfo> qCanBusInterfacesList = QCanBus::instance()->availableDevices("socketcan");
    for (const QCanBusDeviceInfo &info : qAsConst(qCanBusInterfacesList))
    {
        CCanBusDeviceThread *pCCanBusDeviceThread = new CCanBusDeviceThread();
        connect(CMqtt2CanThread::GetInstance(), &CMqtt2CanThread::SignalOneSubscribeMsg,
                pCCanBusDeviceThread, &CCanBusDeviceThread::SlotReadOneMqttMsg);
        connect(pCCanBusDeviceThread, &CCanBusDeviceThread::SignalReadFramePayload,
                CAnalyzeCanMsgThread::GetInstance(), &CAnalyzeCanMsgThread::SlotReadCanMsg);
        SCanBusDeviceStruct ksSCanBusDeviceStruct;
        ksSCanBusDeviceStruct.strPlugin = "socketcan";
        ksSCanBusDeviceStruct.strInterfaceName = info.name();
        pCCanBusDeviceThread->InitCanBusDevice(ksSCanBusDeviceStruct);
        pCCanBusDeviceThread->start();
        m_qCanBusDeviceThreadList.push_back(pCCanBusDeviceThread);
    }
    // mqtt 2 can 线程开启
    CMqtt2CanThread::GetInstance()->start();
}

MainWindow::~MainWindow()
{
//    m_pMqttThread->terminate();
    delete ui;
}

void MainWindow::SlotSubscribeMsg(const QByteArray &message,
                                  const QMqttTopicName &topic)
{
    m_strReceivedMsg = QDateTime::currentDateTime().toString("yyyy-MM-dd:hh:mm:ss")
                + QLatin1String(" Received Topic: ")
                + topic.name()
                + QLatin1String(" Message: ")
                + message
                + QLatin1Char('\n');
    ui->textBrowser->insertPlainText(m_strReceivedMsg);

    CMqtt2CanThread::GetInstance()->AddSubscribeMsg(m_strReceivedMsg);
}

void MainWindow::on_connect_clicked()
{
    m_pCMqttClientThread->setHostname(ui->host->text());
    m_pCMqttClientThread->setPort(ui->port->text().toInt());
    m_pCMqttClientThread->connectToHost();
}

void MainWindow::mqtt_connect_success()
{
    QString strState = QDateTime::currentDateTime().toString("yyyy-MM-dd:hh:mm:ss")
                    + QLatin1String(": State Change")
                    + QString::number(m_pCMqttClientThread->state());
    ui->textBrowser->append(strState);
    if(m_pCMqttClientThread->state() == 2)
    {
           ui->textBrowser->append("连接成功\n");
    }
}

void MainWindow::mqtt_disconnect()
{
    ui->textBrowser->append("连接断开");
}

void MainWindow::mqtt_sub_success(QString topic, quint8 qos)
{
    QString msg = "订阅主题 ";
       msg += ui->sub_topic->text();
       msg += " 成功";
       ui->textBrowser->append(msg);
}


void MainWindow::on_sub_clicked()
{
    m_pCMqttClientThread->subscribe(ui->sub_topic->text(), 0);
}

void MainWindow::on_pub_clicked()
{
    m_pCMqttClientThread->publish(QMqttTopicName(ui->sub_topic->text()),
                                  ui->pub_msg->text().toUtf8());
}
