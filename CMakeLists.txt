cmake_minimum_required(VERSION 3.10)

# Set the project name
project(PacketSequenceHandler VERSION 0.1.0 LANGUAGES C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Define the source files
set(SOURCES
    main.cpp
    src/PacketSequenceHandler.cpp)

include(CTest)
enable_testing()
    
add_executable(PacketSequenceHandler ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
