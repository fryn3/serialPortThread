#ifndef SERIALPORTTHREAD_H
#define SERIALPORTTHREAD_H

#include <QSerialPort>

class SerialPortThread : public QSerialPort
{
    Q_OBJECT
public:
    struct Settings {
        QString name;
        QSerialPort::BaudRate baudRate;
        QSerialPort::DataBits dataBits;
        QSerialPort::Parity parity;
        QSerialPort::StopBits stopBits;
        QSerialPort::FlowControl flowControl;
        Settings(QString _name = "", QSerialPort::BaudRate _baudRate = Baud9600, QSerialPort::DataBits _dataBits = Data8,
                 QSerialPort::Parity _parity = NoParity, QSerialPort::StopBits _stopBits = OneStop, QSerialPort::FlowControl _flowControl = NoFlowControl)
            : name(_name), baudRate(_baudRate), dataBits(_dataBits), parity(_parity), stopBits(_stopBits), flowControl(_flowControl) {}
    };

    SerialPortThread(Settings s = Settings(), QObject *parent = nullptr);
    SerialPortThread(QString name, QSerialPort::BaudRate baudRate = Baud9600, QObject *parent = nullptr);
    SerialPortThread(QSerialPort::BaudRate baudRate, QObject *parent = nullptr);
public slots:
    void setSettings(Settings s);
    void setPortName(QString portName);
    void setBaudRate(int baudRate);
    void start();
    void stop();
    void txMsg(QByteArray txMsg);
signals:
    void stoped(int status);
    void started();
    void rxMsg(QByteArray rxMsg);
};

#endif // SERIALPORTTHREAD_H
