CXX = g++
CXXFLAGS = -g -Wall -MMD
OBJECTS = main.o view/textview.o game/characters/human.o game/enemy.o game/statics/effect.o game/statics/potion.o game/level.o game/statics/boostatk.o game/statics/boostdef.o game/statics/neteffect.o game/statics/noeffect.o game/statics/woundatk.o game/statics/wounddef.o game/characters/shade.o game/game.o game/gameobject.o game/livingentity.o game/turn.o game/player.o game/controller.o tests/playerinputtests.o tests/stacktests.o tests/potioneffecttests.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = ChamberCrawler3000

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}
.PHONY : clean
clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
