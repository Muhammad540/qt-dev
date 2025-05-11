cmake_minimum_required(VERSION 3.18)
project(app LANGUAGES CXX) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_PREFIX_PATH "/home/ambi/Qt/6.9.0/gcc_64/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(app
    src/main.cpp
)
qt_add_resources(APP_RESOURCES resources.qrc)

target_sources(app PRIVATE ${APP_RESOURCES})
target_link_libraries(app PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
