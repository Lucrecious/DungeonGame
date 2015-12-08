#include <Game/Characters/dwarf.hpp>

Dwarf::Dwarf() : Enemy(DwarfKind, 20, 30, 100) {
	this->setName("Dwarf");
}
