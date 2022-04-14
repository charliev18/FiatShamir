add_executable(Simulate simulate.cpp prover/setup.cpp verifier/verifier.cpp prover/prover.cpp utils.cpp)
include_directories(${CMAKE_SOURCE_DIR}/prover) # include files from prover
include_directories(${CMAKE_SOURCE_DIR}/verifier) # include files from verifier
