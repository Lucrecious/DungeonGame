#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdlib.h>
#include <vector>
#include <Global/kind.hpp>
#include <Global/information.hpp>

class Game;
class Player;

class Global {
public:
	const static int levelHeight = 25;
	const static int levelWidth = 79;
	const static int maxChambers = 5;
	const static int maxPotions = 10;
	const static int maxGolds = 10;
	const static int maxEnemies = 20;

	const static int SmallGold = 1;
	const static int NormalGold = 2;
	const static int MerchantGold = 4;
	const static int DragonGold = 6;

	const static char VWallSymbol = '|';
	const static char HWallSymbol = '-';
	const static char FloorSymbol = '.';
	const static char DoorSymbol = '+';
	const static char PassageSymbol = '#';
	const static char StairsSymbol = '\\';

	const static char RHPotionSymbol = '0';
	const static char BAPotionSymbol = '1';
	const static char BDPotionSymbol = '2';
	const static char PHPotionSymbol = '3';
	const static char WAPotionSymbol = '4';
	const static char WDPotionSymbol = '5';
	const static char PotionSymbol = 'P';

	const static char GoldNormalSymbol = '6';
	const static char GoldSmallSymbol = '7';
	const static char GoldMerchantSymbol = '8';
	const static char GoldDragonSymbol = '9';
	const static char GoldSymbol = 'G';

	const static char PlayerSymbol = '@';

	const static char HumanSymbol = 'H';
	const static char DragonSymbol = 'D';
	const static char DwarfSymbol = 'W';
	const static char ElfSymbol = 'E';
	const static char OrcSymbol = 'O';
	const static char MerchantSymbol = 'M';
	const static char HalflingSymbol = 'L';

	const static char Chamber1Symbol = '0';
	const static char Chamber2Symbol = '1';
	const static char Chamber3Symbol = '2';
	const static char Chamber4Symbol = '3';
	const static char Chamber5Symbol = '4';

	static bool hitChance(double);
	static double drand(double, double);
	static int irand(int, int);

	static std::vector<Kind> constructProbabilityDist(Kind*, int*, int length);
	static Kind getRandomKindFrom(std::vector<Kind>);

	static Information makeInfoFromPlayer(Player*, Game*);
};

#endif
