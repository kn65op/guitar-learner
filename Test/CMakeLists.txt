set(TEST_DIR ".")
set(TEST_EXE_DIR "${TEST_DIR}")
set(TEST_SRC_DIR "${TEST_DIR}/src")
set(TEST_INC_DIR "${TEST_DIR}/inc")
set(TEST_EXE Tester)

if ("${GMOCK_DIR}" STREQUAL "")
    message(STATUS "No GMOCK_DIR variable set, trying to use system gmock")
    set(GMOCK_DIR "/usr/src/googletest/googlemock")
endif ("${GMOCK_DIR}" STREQUAL "")

set(GMOCK_MAIN_DIR ${GMOCK_DIR})

set(GMOCK_INCLUDE_DIR "${GMOCK_MAIN_DIR}/include")
set(GTEST_INCLUDE_DIR "${GMOCK_DIR}/../googletest/include")
set(GMOCK_H_INCLUDE_DIR "${GMOCK_DIR}/include/gmock")
set(GMOCK_INCLUDE "${GMOCK_H_INCLUDE_DIR}/gmock.h")
include_directories(${GMOCK_INCLUDE_DIR})
include_directories(${GTEST_INCLUDE_DIR})
set(LIB_GMOCK gmock)

if (EXISTS "${GMOCK_INCLUDE}")
    message(STATUS "Using gmock from ${GMOCK_DIR}")
else (EXISTS "${GMOCK_INCLUDE}")
    message(FATAL_ERROR "Could not find googlemock in ${GMOCK_DIR}")
endif (EXISTS "${GMOCK_INCLUDE}")

set(GMOCK_INCLUDE_DIR "${GMOCK_DIR}/include/gmock")
set(GMOCK_INCLUDE "${GMOCK_INCLUDE_DIR}/gmock.h")

#projects parts
set(TESTS_POSTFIX Tests)
set(MOCKS_POSTFIX Mocks)

set(ONE_MINUTE_CHANGES_TESTS_DIR one_minute_changes${TESTS_POSTFIX})
set(ONE_MINUTE_CHANGES_MOCKS_DIR one_minute_changes${MOCKS_POSTFIX})
set(MAIN_TESTS_DIR Main${TESTS_POSTFIX})

#project includes
include_directories(${TEST_INC_DIR}/${ONE_MINUTE_CHANGES_MOCKS_DIR}/)

#external libs

set(CMAKE_CXX_FLAGS_DEBUG "${NORMAL_WARNING_FLAGS}")
add_subdirectory(${GMOCK_MAIN_DIR} gmock)
set(CMAKE_CXX_FLAGS_DEBUG "${EXTRA_WARNING_FLAGS}")

#test files
file(GLOB MAIN_TEST_FILES ${TEST_SRC_DIR}/${MAIN_TESTS_DIR}/*.cpp)
file(GLOB TEST_MAIN ${TEST_SRC_DIR}/*.cpp)

file(GLOB ONE_MINUTE_CHANGES_TEST_FILES ${TEST_SRC_DIR}/${ONE_MINUTE_CHANGES_TESTS_DIR}/*.cpp)

#tests
enable_testing()

file(MAKE_DIRECTORY ${TEST_EXE_DIR})

add_executable(${TEST_EXE} ${TEST_MAIN} ${MAIN_FILES} ${MAIN_TEST_FILES} ${ONE_MINUTE_CHANGES_FILES} ${ONE_MINUTE_CHANGES_TEST_FILES})
add_dependencies(${TEST_EXE} ${TLOGGER_TARGET})
TARGET_LINK_LIBRARIES(${TEST_EXE} ${THELPER_LIBRARIES} )
TARGET_LINK_LIBRARIES(${TEST_EXE} ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(${TEST_EXE} ${TLOGGER_LIBRARIES})
target_link_libraries(${TEST_EXE} ${LIB_GMOCK})
add_test(gtests ${TEST_EXE}) 

set(COVERAGE_DIR coverage)
set(SOURCE_RAW_FILES_DIR "${CMAKE_BINARY_DIR}/Test/CMakeFiles/Tester.dir/__/Code")
set(COVERAGE_INFO guitar_learner.info)

add_custom_target(coverage)
add_custom_command(TARGET coverage
    COMMAND mkdir -p ${COVERAGE_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(TARGET coverage
        COMMAND find ${CMAKE_BINARY_DIR} -name *.gcda -exec rm {} "\;" && ../${TEST_EXE}  && lcov -d  ${SOURCE_RAW_FILES_DIR} --capture --output-file ${COVERAGE_INFO} && genhtml ${COVERAGE_INFO}
            WORKING_DIRECTORY ${COVERAGE_DIR})

add_dependencies(coverage ${TEST_EXE})


add_custom_target(coverage_view)
add_custom_command(TARGET coverage_view
    COMMAND x-www-browser index.html
    WORKING_DIRECTORY ${COVERAGE_DIR})

add_dependencies(coverage_view coverage)
