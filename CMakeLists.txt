cmake_minimum_required (VERSION 2.6)

project (connected-components-finder)

set(CMAKE_CXX_STANDARD 17)

include_directories(CombOptWS2018)

add_library(wochnik-graph STATIC CombOptWS2018/graph.cpp)

add_library(graph STATIC Graph.cpp)

add_executable(connected-components-finder connected-components-finder.cpp)

target_link_libraries(connected-components-finder wochnik-graph)