#include "serialportasync.h"


SerialPortAsyncPrivate::SerialPortAsyncPrivate(
        SerialPortThread *port, QObject *parent) : QObject(parent) {
    connect(this, &SerialPortAsyncPrivate::sigSetSettings,
            port,          &SerialPortThread::setSettings);
    connect(this, &SerialPortAsyncPrivate::sigSetPortName,
            port,          &SerialPortThread::setPortName);
    connect(this, &SerialPortAsyncPrivate::sigSetBaudRate,
            port,          &SerialPortThread::setBaudRate);
    connect(this, &SerialPortAsyncPrivate::sigSetParity,
            port,          &SerialPortThread::setParity);
    connect(this, &SerialPortAsyncPrivate::sigStart,
            port,          &SerialPortThread::start);
    connect(this, &SerialPortAsyncPrivate::sigStop,
            port,          &SerialPortThread::stop);
    connect(this, &SerialPortAsyncPrivate::sigTxMsg,
            port,          &SerialPortThread::txMsg);
}

SerialPortAsync::SerialPortAsync(SerialPortThread::Settings s, QObject *parent)
    : QObject(parent), _port(new SerialPortThread(s)),
      _portPrivate(new SerialPortAsyncPrivate(_port, this)) {
    _port->moveToThread(&_thread);
    connect(&_thread, &QThread::finished, _port, &QObject::deleteLater);
    _thread.start();
    connect(_port, &SerialPortThread::stoped, this, &SerialPortAsync::stoped);
    connect(_port, &SerialPortThread::started, this, &SerialPortAsync::started);
    connect(_port, &SerialPortThread::rxMsg, this, &SerialPortAsync::rxMsg);
}

SerialPortAsync::SerialPortAsync(QObject *parent)
    : SerialPortAsync(SerialPortThread::Settings(), parent) { }

SerialPortAsync::SerialPortAsync(QString name, QSerialPort::BaudRate baudRate,
                                 QObject *parent)
    : SerialPortAsync(SerialPortThread::Settings(name, baudRate), parent) { }

SerialPortAsync::SerialPortAsync(QSerialPort::BaudRate baudRate,
                                 QObject *parent)
    : SerialPortAsync(SerialPortThread::Settings("", baudRate), parent) { }

SerialPortAsync::~SerialPortAsync() {
    _thread.quit();
    _thread.wait();
}

void SerialPortAsync::setSettings(SerialPortThread::Settings s) {
    _portPrivate->setSettings(s);
}

void SerialPortAsync::setPortName(QString portName) {
    _portPrivate->setPortName(portName);
}

void SerialPortAsync::setBaudRate(int baud) {
    _portPrivate->setBaudRate(baud);
}

void SerialPortAsync::setParity(int value) {
    _portPrivate->setParity(value);
}

void SerialPortAsync::start() {
    _portPrivate->start();
}

void SerialPortAsync::stop() {
    _portPrivate->stop();
}

void SerialPortAsync::txMsg(QByteArray msg) {
    _portPrivate->txMsg(msg);
}
