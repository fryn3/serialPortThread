#include "serialportthread.h"

SerialPortThread::SerialPortThread(Settings s, QObject *parent)
    : QSerialPort(parent) {
    setSettings(s);
    connect(this, &QSerialPort::readyRead, [this] {
        auto msg = readAll();
        emit rxMsg(msg);
    });
}

SerialPortThread::SerialPortThread(QString name,
                                   QSerialPort::BaudRate baudRate,
                                   QObject *parent)
    : SerialPortThread(Settings(name, baudRate), parent) { }

SerialPortThread::SerialPortThread(QSerialPort::BaudRate baudRate,
                                   QObject *parent)
    : SerialPortThread(Settings("", baudRate), parent) { }

void SerialPortThread::setSettings(SerialPortThread::Settings s) {
    bool started = isOpen();
    stop();
    QSerialPort::setPortName(s.name);
    QSerialPort::setBaudRate(s.baudRate);
    setDataBits(s.dataBits);
    setParity(s.parity);
    setStopBits(s.stopBits);
    setFlowControl(s.flowControl);
    if (started) {
        start();
    }
}

void SerialPortThread::setPortName(QString portName) {
    bool started = isOpen();
    stop();
    QSerialPort::setPortName(portName);
    if (started) {
        start();
    }
}

void SerialPortThread::setBaudRate(int baud) {
    bool started = isOpen();
    stop();
    QSerialPort::setBaudRate(baud);
    if (started) {
        start();
    }
}

void SerialPortThread::setParity(int value) {
    bool started = isOpen();
    stop();
    QSerialPort::setParity(Parity(value));
    if (started) {
        start();
    }
}

void SerialPortThread::start() {
    if (!open(QIODevice::ReadWrite)) {
        emit stoped(1); // error
        return;
    }
    emit started();
}

void SerialPortThread::stop() {
    if (isOpen()) {
        close();
        emit stoped(0);
    }
}

void SerialPortThread::txMsg(QByteArray txMsg) {
    write(txMsg);
}
