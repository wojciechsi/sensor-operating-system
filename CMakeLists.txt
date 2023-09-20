cmake_minimum_required(VERSION 3.0.0)
project(sensor-operating-system VERSION 0.1.0 LANGUAGES C CXX)

#include(CTest)
#enable_testing()

set(CMAKE_CXX_STANDARD 23)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED
  PTHREADS REQUIRED)

add_executable(sensor-operating-system
            main.cpp
            manager.cpp
            sensor.cpp
            data.cpp
            serialSensor.cpp
            )

include(FetchContent)
FetchContent_Declare(
  serial
  GIT_REPOSITORY https://github.com/wjwwood/serial.git
  GIT_TAG 10ac4e1c25c2cda1dc0a32a8e12b87fd89f3bb4f
)
FetchContent_makeavailable(serial)

target_link_libraries(sensor-operating-system
  serial)

include_directories(/home/wojtek/studia/inzynier/sensor-operating-system/build/_deps/serial-src/include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)