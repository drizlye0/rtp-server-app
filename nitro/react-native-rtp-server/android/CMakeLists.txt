project(rtpserver)
cmake_minimum_required(VERSION 3.9.0)

set(PACKAGE_NAME rtpserver)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
  uvgrtp
  GIT_REPOSITORY https://github.com/drizlye0/uvgRTP.git
  GIT_TAG feat-add-android-libs
)

FetchContent_MakeAvailable(uvgrtp)

# Define C++ library and add all sources
add_library(${PACKAGE_NAME} SHARED
  src/main/cpp/cpp-adapter.cpp
  ../cpp/HybridRtpServer.cpp
)

# Add Nitrogen specs :)
include(${CMAKE_SOURCE_DIR}/../nitrogen/generated/android/rtpserver+autolinking.cmake)

# Set up local includes
include_directories("src/main/cpp" "../cpp")

find_library(LOG_LIB log)

# Link all libraries together
target_link_libraries(
        ${PACKAGE_NAME}
        ${LOG_LIB}
        android # <-- Android core
        uvgrtp
)
