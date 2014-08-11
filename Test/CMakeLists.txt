set(TEST_DIR ".")
set(TEST_EXE_DIR "${TEST_DIR}/Exe")
set(TEST_SRC_DIR "${TEST_DIR}/src")
set(TEST_INC_DIR "${TEST_DIR}/inc")
set(TEST_EXE ${TEST_EXE_DIR}/Tester)

find_library(GTEST_LIBRARY 
                NAMES gtest 
                      libgtest 
                      libgtest.a 
                PATHS "${GTEST_DIR}"
                PATH_SUFFIXES lib)

message(STATUS GTEST_LIBRARY ${GTEST_LIBRARY})

set(GMOCK_DIR /usr/src/gmock)
set(GTEST_DIR /usr/src/gtest)
set(GMOCK_SOURCE_DIR ${GMOCK_DIR}/src)
set(GTEST_SOURCE_DIR ${GTEST_DIR}/src)

set(LIB_GMOCK gmock)

#projects parts
set(TESTS_POSTFIX Tests)
set(MOCKS_POSTFIX Mocks)

set(ONE_MINUTE_CHANGES_TESTS_DIR one_minute_changes${TESTS_POSTFIX})
set(ONE_MINUTE_CHANGES_MOCKS_DIR one_minute_changes${MOCKS_POSTFIX})

#project includes
include_directories(${PROJECT_SOURCE_DIR}/${SRC2_DIR}/GmockTest)
include_directories(${TEST_INC_DIR}/${ONE_MINUTE_CHANGES_MOCKS_DIR}/)

#externial libs

set(CMAKE_CXX_FLAGS_DEBUG "${NORMAL_WARNING_FLAGS}")

include_directories(${GTEST_DIR})
add_subdirectory(${GMOCK_DIR} gmock)

set(CMAKE_CXX_FLAGS_DEBUG "${EXTRA_WARNING_FLAGS}")

#test files
file(GLOB MAIN_TEST_FILES ${TEST_SRC_DIR}/*.cpp)

file(GLOB ONE_MINUTE_CHANGES_TEST_FILES ${TEST_SRC_DIR}/${ONE_MINUTE_CHANGES_TESTS_DIR}/*.cpp)

#tests
enable_testing()

file(MAKE_DIRECTORY ${TEST_EXE_DIR})

add_executable(${TEST_EXE} ${MAIN_TEST_FILES} ${ONE_MINUTE_CHANGES_FILES} ${ONE_MINUTE_CHANGES_TEST_FILES})
target_link_libraries(${TEST_EXE} ${LIB_GMOCK})
TARGET_LINK_LIBRARIES(${TEST_EXE} ${Boost_LIBRARIES} )
add_test(gtests ${TEST_EXE}) 

set(COVERAGE_DIR coverage)
set(ONE_MINUTE_CHANGES_COVERAGE_RAW_FILES_DIR "${CMAKE_BINARY_DIR}/Test/CMakeFiles/Exe/Tester.dir/__/Code/one_minute_changes/src")
set(ONE_MINUTE_CHANGES_COVERAGE_RAW_FILES "${CMAKE_BINARY_DIR}/Test/CMakeFiles/Exe/Tester.dir/__/Code/one_minute_changes/src/*.gcda")
set(ONE_MINUTE_CHANGES_O_FILES "${ONE_MINUTE_CHANGES_COVERAGE_RAW_FILES_DIR}/*.o")

add_custom_target(coverage)
add_custom_command(TARGET coverage
	COMMAND mkdir -p ${COVERAGE_DIR}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET coverage
	COMMAND rm -rf ${ONE_MINUTE_CHANGES_COVERAGE_RAW_FILES} && ../${TEST_EXE}  && lcov -d  ${ONE_MINUTE_CHANGES_COVERAGE_RAW_FILES_DIR} --capture --output-file one_minute_changes.info && genhtml one_minute_changes.info 
	WORKING_DIRECTORY ${COVERAGE_DIR})

add_dependencies(coverage ${TEST_EXE})

add_custom_target(coverage_view)
add_custom_command(TARGET coverage_view
	COMMAND x-www-browser index.html
	WORKING_DIRECTORY ${COVERAGE_DIR})

add_dependencies(coverage_view coverage)
