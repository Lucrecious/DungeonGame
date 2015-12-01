#ifndef GLOBALS_H
#define GLOBALS_H

class Global {
public:
	const static int levelHeight = 25;
	const static int levelWidth = 79;

	const static char VWallSymbol = '|';
	const static char HWallSymbol = '-';
	const static char FloorSymbol = '.';
	const static char DoorSymbol = '+';
	const static char PassageSymbol = '#';

	const static char RHPotionSymbol = '0';
	const static char BAPotionSymbol = '1';
	const static char BDPotionSymbol = '2';
	const static char PHPotionSymbol = '3';
	const static char WAPotionSymbol = '4';
	const static char WDPotionSymbol = '5';
	const static char PotionSymbol = 'P';

	const static char PlayerSymbol = '@';

	const static char HumanSymbol = 'H';
};

#endif
