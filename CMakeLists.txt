cmake_minimum_required(VERSION 3.16)

project(Sofomo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Sql)

qt_standard_project_setup()

qt_add_executable(appSofomo
	src/main.cpp
)

qt_add_qml_module(appSofomo
	URI Sofomo
	VERSION 1.0
	QML_FILES src/Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSofomo PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSofomo
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appSofomo
	PRIVATE Qt6::Quick Qt6::Sql
	IP2Data
)

if(NOT TARGET ip2Data)
	add_subdirectory(IP2Data)
endif()

if(NOT TARGET tests)
	add_subdirectory(tests)
endif()



include(GNUInstallDirs)
install(TARGETS appSofomo
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
