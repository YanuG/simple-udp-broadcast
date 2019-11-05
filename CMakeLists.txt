cmake_minimum_required(VERSION 3.0)

project(simple-udp-broadcast)
find_package(Boost 1.55.0 REQUIRED COMPONENTS system filesystem program_options)
include_directories(${Boost_INCLUDE_DIRS})

link_directories( ${Boost_LIBRARY_DIRS})

set(SOURCE simple-udp-broadcast.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})

TARGET_LINK_LIBRARIES( ${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES} )

