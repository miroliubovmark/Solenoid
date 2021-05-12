cmake_minimum_required(VERSION 3.5)

set(PROJECT MagneticField)
set(MAIN MagneticField_EXECUTABLE)
set(TEST_PROJECT MagneticFieldTest)

project(${PROJECT})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(${PROJECT}_HEADER_FILES
    MagneticFieldStable.h

    CIntegration.h
)

set(${PROJECT}_SOURCE_FILES
    CIntegration.cpp
)

include_directories("/home/mark/MagneticFieldModeling/Source/MagneticFieldModeling/")


add_library(${PROJECT} SHARED ${${PROJECT}_HEADER_FILES} ${${PROJECT}_SOURCE_FILES})
add_executable(${MAIN} "main.cpp")
add_executable(${TEST_PROJECT} ${TEST_PROJECT}.cpp)

target_link_libraries(${PROJECT} Tools)
target_link_libraries(${TEST_PROJECT} Tools)
target_link_libraries(${MAIN} Tools)


target_link_libraries(${TEST_PROJECT} ${PROJECT})
target_link_libraries(${MAIN} ${PROJECT})


