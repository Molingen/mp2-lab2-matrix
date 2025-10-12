cmake_minimum_required(VERSION 3.10)

option(BUILD_SAMPLES ON)

set(PROJECT_NAME matrix)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()  # defines BUILD_TESTING

set(MP2_TESTS   "test_${PROJECT_NAME}")
set(MP2_CUSTOM_PROJECT "${PROJECT_NAME}")
set(MP2_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(MSVC)
	add_compile_options(/O2)
else()
	add_compile_options(-O2)
endif()

find_package(OpenMP QUIET)
if(OPENMP_FOUND)
	message(STATUS "OpenMP found")
	add_compile_definitions(USE_OPENMP)
else()
	message(STATUS "OpenMP not found - continuing without OpenMP")
endif()

add_subdirectory(include)

if(BUILD_SAMPLES)
	add_subdirectory(samples)
endif()

if(BUILD_TESTING)
    add_subdirectory(gtest)
	add_subdirectory(test)
endif()


# REPORT
message( STATUS "")
message( STATUS "General configuration for ${PROJECT_NAME}")
message( STATUS "======================================")
message( STATUS "")
message( STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message(STATUS "   OpenMP found: ${OPENMP_FOUND}")
message( STATUS "")
