#include "testingharness.h"
#include "../game/statics/boostatk.h"
#include "../game/statics/boostdef.h"
#include "../game/statics/poisonatk.h"
#include "../game/statics/poisondef.h"
#include "../game/statics/noeffect.h"
#include "../game/statics/effect.h"
#include <iostream>
#include <sstream>
using namespace std;


void PotionEffectTests::runTests() {
	testPotionEffects("a", 5, 0);
	testPotionEffects("d", 0, 5);
	testPotionEffects("t", -5, 0);
	testPotionEffects("e", 0, -5);
	testPotionEffects("aa", 10, 0);
	testPotionEffects("adadte", 5, 5);
	testPotionEffects("eeeee", 0, -25);
	testPotionEffects("ddaat", 5, 10);
	testPotionEffects("ttt", -15, 0);
}

void PotionEffectTests::testPotionEffects(string com, int netAtk, int netDef) {
	istringstream in(com);
	Effect* effect = new NoEffect();

	char potion;
	while (true) {
		in >> potion;
		if (in.eof()) {
			break;
		}

		switch (potion) {
			case 'a':
				effect = new BoostAtk(effect);
				break;
			case 'd':
				effect = new BoostDef(effect);
				break;
			case 't':
				effect = new PoisonAtk(effect);
				break;
			case 'e':
				effect = new PoisonDef(effect);
				break;
			default:
				break;
		}
	}
	
	if (effect->getAtkNet() != netAtk || effect->getDefNet() != netDef) {
		cout << "In: " << com << endl;
		cout << "Expected:" << endl;
		cout << netAtk << " " << netDef << endl;
		cout << "Instead got:" << endl;
		cout << effect->getAtkNet() << " " << effect->getDefNet() << endl;
	}

	delete effect;
}









