cmake_minimum_required(VERSION 3.16)

project(IP2Data)

add_library(${PROJECT_NAME}
	src/IP2DataManager.cpp
	src/Server.cpp
	include/public/IP2Data/IP2DataManager.h
	include/private/Server.h)

target_link_libraries(${PROJECT_NAME}
	PRIVATE Qt6::Core)

target_include_directories(${PROJECT_NAME} PUBLIC include/public/)
target_include_directories(${PROJECT_NAME} PRIVATE include/public/IP2Data)
target_include_directories(${PROJECT_NAME} PRIVATE include/private)


