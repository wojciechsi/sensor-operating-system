#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <string>
#include <chrono>
#include <fstream>
#include "sensor.hpp"

const std::string outputDirectoryName = "output";
const int milisecondsAtferBufferUnderflow = 1000;

class Serializer {
    std::string baseFilePath;
    std::chrono::time_point<std::chrono::system_clock> fileCreationTime;
    int fileCounter = 0;
    std::weak_ptr<Sensor> sensorReference;
    std::jthread serializationThread;
    std::ofstream file;
    std::queue<std::shared_ptr<Data>> dataQueue;
    std::atomic<bool> stopFlag = false;
public:
    Serializer(std::shared_ptr<Sensor>& sensor);
    ~Serializer();
private:
    std::string makeFileName ();

    void manageWriting();
};

#endif