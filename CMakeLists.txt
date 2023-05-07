cmake_minimum_required(VERSION 3.25)
project(du_udml_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(du_udml_2 tests.cpp)
find_library(LPSOLVE55_LIBRARY NAMES lpsolve55 PATHS /usr/lib/lp_solve)
if(NOT LPSOLVE55_LIBRARY)
    message(FATAL_ERROR "lpsolve55 library not found")
endif()
target_link_libraries(du_udml_2 ${LPSOLVE55_LIBRARY})
target_include_directories(du_udml_2 PRIVATE /usr/include/lpsolve/)

