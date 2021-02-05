#ifndef SERIALPORTASYNC_H
#define SERIALPORTASYNC_H

#include "serialportthread.h"

#include <QObject>
#include <QThread>

class SerialPortAsyncPrivate;

class SerialPortAsync : public QObject
{
    Q_OBJECT
public:
    SerialPortAsync(QObject *parent = nullptr);
    SerialPortAsync(SerialPortThread::Settings s, QObject *parent = nullptr);
    SerialPortAsync(QString name,
                    QSerialPort::BaudRate baudRate = QSerialPort::Baud9600,
                    QObject *parent = nullptr);
    SerialPortAsync(QSerialPort::BaudRate baudRate, QObject *parent = nullptr);
    virtual ~SerialPortAsync();
public slots:
    void setSettings(SerialPortThread::Settings s);
    void setPortName(QString portName);
    void setBaudRate(int baud);
    void setParity(int value);
    /*!
     * \brief Открывает порт
     */
    void start();

    /*!
     * \brief Закрывает порт
     */
    void stop();
    void txMsg(QByteArray msg);
signals:
    void stoped(int status);
    void started();
    void rxMsg(QByteArray rxMsg);
private:
    QThread _thread;
    SerialPortThread *_port = nullptr;
    SerialPortAsyncPrivate *_portPrivate = nullptr;
};

class SerialPortAsyncPrivate : public QObject
{
    Q_OBJECT
    friend SerialPortAsync;
private:
    SerialPortAsyncPrivate(SerialPortThread *port, QObject *parent = nullptr);
signals:
    void sigSetSettings(SerialPortThread::Settings s);
    void sigSetPortName(QString portName);
    void sigSetBaudRate(int baud);
    void sigSetParity(int value);
    void sigStart();
    void sigStop();
    void sigTxMsg(QByteArray txMsg);

public slots:
    void setSettings(SerialPortThread::Settings s)  { emit sigSetSettings(s); }
    void setPortName(QString portName)              { emit sigSetPortName(portName); }
    void setBaudRate(int baud)                      { emit sigSetBaudRate(baud); }
    void setParity(int value)                       { emit sigSetParity(value); }
    void start()                                    { emit sigStart(); }
    void stop()                                     { emit sigStop(); }
    void txMsg(QByteArray msg)                      { emit sigTxMsg(msg); }
};

#endif // SERIALPORTASYNC_H
