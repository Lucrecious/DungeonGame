#include "testingharness.h"
#include <iostream>
#include <sstream>
using namespace std;


void StackTests::runTests() {
	Stack<int>* test1 = new Stack<int>();
	test1->push(1);
	test1->push(2);
	test1->push(3);
	this->testStacks(test1, "321");
	delete test1;

	Stack<int>* test2 = new Stack<int>();
	test2->push(10);
	this->testStacks(test2, "10");
	delete test2;

	Stack<int>* test3 = new Stack<int>();
	this->testStacks(test3, "");
	delete test3;
}


void StackTests::testStacks(Stack<int>* stack, string nums) {
	ostringstream out("");
	while (!stack->isEmpty()) {
		out << stack->pop();
	}
	
	if (out.str() != nums) {
		cout << "For stacks..." << endl;
		cout << "Expected: " << nums << endl;
		cout << "Instead got: " << out.str() << endl;
	}

}

