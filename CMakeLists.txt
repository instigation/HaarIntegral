cmake_minimum_required(VERSION 3.13)
project(codes)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -O2")
set(CMAKE_C_FLAGS "-g -O2")

add_executable(IntegralOnR IntegralOnR.cc)
add_executable(IntegralOnSU2 IntegralOnSU2.cpp IntegralOnR3.cpp)
target_link_libraries(IntegralOnR iRRAM mpfr gmp m)
target_link_libraries(IntegralOnSU2 iRRAM mpfr gmp m)

