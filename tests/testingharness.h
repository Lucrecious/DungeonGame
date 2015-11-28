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



#endif
