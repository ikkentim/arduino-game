cmake_minimum_required(VERSION 3.2)
project(ArduinoGame)

if(WIN32)

else()
    set(ENV{PATH} "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin")
    set(PLATFORMIO_CMD "/usr/local/bin/platformio")
endif()

include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/variants/standard")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/cores/arduino")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-atmelavr/avr/include")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-atmelavr/bfd/include")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-atmelavr/lib/gcc/avr/4.8.1/include")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-atmelavr/lib/gcc/avr/4.8.1/include-fixed")
include_directories(".pioenvs/uno/")

add_definitions(-DF_CPU=16000000L)
add_definitions(-DARDUINO_ARCH_AVR)
add_definitions(-DARDUINO_AVR_UNO)
add_definitions(-DARDUINO=10606)
add_definitions(-DPLATFORMIO=020304)
add_definitions(-D__AVR_ATmega328P__)

add_custom_target(
    PLATFORMIO_BUILD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOAD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target upload
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_CLEAN ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoavr/libraries/EEPROM/")

add_subdirectory (src)