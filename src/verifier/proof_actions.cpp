#include <utility>

#include "verifier.h"
#include "../../lib/cxxopts/cxxopts.hpp"

/* Perform verifier's first step of the protocol */
void generate_challenge(verifier* instance) {
	instance->generate_random_bools();

	Utils::print_verifier_step_1(instance->challenge);
}

/* Perform verifier's second step of the protocol */
void calculate_x(verifier* instance, int y, vector<int> published) {
	bool verified = instance->verify(y, std::move(published));

	Utils::print_verifier_step_2(instance->calc_x, verified);
}

/* Parses user input to dispatch actions */
void parse(int argc, char** argv) {
	cxxopts::Options options("FiatShamirVerifier",
							 "Implements verifier actions of the Fiat Shamir identification proof");

	options.add_options()
			// Setting parameters
			("k", "Number of witnesses", cxxopts::value<int>()->default_value(std::to_string(DEFAULT_K)))
			("n", "Published N value", cxxopts::value<int>()->default_value(std::to_string(DEFAULT_N)))
			("x,xval", "Initial X value received from prover", cxxopts::value<int>()->default_value(std::to_string(-1)))
			("y,yval", "Y value received from prover", cxxopts::value<int>())
			("b,bools", "List of previously generated challenges", cxxopts::value<std::vector<bool>>())
			("p,published", "Prover published identification values", cxxopts::value<std::vector<int>>())
			("f", "File name for caching values", cxxopts::value<string>()->default_value(DEFAULT_FNAME))

			// Setting flags
			("l,load", "Use cached values from previous steps and cache results for future use")
			("c,challenge", "Flag to generate challenge to send to prover (step 1)")
			("v,verify", "Flag to verify prover response (step 2)")
			("h,help", "Print usage");

	auto result = options.parse(argc, argv);

	if (result.count("help")) {
		std::cout << options.help() << std::endl;
		exit(0);
	}

	int k = result["k"].as<int>();
	int n = result["n"].as<int>();
	int x = result["x"].as<int>();

	vector<bool> challenge = {};
	if (result.count("b")) {
		challenge = result["b"].as<vector<bool>>();
	}

	vector<int> published = {};
	if (result.count("p")) {
		published = result["p"].as<vector<int>>();
	}

	bool load = result.count("l");
	string fname = result["f"].as<string>();

	if (load) {
		map<string, string> saved = Utils::load(fname);

		if (!saved[K_VAR].empty()) k = stoi(saved[K_VAR]);
		if (!saved[N_VAR].empty()) n = stoi(saved[N_VAR]);
		if (!saved[X_VAR].empty()) x = stoi(saved[X_VAR]);
		if (!saved[CHALLENGE_VAR].empty()) challenge = Utils::bools_from_string(saved[CHALLENGE_VAR]);
		if (!saved[PUBLISHED_VAR].empty()) published = Utils::ints_from_string(saved[PUBLISHED_VAR]);
	}

	map<string, string> toSave = {};
	verifier instance = verifier(k, n, x, challenge);

	if (result.count("c")) {
		generate_challenge(&instance);
		toSave = instance.serialise();
	}
	else if (result.count("v")) {
		if (!result.count("y")) {
			cout << "This step requires prover y-value, try again with the -y flag";
			exit(EXIT_FAILURE);
		}

		if (instance.x == -1) {
			cout << "This step requires a prover x-value, try again with the -x flag";
			exit(EXIT_FAILURE);
		}

		if (challenge.empty()) {
			cout << "This step requires previously generated challenge values, try again with the -b flag";
			exit(EXIT_FAILURE);
		}

		if (published.empty()) {
			cout << "This step requires prover published ID values, try again with the -p flag";
			exit(EXIT_FAILURE);
		}

		if (challenge.size() != k || published.size() != k) {
			cout << "To perform this step, there must be exactly k published values and challenges......Exiting"
				 << endl;
			exit(EXIT_FAILURE);
		}

		int y = result["y"].as<int>();
		calculate_x(&instance, y, published);
		toSave = instance.serialise();
	}

	if (load) {
		if (!published.empty()) toSave[PUBLISHED_VAR] = Utils::to_string(published);
		Utils::save(toSave, fname);
	}
}

int main(int argc, char** argv) {
	parse(argc, argv);
	return 0;
}
