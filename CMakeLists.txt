cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(gas_inspector)

target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/sensor.c)
target_sources(app PRIVATE src/ble.c)

zephyr_include_directories(include)
zephyr_include_directories(src)
