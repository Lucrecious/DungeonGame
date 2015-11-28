#include <iostream>
#include "game/livingentity.h"
#include "tests/testingharness.h"


int main() {
	TestingHarness* playerInput = new PlayerInputTests();
	TestingHarness* potionEffects = new PotionEffectTests();
	TestingHarness* stacks = new StackTests();
	playerInput->runTests();
	potionEffects->runTests();
	stacks->runTests();
	delete playerInput;
	delete potionEffects;
	delete stacks;
}

