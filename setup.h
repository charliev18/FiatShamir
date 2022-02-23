#ifndef FIATSHAMIR_SETUP_H
#define FIATSHAMIR_SETUP_H

#include <random> // (uniform_in_distribution)
#include <tuple> // (Tuple)
#include <vector> // (Vector)
#include <iostream> // (cout)
#include <algorithm> // (find)

using namespace std;

class setup {
public:
		unsigned p, q, n;  																			// Primes and their product
		unsigned k;																							// Number of witnesses to generate
		vector<unsigned> witnesses;															// User's private values
		vector<int> publishable;																// User's public values
		setup(unsigned p, unsigned q, unsigned k);
		static void verify_prime(unsigned prime);
		unsigned calc_quadratic_residue(unsigned witness);
		static unsigned random_in_range(unsigned min, unsigned max);
		unsigned pick_witness();
		void choose_witnesses();
		int calc_publishable(unsigned witness);
		static int euclidian_gcd(unsigned a, unsigned b, int* x, int* y);
		static int mod_inverse(unsigned a, unsigned m);
};


#endif //FIATSHAMIR_SETUP_H
