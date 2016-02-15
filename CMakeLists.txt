cmake_minimum_required (VERSION 2.8.4) 

#variables
set(SRC_DIR "Code")
set(MAIN_SRC_DIR "${SRC_DIR}/Main")
set(DEBUG_BIN_DIR "Debug")
set(RELEASE_BIN_DIR "Release")

#project
project (guitar-learner)

#external libs
FIND_PACKAGE( Boost 1.46 COMPONENTS program_options REQUIRED )
FIND_PACKAGE( TLogger REQUIRED PATHS TLogger)
FIND_PACKAGE( THelper REQUIRED PATHS THelper)

#compiler options
set(CMAKE_CXX_FLAGS "-std=c++14")

if ("${NO_COVERAGE}" STREQUAL "true")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
else ("${NO_COVERAGE}" STREQUAL "true")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
endif ("${NO_COVERAGE}" STREQUAL "true")

set(NORMAL_WARNING_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")
set(EXTRA_WARNING_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")
#set(EXTRA_WARNING_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Weffc++ -Wextra")

set(CMAKE_CXX_FLAGS_DEBUG "${EXTRA_WARNING_FLAGS}")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

#tests
set(COVERAGE_COMMAND "gcov")

set(CTEST_MEMORYCHECK_COMMAND "valgrind")
set(CTEST_MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --quiet
--tool=memcheck --leak-check=yes --show-reachable=yes
--num-callers=100 --verbose --demangle=yes")

##submodules
link_directories(${CMAKE_BINARY_DIR}/${TLOGGER_LIBRARIES_DIR})
link_directories(${CMAKE_BINARY_DIR}/${THELPER_LIBRARIES_DIR})

#includes
include_directories(${SRC_DIR})
include_directories(${SRC_DIR}/one_minute_changes/inc/)
include_directories(${SRC_DIR}/main/inc)
include_directories(${TLOGGER_INCLUDE_DIRS})
include_directories(${THELPER_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIR})

set(BUILD_TESTS "false")
add_subdirectory(TLogger)
add_subdirectory(THelper)

#files
file(GLOB ONE_MINUTE_CHANGES_FILES ${SRC_DIR}/one_minute_changes/src/*.cpp)
file(GLOB MAIN_FILES ${SRC_DIR}/Main/src/*.cpp)
file(GLOB GLOBAL_MAIN_FILES "${MAIN_SRC_DIR}/*.cpp")

#executables
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	if ("${NO_COVERAGE}" STREQUAL "true")
	else ("${NO_COVERAGE}" STREQUAL "true")
		add_definitions(--coverage)
	endif ("${NO_COVERAGE}" STREQUAL "true")
	#test
	add_subdirectory(Test)
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
else (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	message(FATAL_ERROR "Invalid build type. Can be Debug | Release")
endif (${CMAKE_BUILD_TYPE} STREQUAL "Debug")

set(EXE_FILE ${PROJECT_NAME})

add_executable(${EXE_FILE} ${GLOBAL_MAIN_FILES} ${MAIN_FILES} ${ONE_MINUTE_CHANGES_FILES})

#dependencies
add_dependencies(${EXE_FILE} ${TLOGGER_TARGET})
add_dependencies(${EXE_FILE} ${THELPER_TARGET})

#libraries
TARGET_LINK_LIBRARIES(${EXE_FILE} ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES(${EXE_FILE} ${TLOGGER_LIBRARIES} )
TARGET_LINK_LIBRARIES(${EXE_FILE} ${THELPER_LIBRARIES} )

