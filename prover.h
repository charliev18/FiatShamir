//
// Created by Charlie Victor on 20/02/2022.
//

#ifndef FIATSHAMIR_PROVER_H
#define FIATSHAMIR_PROVER_H


class prover {
public:
		void setup(unsigned k, unsigned t);
		void generate_proof();
private:
		unsigned generate_public_n(); // Unsigned has 16 bits, so needs to be extended to be uint256 or uint512
		unsigned hash(); // Must output values in range 0-n (same as above function)



};


#endif //FIATSHAMIR_PROVER_H
