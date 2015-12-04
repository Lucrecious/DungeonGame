#include <iostream>
#include "tests/testingharness.h"
#include "game/controller.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;


int main(int argc, char** argv) {
	// Start tests
	// These tests are invalid after the major controller change
	// TestingHarness* playerInput = new PlayerInputTests();
	TestingHarness* potionEffects = new PotionEffectTests();
	TestingHarness* stacks = new StackTests();
	//playerInput->runTests();
	potionEffects->runTests();
	stacks->runTests();
	//delete playerInput;
	delete potionEffects;
	delete stacks;
	// End tests

	ifstream splash("assets/splash.txt");
	string line;
	while (true) {
		getline(splash, line);
		if (splash.eof()) {
			break;
		}
		cout << line << endl;
	}
	splash.close();


	string filepath = "";
	if (argc >= 2) {
		filepath = string(argv[1]);
	}

	if (argc >= 3) {
		int seed = 0;
		string sseed = string(argv[2]);
		for (int i = 0; i < (int)sseed.size(); i++) {
			seed += (int)sseed[i];
		}

		srand(seed);
	}
	else {
		srand(time(NULL));
	}

	Controller cont(std::cin, filepath);
	cont.main();

}

