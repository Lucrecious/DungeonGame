#include <Game/Characters/elf.hpp>

Elf::Elf() : Enemy(ElfKind, 30, 10, 140) {
	this->setName("Elf");
}
