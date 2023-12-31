#include <iostream>
#include <regex>
#include "serialSensor.hpp"


SerialSensor::SerialSensor(std::string name, std::string port, int baudrate, uint32_t timeout) : Sensor(name) {
    this->serial.setPort(port);
    this->serial.setBaudrate(baudrate);
    this->serial.setTimeout(serial::Timeout::max(), timeout, 0, timeout, 0);
}

void SerialSensor::reciveLine() {
        auto line = this->serial.readline();
        if (line.empty()) return;
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.cend());

        if (this->isRegexFilterEnabled()) {
            std::regex regex(this->getRegexFilter());
            if (!std::regex_search(line, regex)) {
                return;
            }
        }
        this->pushData(std::make_shared<SerialData>(line));
}



void SerialSensor::run() {
    prepareSerialConnection();

    while (! this->getStopFlag()) {
        reciveLine();
    }
}

void SerialSensor::prepareSerialConnection()
{
    try
    {
        if (!this->serial.isOpen())
            this->serial.open();
    }
    catch (serial::IOException e)
    {
        std::string errorMessage = "Serial port " + this->serial.getPort() + " is unavaliable";
        throw std::runtime_error(errorMessage);
    }
}

SerialData::SerialData(std::string data) : Data() {
    this->line = data;
}

std::string SerialData::toString() {
    auto baseString = Data::toString();
    return baseString + this->line;
}
