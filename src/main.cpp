#include <iostream>
#include <Game/controller.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;


int main(int argc, char** argv) {
	ifstream splash("assets/splash.txt");
	string line;
	while (true) {
		getline(splash, line);
		cout << line << endl;
		if (splash.eof()) {
			break;
		}
	}
	splash.close();

	cout << endl << endl;
	
	if (argc >= 2) {
		int seed = 0;
		string sseed = string(argv[1]);
		for (int i = 0; i < (int)sseed.size(); i++) {
			seed += (int)sseed[i];
		}

		srand(seed);
	}
	else {
		srand(time(NULL));
	}
	
	Controller cont(std::cin);
	cont.main();

}

