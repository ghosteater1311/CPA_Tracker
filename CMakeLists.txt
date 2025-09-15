cmake_minimum_required(VERSION 3.16)
project(cpatracker LANGUAGES CXX)

# Turn on Qt automoc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Add source files
set(SOURCES
    main/main.cpp
    gui/UI.cpp
    pkg/Calculator.cpp
    pkg/Course.cpp
    pkg/Sort.cpp 
    pkg/Search.cpp
)

set(HEADERS
    gui/UI.h
    pkg/Calculator.h
    pkg/Course.h
    pkg/Search.h
    pkg/Sort.h
)

add_executable(cpatracker ${SOURCES} ${HEADERS})

# Tell the compiler where to find headers
target_include_directories(cpatracker PRIVATE
    ${CMAKE_SOURCE_DIR}/gui
    ${CMAKE_SOURCE_DIR}/pkg
    ${CMAKE_SOURCE_DIR}/main
)

# Link Qt libs
target_link_libraries(cpatracker PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
