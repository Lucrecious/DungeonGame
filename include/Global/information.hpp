#ifndef INFORMATION_H
#define INFORMATION_H

#include <Global/kind.hpp>
#include <string>

struct Information {
	const int atkStat;
	const int defStat;
	const int currentHP;
	const int maxHP;
	const int gold;
	const std::string name;
	const Kind kind;
	const int healsLeft;
	const int level;
};

#endif
