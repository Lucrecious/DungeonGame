#include <iostream>
#include "tests/testingharness.h"
#include "game/controller.h"
#include <iostream>


int main() {
	// Start tests
	TestingHarness* playerInput = new PlayerInputTests();
	TestingHarness* potionEffects = new PotionEffectTests();
	TestingHarness* stacks = new StackTests();
	playerInput->runTests();
	potionEffects->runTests();
	stacks->runTests();
	delete playerInput;
	delete potionEffects;
	delete stacks;
	// End tests
	
	Controller cont(std::cin);
	cont.play();

}

