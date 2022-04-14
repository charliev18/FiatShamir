#include "prover.h"
#include "setup.h"
#include "../../lib/cxxopts/cxxopts.hpp"

using namespace Utils;

/* Performs the setup step of the protocol */
void setup_proof(setup* instance) {
	instance->choose_witnesses();

	Utils::print_after_setup(instance->n, instance->witnesses, instance->publishable);
}

/* Performs the first step the prover must complete of the protocol */
void generate_x_val(prover* instance) {
	int x = instance->calculate_x();

	Utils::print_prover_step_1(instance->r, x);
}

/* Performs the second step the prover must complete of the protocol */
void generate_y_val(prover* instance, const vector<bool>& challenge) {
	int y = instance->calculate_y(challenge);

	Utils::print_prover_step_2(y);
}

/* Parses user input to dispatch actions */
void parse(int argc, char** argv) {
	cxxopts::Options options("FiatShamirProver",
							 "Implements prover actions of the Fiat Shamir identification proof");

	options.add_options()
			// Setting parameters
			("p", "First safe prime", cxxopts::value<int>()->default_value(std::to_string(DEFAULT_P)))
			("q", "Second safe prime", cxxopts::value<int>()->default_value(std::to_string(DEFAULT_Q)))
			("k", "Number of witnesses", cxxopts::value<int>()->default_value(std::to_string(DEFAULT_K)))
			("n", "Published N value", cxxopts::value<int>()->default_value(std::to_string(DEFAULT_N)))
			("r", "Previously generated r value", cxxopts::value<int>()->default_value(std::to_string(DEFAULT_R)))
			("w,witnesses", "List of private witnesses", cxxopts::value<std::vector<int>>())
			("c,challenge", "List of challenges from verifier", cxxopts::value<std::vector<bool>>())
			("f", "File name for caching values", cxxopts::value<string>()->default_value(DEFAULT_FNAME))

			// Setting flags
			("l,load", "Use cached values from previous steps and cache results for future use")
			("s,setup", "Flag to set up the protocol")
			("x,xval", "Flag to generate commitment to send to verifier")
			("y,yval", "Flag to generate value to respond to verifier challenge")
			("h,help", "Print usage");

	auto result = options.parse(argc, argv);

	if (result.count("help")) {
		std::cout << options.help() << std::endl;
		exit(0);
	}

	int p = result["p"].as<int>();
	int q = result["q"].as<int>();
	int k = result["k"].as<int>();
	int n = result["n"].as<int>();
	int r = result["r"].as<int>();

	vector<int> witnesses = {};
	if (result.count("w")) {
		witnesses = result["w"].as<vector<int>>();
	}


	bool load = result.count("l");
	string fname = result["f"].as<string>();

	if (load) {
		map<string, string> saved = Utils::load(fname);

		if (!saved[K_VAR].empty()) k = stoi(saved[K_VAR]);
		if (!saved[N_VAR].empty()) n = stoi(saved[N_VAR]);
		if (!saved[R_VAR].empty()) r = stoi(saved[R_VAR]);
		if (!saved[WITNESS_VAR].empty()) witnesses = Utils::ints_from_string(saved[WITNESS_VAR]);
	}

	map<string, string> toSave = {};

	if (result.count("s")) {
		setup instance = setup(p, q, k);
		setup_proof(&instance);
		toSave = instance.serialise();
	}
	else if (result.count("x")) {
		prover prove = prover(k, n, witnesses);
		generate_x_val(&prove);
		toSave = prove.serialise();
	}
	else if (result.count("y")) {
		if (result.count("c")) {
			auto &challenge = result["c"].as<vector<bool>>();
			if (witnesses.size() != k || challenge.size() != k) {
				cout << "To perform this step, there must be exactly k witnesses and challenges......Exiting"
					 << endl;
				exit(EXIT_FAILURE);
			}

			prover prove = prover(k, n, r, witnesses);
			generate_y_val(&prove, challenge);
			toSave = prove.serialise();
		} else {
			cout << "To perform this step, you must supply verifier challenge" << endl;
			cout << "Try again with appropriate -c flags set......Exiting" << endl;
			exit(EXIT_FAILURE);
		}
	}

	if (load) {
		Utils::save(toSave, fname);
	}
}

int main(int argc, char** argv) {
	parse(argc, argv);
	return 0;
}
