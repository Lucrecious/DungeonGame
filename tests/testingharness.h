#ifndef TESTINGHARNESS_H
#define TESTINGHARNESS_H
#include <string>

class TestingHarness {
public:
	virtual void runTests() = 0;
};


class PlayerInputTests : public TestingHarness {
public:
	void runTests();
private:
	void testInput(std::string, std::string);
};


class PotionEffectTests : public TestingHarness {
public:
	void runTests();
private:
	// a - boost attack
	// d - boost defence
	// t - poison attack
	// e - poison defence
	void testPotionEffects(std::string, int, int);
};

#endif
