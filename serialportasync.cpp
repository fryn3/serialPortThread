#include "serialportasync.h"


SerialPortAsyncPrivate::SerialPortAsyncPrivate(
        SerialPortThread *port, QObject *parent) : QObject(parent)
{
    connect(this, &SerialPortAsyncPrivate::sigSetSettings,
            port,          &SerialPortThread::setSettings);
    connect(this, &SerialPortAsyncPrivate::sigChangePortName,
            port,          &SerialPortThread::changePortName);
    connect(this, &SerialPortAsyncPrivate::sigStart,
            port,          &SerialPortThread::start);
    connect(this, &SerialPortAsyncPrivate::sigStop,
            port,          &SerialPortThread::stop);
    connect(this, &SerialPortAsyncPrivate::sigTxMsg,
            port,          &SerialPortThread::txMsg);
}

SerialPortAsync::SerialPortAsync(QObject *parent)
    : QObject(parent), _port(new SerialPortThread()),
      _portPrivate(new SerialPortAsyncPrivate(_port, this))
{
    _port->moveToThread(&_thread);
    connect(&_thread, &QThread::finished, _port, &QObject::deleteLater);
    _thread.start();
    connect(_port, &SerialPortThread::stoped, this, &SerialPortAsync::stoped);
    connect(_port, &SerialPortThread::started, this, &SerialPortAsync::started);
    connect(_port, &SerialPortThread::rxMsg, this, &SerialPortAsync::rxMsg);
}

void SerialPortAsync::setSettings(SerialPortThread::Settings s)
{
    _portPrivate->setSettings(s);
}

void SerialPortAsync::changePortName(QString portName)
{
    _portPrivate->changePortName(portName);
}

void SerialPortAsync::start()
{
    _portPrivate->start();
}

void SerialPortAsync::stop()
{
    _portPrivate->stop();
}

void SerialPortAsync::txMsg(QByteArray msg)
{
    _portPrivate->txMsg(msg);
}
