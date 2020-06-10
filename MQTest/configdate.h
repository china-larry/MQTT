#ifndef CONFIGDATE_H
#define CONFIGDATE_H
#include <QString>
struct SCanBusDeviceStruct
{
    QString strPlugin;// 接口类型
    QString strInterfaceName;// 接口名称
    qint32 iCanId;// CAN总线标识符
    qint32 iBitRate;// 波特率
};



#endif // CONFIGDATE_H


