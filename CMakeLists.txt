cmake_minimum_required(VERSION 3.26.3)

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(
    ABRUHP
    VERSION 0.1.0
    LANGUAGES CXX
)

include(CTest)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

add_executable(abruhp ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(abruhp common lexer parser ast)

add_test(NAME SimpleTest COMMAND abruhp ${CMAKE_SOURCE_DIR}/examples/test.abruhp)