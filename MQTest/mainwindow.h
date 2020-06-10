#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtMqtt/qmqttclient.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_connect_clicked();

    void mqtt_connect_success();

    void mqtt_disconnect();

    void mqtt_sub_success(QString topic, quint8 qos = 0);

//    void mqtt_recv_msg(QMQTT::Message msg);

    void on_sub_clicked();

    void on_pub_clicked();

private:
    Ui::MainWindow *ui;
    QMqttClient *m_client;
};

#endif // MAINWINDOW_H
