#include "setup.h"

using namespace std;

#define p(X) (cout << X << endl)

setup::setup(int p, int q, int k) {
		verify_prime(p);
		verify_prime(q);
		this->p = p;
		this->q = q;
		this->n = p * q;
		this->k = k;
		this->witnesses = {};
		this->publishable = {};
}

/*
 * Checks a supplied value is prime and a Blum integer (4r + 3), exits with error message if not
 * @param prime: the value to check
 */
void setup::verify_prime(int prime) {
		// Check if Blum integer
		if (prime % 4 != 3) {
				p("The supplied value " << prime << " must be a Blum integer (in form 4r + 3).......exiting");
				exit(EXIT_FAILURE);
		}

		// Check if prime
		for (int i = 3; i < prime; i += 2) {
				if (prime % i == 0) {
						p("The supplied value " << prime << " must be prime.......exiting");
						exit(EXIT_FAILURE);
				}
		}
}

/*
 * @param witness: value used to form a quadratic residue
 * @returns: quadratic residue mod n for witness
 */
int setup::calc_quadratic_residue(int witness) const {
		return witness * witness % this->n;
}

/*
 * Picks a new witness which is coprime to n and not already a witness
 * @returns: a random secret integer in the range 0..n-1
 */
int setup::pick_witness() {
		int rand = Utils::random_in_range(0, this->n - 1);
		while (rand == this->p || rand == this->q ||
					 find(this->witnesses.begin(), this->witnesses.end(), rand) != this->witnesses.end()) {
				rand = Utils::random_in_range(0, this->n - 1);
		}
		return rand;
}

/*
 * @param witness: potential witness to determine the validity of
 * @returns: the corresponding value to a given witness (1/witness^2)
 */
int setup::calc_publishable(int witness) {
		int quad_res = calc_quadratic_residue(witness);
		return mod_inverse(quad_res, n);
}

/*
 * Populates the witness and publishable instance vectors
 * Picks k random witnesses and then calculates their publishable counterparts according to the protocol
 */
void setup::choose_witnesses() {
		int val;
		int try_witness;
		int flip;
		for (int i = 0; i < this->k; i++) {
				flip = Utils::random_in_range(0, 1);
				if (flip == 0) --flip; // flip is now either -1 or 1 with equal probability

				val = -1;
				while (val == -1) { 														// Keep picking witnesses until one is valid for protocol
						try_witness = pick_witness();
						val = calc_publishable(try_witness);
				}

				this->witnesses.push_back(try_witness);
				this->publishable.push_back(flip * val);
		}
}

map<string,string> setup::serialise() const {
		return {{"k", to_string(this->k)},
						{"n", to_string(this->n)},
						{"witnesses", Utils::to_string(this->witnesses)}};
}

/*
 * Calculates the modular multiplicative inverse of a number using the extended euclidean algorithm
 * @param a: value to find the multiplicative inverse of
 * @param m: field order
 * @returns: the modular multiplicative inverse of a if it exists, -1 if not
 */
int setup::mod_inverse(int a, int m) {
		int x, y; // To be populated in euclidian_gcd()
		int g = euclidian_gcd(a, m, &x, &y);
		if (g != 1) { // Inverse does not exist
				return -1;
		} else {
				return Utils::mod(x, m); //(x % m + m) % m; // m added to make it positive
		}
}

/*
 * Recursive helper function for extended euclidian gcd algorithm
 */
int setup::euclidian_gcd(int a, int b, int* x, int* y) {
		// Base Case
		if (a == 0) {
				*x = 0, *y = 1;
				return b;
		}

		// To store results of recursive call
		int x1, y1;
		int gcd = euclidian_gcd(b % a, a, &x1, &y1);

		*x = y1 - (b / a) * x1;
		*y = x1;

		return gcd;
}
