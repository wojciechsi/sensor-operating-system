#include <iostream>
#include "manager.hpp"
#include "serialSensor.hpp"


Manager::Manager() {
    this->configuration.load("/home/wojtek/studia/inzynier/sensor-operating-system/sos_config.json"); //@todo: pass as command line argument
    this->configuration.print();

    this->sensors = this->configuration.createSensors();
    this->createSerializers();
}



void Manager::runSensors() {
    std::cout << "Sensors amount: " << this->sensors.size() << std::endl;
    for (auto& sensor : this->sensors) {
        this->sensor_threads.emplace_back(&Sensor::run, sensor.get());
    }
}

std::string Manager::getLastValuesOfAllSensors(){
    std::string lastValues;
    for (auto& sensor : this->sensors) {
        if(sensor.get()->hasData()) {
            lastValues.append(sensor.get()->getLatestData().lock()->toString());
            lastValues.append(",");
        }

    }
    return lastValues;
}

void Manager::stopSensors() {
    for (auto& sensor : this->sensors) {
        sensor.get()->stop();
    }
}

void Manager::createSerializers() {
    for (auto& sensor : sensors) {
        serializers.emplace_back(std::make_shared<Serializer>(sensor));
    }
}