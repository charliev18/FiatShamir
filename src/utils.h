#ifndef FIATSHAMIRGLOBAL_UTILS_H
#define FIATSHAMIRGLOBAL_UTILS_H

#include <vector>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <random> // (uniform_in_distribution)

// Global constants
#define DEFAULT_P 151
#define DEFAULT_Q 211
#define DEFAULT_N (DEFAULT_P * DEFAULT_Q)
#define DEFAULT_K 12
#define DEFAULT_T 4
#define DEFAULT_R 0
#define DEFAULT_FNAME "./../../cache/saved.txt"

#define K_VAR "k"
#define N_VAR "n"
#define R_VAR "r"
#define X_VAR "x"
#define WITNESS_VAR "witnesses"
#define CHALLENGE_VAR "challenge"
#define PUBLISHED_VAR "published"

using namespace std;

namespace Utils {
	// Prints
	void print_after_setup(int n, const vector<int> &witnesses, const vector<int> &published);
	void print_prover_step_1(int r, int x);
	void print_verifier_step_1(const vector<bool> &toggles);
	void print_prover_step_2(int y);
	void print_verifier_step_2(int x, bool match);

	// Math
	int mod(int val, int modulo);
	int random_in_range(int min, int max);

	// Serialising
	string to_string(const vector<int> &vals);
	string to_string(const vector<bool> &vals);
	vector<int> ints_from_string(const string &vals);
	vector<bool> bools_from_string(const string &vals);
	map<string, string> load(const string &fname);
	void save(const map<string, string> &vals, const string &fname);
}


#endif //FIATSHAMIRGLOBAL_UTILS_H
