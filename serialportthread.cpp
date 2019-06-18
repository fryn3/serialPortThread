#include "serialportthread.h"

SerialPortThread::SerialPortThread(Settings s, QObject *parent)
    : QSerialPort(s.name, parent)
{
    setBaudRate(s.baudRate);
    setDataBits(s.dataBits);
    setParity(s.parity);
    setStopBits(s.stopBits);
    setFlowControl(s.flowControl);
    connect(this, &QSerialPort::readyRead, [this] {
        auto msg = readAll();
        emit rxMsg(msg);
    });
    connect(this, &SerialPortThread::stoped, [this] () { m_loop.exit(); });
}

void SerialPortThread::start()
{
    if (!open(QIODevice::ReadWrite)) {
        emit stoped(1); // error
        return;
    }
    emit started();
    m_loop.exec();
}

void SerialPortThread::stop()
{
    if (isOpen()) {
        close();
    }
    m_loop.exit();
    emit stoped(0);
}

void SerialPortThread::txMsg(QByteArray txMsg)
{
    write(txMsg);
}
