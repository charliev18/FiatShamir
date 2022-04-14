#ifndef FIATSHAMIR_SETUP_H
#define FIATSHAMIR_SETUP_H

#include <tuple> // (Tuple)
#include <vector> // (Vector)
#include <iostream> // (cout)
#include <algorithm> // (find)
#include "../utils.h"

using namespace std;
using namespace Utils;

class setup {
public:
		int p, q, n;  																			// Primes and their product
		int k;																							// Number of witnesses to generate
		vector<int> witnesses;															// User's private values
		vector<int> publishable;														// User's public values

		setup(int p, int q, int k);
		void choose_witnesses();
		map<string,string> serialise() const;
private:
		static void verify_prime(int prime);
		int calc_quadratic_residue(int witness) const;
		int pick_witness();
		int calc_publishable(int witness);
		static int euclidian_gcd(int a, int b, int* x, int* y);
		static int mod_inverse(int a, int m);
};


#endif //FIATSHAMIR_SETUP_H
