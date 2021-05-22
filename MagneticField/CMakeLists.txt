cmake_minimum_required(VERSION 3.5)

set(PROJECT MagneticField)

set(MAIN main)
set(TEST_PROJECT MagneticFieldTest)
set(SIMULATION Simulation)
set(FORCE_PROFILE Force_profile)
set(LINES_OF_FORCE LinesOfForce)

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


# Include Project directory

set(MARK_HOSTNAME mark-HP-EliteBook-1050-G1)
set(DIMA_HOSTNAME mark-MBP)

cmake_host_system_information(RESULT _HOSTNAME QUERY HOSTNAME)
message(${_HOSTNAME})

if(${_HOSTNAME} STREQUAL ${MARK_HOSTNAME})
    include_directories("/home/mark/QtProjects/MagneticField/")
elseif(${_HOSTNAME} STREQUAL ${DIMA_HOSTNAME})
    include_directories("/home/mark/MagneticFieldModeling/Source/MagneticFieldModeling/")
endif()


add_library(${PROJECT} SHARED ${${PROJECT}_HEADER_FILES} ${${PROJECT}_SOURCE_FILES})
add_executable(${MAIN} "main.cpp")
add_executable(${TEST_PROJECT} ${TEST_PROJECT}.cpp)
add_executable(${SIMULATION} ${SIMULATION}.cpp)
add_executable(${FORCE_PROFILE} ${FORCE_PROFILE}.cpp)
add_executable(${LINES_OF_FORCE} ${LINES_OF_FORCE}.cpp)

target_link_libraries(${PROJECT} Tools)
target_link_libraries(${TEST_PROJECT} Tools)
target_link_libraries(${MAIN} Tools)
target_link_libraries(${SIMULATION} Tools)
target_link_libraries(${FORCE_PROFILE} Tools)
target_link_libraries(${LINES_OF_FORCE} Tools)


target_link_libraries(${TEST_PROJECT} ${PROJECT})
target_link_libraries(${MAIN} ${PROJECT})
target_link_libraries(${SIMULATION} ${PROJECT})
target_link_libraries(${FORCE_PROFILE} ${PROJECT})
target_link_libraries(${LINES_OF_FORCE} ${PROJECT})
