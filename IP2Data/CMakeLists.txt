cmake_minimum_required(VERSION 3.16)

project(IP2Data)

add_library(${PROJECT_NAME}
	src/IP2DataManager.cpp
	src/Server.cpp
	include/IP2Data/IP2DataManager.h
	include/IP2Data/Server.h
	include/IP2Data/IpData.h)

target_link_libraries(${PROJECT_NAME}
	PRIVATE Qt6::Core Qt6::Network)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE include/IP2Data)


