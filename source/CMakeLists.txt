cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project(Engine VERSION 0.1.0 LANGUAGES CXX C)

#########################################
#				Defination				#
#########################################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_definitions(GLFW_INCLUDE_NONE)
add_compile_definitions(SPDLOG_COMPILED_LIB)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_compile_definitions(JUICE_PLATFORM_LINUX)
endif()

if(WIN32)
    add_compile_definitions(JUICE_PLATFORM_WINDOW)
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++17")
	add_compile_definitions(SQ_RELEASE)
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -ggdb3 -Wall -std=c++17")
	add_compile_definitions(SQ_DEBUG)
endif()

#########################################
#				Dependencies			#
#########################################
set(DEPENDENCIES_DIR "${PROJECT_SOURCE_DIR}/dependencies")
find_library(glfwlib libglfw.so PATHS "${DEPENDENCIES_DIR}")
find_library(dllib libdl-2.33.so PATHS "${DEPENDENCIES_DIR}")

#########################################
#				Includes				#
#########################################
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/juice")
set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor")
include_directories(${SOURCE_DIR})
include_directories(${VENDOR_DIR})
include_directories(${VENDOR_DIR}/glad)
include_directories(${VENDOR_DIR}/glm)
include_directories(${VENDOR_DIR}/spdlog/include)
include_directories(${VENDOR_DIR}/stb)

add_subdirectory(${VENDOR_DIR}/glad)
add_subdirectory(${VENDOR_DIR}/spdlog)
add_subdirectory(${VENDOR_DIR}/stb)

#########################################
#				Build SQ				#
#########################################
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp")

add_library(juice STATIC ${SOURCE_FILES})
target_link_libraries(juice "glad")
target_link_libraries(juice "stb")
target_link_libraries(juice "spdlog")
target_link_libraries(juice ${dllib})
target_link_libraries(juice ${glfwlib})
