cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)

project(skyline CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH 
    ${PROJECT_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH} 
    )

include(CompilerConfiguration)
include(CPPCheck)

## include cmake file
include(cmake/CompilerConfiguration.cmake)
include(cmake/CppcheckConfiguration.cmake)
include(cmake/PrependFilePaths.cmake)

## organize multiple files
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

## platform specific settings
if (TARGET_PLATFORM_UNIX)
    if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
      # GNU/Linux 
       set(LINUX true)
       add_definitions(-DLINUX=1)
    endif() # ${CMAKE_SYSTEM_NAME} MATCHES "Linux"
endif() # TARGET_PLATFORM_UNIX

## set up directoy structure
set(VENDOR_DIR ${CMAKE_SOURCE_DIR}/vendor)

if (TARGET_PLATFORM_MAC)
   
    # Configure toolchain for building for Mac platform	
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

    add_definitions(-DTARGET_PLATFORM_MAC=1)
    add_definitions(-DDARWIN=1)   # for third party code which expects DARWIN as Mac OSX identifier
elseif (TARGET_PLATFORM_UNIX)  #including GNU/Linux 
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wunused-variable ")

    # Configure toolchain for building for generic Unix platform
    add_definitions(-DTARGET_PLATFORM_UNIX=1)

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wno-multichar")

endif() # platform

## add directoies to build the code
add_subdirectory(apps)
add_subdirectory(modules)
add_subdirectory(test)

