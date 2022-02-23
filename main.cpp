#include <iostream>
#include "setup.h"

using namespace std;

int main() {
		unsigned p = 7;
		unsigned q = 11;

		setup instance = setup(p, q, 10);
		instance.choose_witnesses();
		cout << "Your N value is " << instance.n << endl;
		cout << "Your secret witnesses are :";
		for (unsigned val : instance.witnesses) {
				cout << val << ", ";
		}
		cout << endl;

		cout << "Your publishable values are :";
		for (int val : instance.publishable) {
				cout << val << ", ";
		}
		return 0;
}
