cmake_minimum_required (VERSION 2.8) 

#variables
set(SRC_DIR "Code")
set(MAIN_SRC_DIR "${SRC_DIR}/Main/src")
set(MAIN_FILE "${MAIN_SRC_DIR}/main.cpp")
set(DEBUG_BIN_DIR "Debug")
set(RELEASE_BIN_DIR "Release")

#project
project (guitar-learner)

#externial libs
#FIND_PACKAGE( Boost 1.54 COMPONENTS date_time REQUIRED )

#compiler options
set(CMAKE_CXX_FLAGS "-std=c++1y")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")

set(NORMAL_WARNING_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")
set(EXTRA_WARNING_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Weffc++ -Wextra")

set(CMAKE_CXX_FLAGS_DEBUG "${EXTRA_WARNING_FLAGS}")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

#tests
set(COVERAGE_COMMAND "gcov")

set(CTEST_MEMORYCHECK_COMMAND "valgrind")
set(CTEST_MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --quiet
--tool=memcheck --leak-check=yes --show-reachable=yes
--num-callers=100 --verbose --demangle=yes")

#includes
include_directories(${SRC_DIR})

#files
file(GLOB ONE_MINUTE_CHANGES_FILES ${SRC_DIR}/one_minute_changes/src/*.cpp)

#executables
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	add_definitions(--coverage)
	file(MAKE_DIRECTORY ${DEBUG_BIN_DIR})
	set(EXE_FILE ${DEBUG_BIN_DIR}/${PROJECT_NAME})

	#test
	add_subdirectory(Test)
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
	file(MAKE_DIRECTORY ${RELEASE_BIN_DIR})
        set(EXE_FILE ${RELEASE_BIN_DIR}/${PROJECT_NAME})
endif (${CMAKE_BUILD_TYPE} STREQUAL "Debug")

add_executable(${EXE_FILE} ${MAIN_FILE})

#libraries
TARGET_LINK_LIBRARIES(${EXE_FILE} ${Boost_LIBRARIES} )

