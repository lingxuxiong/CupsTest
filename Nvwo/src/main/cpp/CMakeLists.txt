# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(myNpmLib)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

set(CUPS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/cups/include)
set(CUPS_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/cups/libs/${OHOS_ARCH})
message("CMAKE_CURRENT_SOURCE_DIR:" + ${CMAKE_CURRENT_SOURCE_DIR})
message("CUPS_INCLUDE_DIRS:" + ${CUPS_INCLUDE_DIR})
message("CUPS_LIBRARIES:" + ${CUPS_LIBRARY_DIR})

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include
                    ${CUPS_INCLUDE_DIR})

add_library(mycups SHARED IMPORTED)
set_target_properties(mycups
    PROPERTIES
    IMPORTED_LOCATION ${CUPS_LIBRARY_DIR}/libcups.z.so)

add_library(nvwo SHARED napi_init.cpp)

target_link_libraries(nvwo PUBLIC libace_napi.z.so libhilog_ndk.z.so mycups)