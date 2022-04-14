#include "verifier.h"

verifier::verifier(int k, int n) {
		this->k = k;
		this->n = n;
		this->x = -1;
		this->calc_x = -1;
		this->challenge = {};
}

verifier::verifier(int k, int n, int x, vector<bool> challenge) {
	this->k = k;
	this->n = n;
	this->x = x;
	this->calc_x = -1;
	this->challenge = challenge;
}

void verifier::set_x(int val) {
	this->x = val;
}

/*
 * Populates the challenge parameter
 */
void verifier::generate_random_bools() {
	vector<bool> toggles = {};
	for (int i = 0; i < this->k; i++) {
		bool rand = Utils::random_in_range(0, 1) == 1;
		toggles.push_back(rand);
	}

	this->challenge = toggles;
}

/*
 * Calculates a value to verify the authenticity of the prover
 * @param y: a value received from the prover
 * @param published: the prover's public values
 * @returns: true if the calculated value is the same as the stored x, false otherwise
 */
bool verifier::verify(int y, vector<int> published) {
	int base = y * y % this->n;
	for (int i = 0; i < this->k; i++) {
		if (this->challenge[i]) {
			base = Utils::mod(base * published[i], this->n);
		}
	}

	this->calc_x = base;
	return base == this->x || Utils::mod(base * -1, n) == this->x;
}

map<string, string> verifier::serialise() {
	map<string,string> out = {{K_VAR, to_string(this->k)},
							  {N_VAR, to_string(this->n)}};

	if (this->x != -1) out[X_VAR] = to_string(this->x);
	if (!this->challenge.empty()) out[CHALLENGE_VAR] = Utils::to_string(this->challenge);

	return out;
}
