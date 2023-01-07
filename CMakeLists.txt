cmake_minimum_required(VERSION 3.21)
project(NETSIM)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        include
)

set(SOURCE_FILES
        src/storage_types.cpp
        src/package.cpp
        )

add_executable(netsim ${SOURCE_FILES} main.cpp)


set(SOURCES_FILES_TESTS
        test/main_gtest.cpp
        test/test_package.cpp
        test/test_storage_types.cpp
#        test/test_Factory.cpp
#        test/test_factory_io.cpp
#        test/test_nodes.cpp
#        test/test_reports.cpp
#        test/test_simulate.cpp
        )


add_executable(netsim_test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)



target_include_directories(netsim PUBLIC
    googletest-master/googlemock/include
    googletest-master/googletest/include
    mocks
    )

add_subdirectory(googletest-master)
target_link_libraries(netsim_test gmock)
target_link_libraries(netsim_test gtest)