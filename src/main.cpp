#include <iostream>
#include <Game/controller.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;


int main(int argc, char** argv) {
	// This just a simple splash screen for bonus :)
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


	// The first argument has a to be a valid path otherwise errors!
	string filepath = "";
	if (argc >= 2) {
		filepath = string(argv[1]);
	}
	
	// Produces a seed for random generation. Takes a string and just
	//   adds up the charaters ascii values.
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
	
	// We start the game
	Controller cont(std::cin, filepath);
	cont.main();

}

