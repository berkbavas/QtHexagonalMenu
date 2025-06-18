cmake_minimum_required(VERSION 3.25.1)

project(QtHexagonalMenu VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "$ENV{Qt6_DIR}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE SOURCES Source/*.cpp *.qrc)

find_package(Qt6 COMPONENTS Core Widgets Gui REQUIRED)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Source")

add_executable(QtHexagonalMenu ${SOURCES})

target_link_libraries(QtHexagonalMenu Qt6::Core Qt6::Widgets)

add_custom_command(TARGET QtHexagonalMenu
    POST_BUILD COMMAND
    Qt6::windeployqt
    --dir "$<TARGET_FILE_DIR:QtHexagonalMenu>"
    "$<TARGET_FILE_DIR:QtHexagonalMenu>/$<TARGET_FILE_NAME:QtHexagonalMenu>"
)
