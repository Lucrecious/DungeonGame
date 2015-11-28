#include "../game/controller.h"
#include "testingharness.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void PlayerInputTests::runTests() {
	testInput("a no", "attack x:0 y:-1");
	testInput("u nw", "drink x:-1 y:-1");
	testInput("se", "move x:1 y:1");
	testInput("ne", "move x:1 y:-1");
	testInput("we", "move x:-1 y:0");
	testInput("ea", "move x:1 y:0");
	testInput("sw", "move x:-1 y:1");
	testInput("so", "move x:0 y:1");
}

void PlayerInputTests::testInput(string input, string expected) {
	istringstream in(input);
	Controller cont(in);
	Turn turn = cont.getInput();
	ostringstream out;
	switch (turn.kind) {
		case Attack:
			out << "attack ";
			break;
		case Drink:
			out << "drink ";
			break;
		case Move:
			out << "move ";
			break;
		default:
			out << "ERROR";
			break;
	}

	out << "x:" << turn.target.x << " y:" << turn.target.y;

	if (expected == out.str()) {
	}
	else {
		cout << "Failed:" << endl;
		cout << "Expected:" << endl;
		cout << expected << endl;
		cout << "Instead got:" << endl;
		cout << out.str() << endl;
	}

}
