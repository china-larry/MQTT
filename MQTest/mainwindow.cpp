#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_client = new QMqttClient();
    connect(m_client, &QMqttClient::stateChanged, this, &MainWindow::mqtt_connect_success);

    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(" Received Topic: ")
                    + topic.name()
                    + QLatin1String(" Message: ")
                    + message
                    + QLatin1Char('\n');
        ui->textBrowser->insertPlainText(content);
    });

    connect(m_client, &QMqttClient::pingResponseReceived, this, [this]() {
        const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(" PingResponse")
                    + QLatin1Char('\n');
        ui->textBrowser->insertPlainText(content);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connect_clicked()
{



    m_client->setHostname(ui->host->text());
    m_client->setPort(ui->port->text().toInt());

    m_client->connectToHost();

}

void MainWindow::mqtt_connect_success()
{

    const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(": State Change")
                    + QString::number(m_client->state())
                    + QLatin1Char('\n');

    ui->textBrowser->append("连接成功" + content);
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

//void MainWindow::mqtt_recv_msg(QMQTT::Message msg)
//{
//    QString recv_msg = "Topic:";
//        QString data = msg.payload();
//        recv_msg += msg.topic();
//        recv_msg += "    Payload:";
//        recv_msg += data;
//        ui->textBrowser->append(recv_msg);

//}

void MainWindow::on_sub_clicked()
{
    m_client->subscribe(ui->sub_topic->text(), 0);

    QString msg = "订阅主题 ";
       msg += ui->sub_topic->text();
       msg += " 成功";
       ui->textBrowser->append(msg);
}

void MainWindow::on_pub_clicked()
{

}
