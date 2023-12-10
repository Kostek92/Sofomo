cmake_minimum_required(VERSION 3.14)
project(tests)

find_package(Qt6 REQUIRED COMPONENTS Test)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

enable_testing(true)

add_executable(${PROJECT_NAME}
	IP2Data/src/ServerTest.cpp
	IP2Data/src/WebAddressTest.cpp
	IP2Data/src/main.cpp
	IP2Data/include/ServerTest.h
	IP2Data/include/WebAddressTest.h
)
add_test(NAME ServerTest COMMAND ServerTest)
add_test(NAME WebAddressTest COMMAND WebAddressTest)

target_include_directories(${PROJECT_NAME} PRIVATE IP2Data/include)
target_include_directories(${PROJECT_NAME} PRIVATE IP2Data/src)

target_link_libraries(${PROJECT_NAME}
 PRIVATE
  Qt::Test Qt6::Core Qt6::Network IP2Data)
