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

