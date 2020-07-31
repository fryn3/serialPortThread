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
public slots:
    void setSettings(SerialPortThread::Settings s);
    void changePortName(QString portName);
    void start();
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
    void sigChangePortName(QString portName);
    void sigStart();
    void sigStop();
    void sigTxMsg(QByteArray txMsg);

public slots:
    void setSettings(SerialPortThread::Settings s)  { emit sigSetSettings(s); }
    void changePortName(QString portName)           { emit sigChangePortName(portName); }
    void start()                                    { emit sigStart(); }
    void stop()                                     { emit sigStop(); }
    void txMsg(QByteArray msg)                      { emit sigTxMsg(msg); }
};

#endif // SERIALPORTASYNC_H
