#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtMqtt/qmqttclient.h"
#include "CMqttClientThread.h"
#include "CCanBusDeviceThread.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void SlotSubscribeMsg(const QByteArray &kqMessageByteArray, const QMqttTopicName &kqTopicName);
    void mqtt_connect_success();
private slots:
    void on_connect_clicked();

    void mqtt_disconnect();

    void mqtt_sub_success(QString topic, quint8 qos = 0);


    void on_sub_clicked();

    void on_pub_clicked();

private:
    Ui::MainWindow *ui;
//    QThread *m_pMqttThread;
    QMqttClient *m_pCMqttClientThread;
//    QMqttClient *m_client;
    QString m_strReceivedMsg;
    // can
    QList<CCanBusDeviceThread*> m_qCanBusDeviceThreadList;
};

#endif // MAINWINDOW_H
