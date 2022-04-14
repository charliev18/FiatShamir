cmake_minimum_required(VERSION 3.2.2)
project(FiatShamirGlobal)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src/prover)
add_subdirectory(src/verifier)
add_subdirectory(src)