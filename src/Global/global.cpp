#include <Global/global.hpp>
#include <Game/game.hpp>
#include <Game/player.hpp>
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

Information Global::makeInfoFromPlayer(Player* p, Game* g) {
	Information info = {
		p->getAtkStat(),
		p->getDefStat(),
		p->getHP(),
		p->getMaxHP(),
		p->getGold(),
		p->getName(),
		p->subKind,
		p->getHealsLeft(),
		g->getLevelNumber()
	};

	return info;	
}


const int Global::levelHeight;
const int Global::levelWidth;
const int Global::maxChambers;
const int Global::maxPotions;
const int Global::maxGolds;
const int Global::maxEnemies;

const int Global::SmallGold;
const int Global::NormalGold;
const int Global::MerchantGold;
const int Global::DragonGold;

const char Global::VWallSymbol;
const char Global::HWallSymbol;
const char Global::FloorSymbol;
const char Global::DoorSymbol;
const char Global::PassageSymbol;
const char Global::StairsSymbol;

const char Global::RHPotionSymbol;
const char Global::BAPotionSymbol;
const char Global::BDPotionSymbol;
const char Global::PHPotionSymbol;
const char Global::WAPotionSymbol;
const char Global::WDPotionSymbol;
const char Global::PotionSymbol;

const char Global::GoldNormalSymbol;
const char Global::GoldSmallSymbol;
const char Global::GoldMerchantSymbol;
const char Global::GoldDragonSymbol;
const char Global::GoldSymbol;

const char Global::PlayerSymbol;

const char Global::HumanSymbol;
const char Global::DragonSymbol;
const char Global::DwarfSymbol;
const char Global::ElfSymbol;
const char Global::OrcSymbol;
const char Global::MerchantSymbol;
const char Global::HalflingSymbol;

const char Global::Chamber1Symbol;
const char Global::Chamber2Symbol;
const char Global::Chamber3Symbol;
const char Global::Chamber4Symbol;
const char Global::Chamber5Symbol;
