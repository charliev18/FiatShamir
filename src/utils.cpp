#include "utils.h"

using namespace Utils;

/* Prints relevant information gained from the setup phase */
void Utils::print_after_setup(int n, const vector<int>& witnesses, const vector<int>& published) {
	cout << "The N value is " << n << " requiring " << ceil(log2(n)) << " bits" << endl;
	cout << "Prover's secret witnesses are :";

	for (int val : witnesses) {
		cout << val << ", ";
	}
	cout << endl;

	cout << "The published values are :";
	for (int val : published) {
		cout << val << ", ";
	}
	cout << endl;
}

void Utils::print_prover_step_1(int r, int x) {
	cout << "Prover's secret random R value is : " << r << endl;
	cout << "Prover's calculated X value is : " << x << endl;
}

void Utils::print_verifier_step_1(const vector<bool> &toggles) {
	cout << "Verifier's generated toggles are :";
	for (int val : toggles) {
		cout << val << ", ";
	}

	cout << endl;
}

void Utils::print_prover_step_2(int y) {
	cout << "Prover's calculated Y value is : " << y << endl;
}

void Utils::print_verifier_step_2(int x, bool match) {
	cout << "Verifier's calculated X value is : " << x << endl;

	if (match) {
		cout << "Verifier accepts this iteration" << endl << endl;
	} else {
		cout << "Verifier rejects this iteration" << endl << endl;
	}
}

/* Alternative mod function to account for negative values */
int Utils::mod(int val, int modulo) {
	return (val % modulo + modulo) % modulo;
}

/*
 * @param min: minimum value for range of random number
 * @param max: maximum value for range of random number
 * @returns: random integer between input parameters
 */
int Utils::random_in_range(int min, int max) {
	random_device seed;
	mt19937 gen(seed());
	uniform_int_distribution<> distrib(min, max);
	return distrib(gen);
}

string Utils::to_string(const vector<int>& vals) {
	ostringstream output;
	for (int val : vals) {
		output << val << ",";
	}

	return output.str();
}

string Utils::to_string(const vector<bool>& vals) {
	ostringstream output;
	for (int val : vals) {
		output << val << ",";
	}

	return output.str();
}

vector<bool> Utils::bools_from_string(const string& vals) {
	ostringstream cur;
	vector<bool> output = {};
	for (char c : vals) {
		if (c == ',') {
			output.push_back(stoi(cur.str()));
			cur.str("");
			cur.clear();
			continue;
		}

		cur << c;
	}

	return output;
}

vector<int> Utils::ints_from_string(const string& vals) {
	ostringstream cur;
	vector<int> output = {};
	for (char c : vals) {
		if (c == ',') {
			output.push_back(stoi(cur.str()));
			cur.str("");
			cur.clear();
			continue;
		}

		cur << c;
	}

	return output;
}

void Utils::save(const map<string,string>& vals, const string& fname) {
	ofstream file;
	file.open(fname, ios::trunc);

	for (const auto &pair : vals) {
		file << pair.first << ":" << pair.second << "\n";
	}

	file.close();
}

map<string,string> Utils::load(const string& fname) {
	string line;
	ifstream file;
	file.open(fname);
	map<string, string> output = {};

	if (file.is_open()) {
		while (getline(file, line)) {
			auto split = line.find(':');
			output[line.substr(0, split)] = line.substr(split + 1);
		}

		file.close();
	}

	return output;
}
