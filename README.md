# FiatShamir
Implementation of the [Fiat-Shamir Identification protocol](https://link.springer.com/content/pdf/10.1007/3-540-47721-7_12.pdf) 
in C++. Requires C++11 or greater. The following instructions 
are intended for Unix machines, but can be easily altered for Windows users.

After each step, the program will print out the relevant information for a user to either save privately or send to the 
other party.

### Prover actions:
The prover first navigates to the prover directory and compiles their executable with:

    g++ -o prover proof_actions.cpp setup.cpp prover.cpp
    
This executable holds all the interactions that the prover can perform in the protocol. These are specified by using 
flags from the command line. To initially setup the protocol, the prover runs the following with their chosen p, q, k 
parameters:

    ./prover -s -l -p [p] -q [q] -k [k]
   
The -l flag is optional, and caches the results for later steps of the proof.
It can be left out if the user wants to manually input all parameters, or the cached values gets lost.

To run the next step, after initialising communication with the verifier, the prover runs:

    ./prover -x -l
    
This will load in the previously cached values and generate a random x as per the protocol to be sent to the verifier.

Upon receiving the challenge from the verifier, the prover then runs:

    ./prover -y -l -c [challenge]
    
Note: It is important when supplying the challenge to provide comma separated values without spaces, i.e. 0,1,1,0...

### Verifier Actions:
The verifier first navigates to the verifier directory then compiles their executable with:

    g++ -o verifier proof_actions.cpp verifier.cpp
    
The verifier's first step of the protocol can the be run with parameters, k, n, I, x received from the prover by 
running:

    ./verifier -c -l -n [n] -k [k] -p [I] -x [x]
    
Again, the -l flag is optional and instructs the program to cache relevant values between steps of the protocol.
It can be left out if the user wants to manually input all parameters, or the cached values gets lost.

The verifier then runs their second step after receiving input y from the prover:

    ./verifier -v -l -y [y]

It will print out if this round is accepted or rejected.

### Simulating the full communication:
From the command line, in the 'src' directory run:

    g++ -o simulation simulate.cpp prover/setup.cpp verifier/verifier.cpp prover/prover.cpp

This will compile the executable file 'simulation'. This can either be run with no parameters to simulate the protocol 
with preset parameters:
- p = 151
- q = 211
- k = 12
- t = 4

Or can include custom parameters by running:

    ./simulation -p [p] -q [q] -k [k] -t [t]
    
All relevant information from the simulation will be formatted and printed to the terminal

Built using [cxxopts](https://github.com/jarro2783/cxxopts) to parse command line input.