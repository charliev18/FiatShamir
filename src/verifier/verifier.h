#ifndef FIATSHAMIR_VERIFIER_H
#define FIATSHAMIR_VERIFIER_H

#include <vector>
#include "../utils.h" // (random_in_range)

using namespace std;
using namespace Utils;

class verifier {
public:
	int k;
	int n;
	int x;
	int calc_x;
	vector<bool> challenge;

	verifier(int k, int n);
	verifier(int k, int n, int x, vector<bool> challenge);
	void set_x(int val);
	void generate_random_bools();
	bool verify(int y, vector<int> published);
	map<string,string> serialise();
};


#endif //FIATSHAMIR_VERIFIER_H
