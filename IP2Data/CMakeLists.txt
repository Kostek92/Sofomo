cmake_minimum_required(VERSION 3.16)

project(IP2Data)
find_package(Qt6 REQUIRED COMPONENTS Sql)

add_library(${PROJECT_NAME}
	src/IP2DataManager.cpp
	src/Server.cpp
	src/WebAddress.cpp
	include/IP2Data/IP2DataManager.h
	include/IP2Data/Server.h
	include/IP2Data/WebAddress.h
	include/IP2Data/IpData.h
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE Qt6::Core Qt6::Network Qt6::Sql)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE include/IP2Data)


