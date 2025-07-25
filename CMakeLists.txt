cmake_minimum_required(VERSION 3.19)

project("qu3e")

set(qu3e_version 1.1)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

option(qu3e_build_shared "Build qu3e shared libraries" OFF)
option(qu3e_build_static "Build qu3e static libraries" ON)
option(qu3e_build_demo "Build qu3e demo" ON)
option(qu3e_bindings "Build qu3e bindings" ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


add_subdirectory(src)

if(qu3e_bindings)
	message(STATUS "Building qu3e bindings")
	set(DEV_MODULE Development.Module)
	find_package(Python 3.10 COMPONENTS Interpreter ${DEV_MODULE} REQUIRED)
	# Detect the installed nanobind package and import it into CMake
	execute_process(
		COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
		OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE nanobind_ROOT)
  	find_package(nanobind CONFIG REQUIRED)
	# add extension
	nanobind_add_module(qu3e_ext src/qu3e_ext.cpp)
	target_link_libraries(qu3e_ext PRIVATE qu3e)
endif()


if(qu3e_build_demo)
	find_package(OpenGL REQUIRED)
	add_subdirectory(freeglut)
	add_subdirectory(demo)
	add_subdirectory(imgui)
endif()
