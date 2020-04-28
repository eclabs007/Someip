cmake_minimum_required (VERSION 2.8)

set (CMAKE_CXX_FLAGS "-g -std=c++0x")

find_package (vsomeip 2.6.0 REQUIRED)
find_package( Boost 1.55 COMPONENTS system thread log REQUIRED )

include_directories (
    ${Boost_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIRS}
)

add_executable(service ./ser.cpp)
add_executable(cli ./cli.cpp)
target_link_libraries(service vsomeip ${Boost_LIBRARIES})
target_link_libraries(cli vsomeip ${Boost_LIBRARIES})
