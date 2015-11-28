#include <iostream>
#include "Game/livingentity.h"
#include "tests/testingharness.h"


int main() {
	TestingHarness* playerInput = new PlayerInputTests();
	playerInput->runTests();
	delete playerInput;
}

