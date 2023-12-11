# Sofomo

#Description:

Simple desktop app that displays basic geological data from URL address or IP.
App connects to http://api.ipstack.com/" to retreive data. Secret API key of webiste is hardcoded in app.
When data is retreived it is automatically saved in database. Database name is created in app directory and it's name is "SofomoDb"

#Install and run

##Requirement

Qt6
CMake 3.16

##Install/run

App is created with CMakeList.

Example compilation with ninja:

download repo

mkdir buildFolder

cd buildFolder

cmake -G Ninja ../Sofomo

ninja

Run unit tests:
./tests/tests

Run app
./appSofomo
