cmake_minimum_required(VERSION 3.5)
project(Tools)
set(TEST_PROJECT_NAME ToolsTest)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

#find_library(FFTW_LIB REQUIRED)

#include_directories(${fftw_INCLUDES})

set(HEADER_FILES
    ToolsStable.h

    UBaseTypes.h
    CMathFunc.h
    CVector3D.h
    CVector4D.h
    CPoint3D.h
)

set(SOURCE_FILES
    CMathFunc.cpp
    CVector3D.cpp
    CVector4D.cpp
    CPoint3D.cpp
)

set(Oscilloscope_PCH_HEADER
    ToolsStable.h
)

# Add sources to the test project
set(${TEST_PROJECT_NAME}_SOURCES
        UToolsTest.cpp
)

# Add libraries to the test project
set(${TEST_PROJECT_NAME}_LIBS
        Tools
)


include_directories("/home/mark/QtProjects/MagneticField/")
add_library(Tools SHARED ${HEADER_FILES} ${SOURCE_FILES})

add_executable(${TEST_PROJECT_NAME} ${TEST_PROJECT_NAME}.cpp)

target_link_libraries(${TEST_PROJECT_NAME} Tools)
#target_link_libraries(Tools fftw)


# Add BOOST

#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
#find_package(Boost 1.65.0 COMPONENTS )

#if(Boost_FOUND)
#    message("BOOST found")

#    include_directories(${Boost_INCLUDE_DIRS})
#    target_link_libraries(Tools ${Boost_LIBRARIES})
#else()
#    message("BOOST NOT found")
#endif()
