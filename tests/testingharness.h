#ifndef TESTINGHARNESS_H
#define TESTINGHARNESS_H
#include <string>
#include "../utils/stack.h"

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

class StackTests : public TestingHarness {
public:
	void runTests();
private:
	void testStacks(Stack<int>*, std::string);
};

#endif
