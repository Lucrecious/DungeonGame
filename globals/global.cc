#include "global.h"
using namespace std;

double Global::drand(double lower, double upper) {
	double d = (double)rand()/ RAND_MAX;
	return lower + d * (upper - lower);
}

int Global::irand(int lower, int upper) {
	double i = rand() % (upper + 1 - lower);
	return lower + i;
}

bool Global::hitChance(double c) {
	return drand(0, 1) <= c;
}

Kind Global::getRandomKindFrom(vector<Kind> kinds) {
	int i = Global::irand(0, kinds.size() - 1);

	return kinds[i];
}

vector<Kind> Global::constructProbabilityDist(Kind* kinds, int* probs, int length) {
	vector<Kind> probDist;

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < probs[i]; j++) {
			probDist.push_back(kinds[i]);
		}
	}

	return probDist;
}



