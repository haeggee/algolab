cmake_minimum_required(VERSION 2.8)
project(algo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

find_package(CGAL REQUIRED COMPONENTS Core)
find_package(Boost REQUIRED)
include_directories(${CGAL_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
include( ${CGAL_USE_FILE} )

add_executable(${PROJECT_NAME} "src/algorithm.cpp")
target_link_libraries(${PROJECT_NAME} ${CGAL_LIBRARIES} ${Boost_LIBRARIES} ${MPFR_LIBRARIES} ${GMP_LIBRARIES} ${THREAD_LIBRARIES})
