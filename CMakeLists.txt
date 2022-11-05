## ========================================================
##
## FILE:			/CMakeLists.txt
##
## AUTHORS:			Jaycie Ewald
##
## PROJECT:			DOSLIB
##
## LICENSE:			ACSL 1.4
##
## DESCRIPTION:		CMake project definition.
##
## LAST EDITED:		November 4th, 2022
##
## ========================================================

##
## CMake Startup
##

## CMake version gate
cmake_minimum_required(VERSION 3.13)

## Debug mode
set(CMAKE_BUILD_TYPE Debug)

## Determine what's compiling us
if(CMAKE_GENERATOR STREQUAL "Watcom WMake")
	set(WATCOM TRUE)
	set(COMPILER_EXTENSION w)
elseif(CMAKE_C_COMPILER_ID STREQUAL "DJGPP")
	set(DJGPP TRUE)
	set(COMPILER_EXTENSION d)
else()
	message(FATAL_ERROR "DOSLIB can only be compiled with Open Watcom v2 or DJGPP.")
endif()

## Processor architechture gate
if(CMAKE_SYSTEM_PROCESSOR STREQUAL I86)
	message(FATAL_ERROR "DOSLIB can only be compiled in 32-bit protected mode.")
endif()

## DOS target gate
if(NOT CMAKE_SYSTEM_NAME STREQUAL DOS)
	message(FATAL_ERROR "DOSLIB can only compile under DOS.")
endif()

##
## DOSLIB
##

## Define project
project(DOSLIB LANGUAGES C)

## C compile options & definitions
if(WATCOM)
	add_compile_options("$<$<COMPILE_LANGUAGE:C>:-za99>")
	add_compile_options("$<$<COMPILE_LANGUAGE:C>:-bt=dos32x>")
	add_compile_options("$<$<COMPILE_LANGUAGE:C>:-bcl=dos32x>")
endif()

## Set project names
set(TEST001 test001${COMPILER_EXTENSION})

## Set directory paths
set(DOSLIB_INC_DIR ${CMAKE_SOURCE_DIR}/source/inc)

## Include base DOSLIB header directory
include_directories(${DOSLIB_INC_DIR})

##
## Test001
##

## Add source files
set(TEST001_SRC
	${CMAKE_SOURCE_DIR}/source/test001.c
)

## Add executable
add_executable(${TEST001} ${TEST001_SRC})

## Set output directory
set_target_properties(${TEST001}
	PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/builds"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/builds"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/builds"
)
