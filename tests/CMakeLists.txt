cmake_minimum_required(VERSION 3.14)
project(tests)

find_package(Qt6 REQUIRED COMPONENTS Test)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

enable_testing(true)

add_executable(tests src/IP2Data/ServerTest.cpp)
add_test(NAME ServerTest COMMAND ServerTest)

target_link_libraries(tests
 PRIVATE
  Qt::Test Qt6::Core Qt6::Network
  IP2Data)
