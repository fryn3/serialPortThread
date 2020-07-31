#include "serialportthread.h"

SerialPortThread::SerialPortThread(Settings s, QObject *parent)
    : QSerialPort(parent)
{
    setSettings(s);
    connect(this, &QSerialPort::readyRead, [this] {
        auto msg = readAll();
        emit rxMsg(msg);
    });
}

void SerialPortThread::setSettings(SerialPortThread::Settings s)
{
    bool started = isOpen();
    stop();
    setPortName(s.name);
    setBaudRate(s.baudRate);
    setDataBits(s.dataBits);
    setParity(s.parity);
    setStopBits(s.stopBits);
    setFlowControl(s.flowControl);
    if (started) {
        start();
    }
}

void SerialPortThread::changePortName(QString portName)
{
    bool started = isOpen();
    stop();
    setPortName(portName);
    if (started) {
        start();
    }
}

void SerialPortThread::start()
{
    if (!open(QIODevice::ReadWrite)) {
        emit stoped(1); // error
        return;
    }
    emit started();
}

void SerialPortThread::stop()
{
    if (isOpen()) {
        close();
        emit stoped(0);
    }
}

void SerialPortThread::txMsg(QByteArray txMsg)
{
    write(txMsg);
}
