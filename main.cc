#include <iostream>
#include "game/livingentity.h"
#include "tests/testingharness.h"


int main() {
	TestingHarness* playerInput = new PlayerInputTests();
	TestingHarness* potionEffects = new PotionEffectTests();
	playerInput->runTests();
	potionEffects->runTests();
	delete playerInput;
	delete potionEffects;
}

