CXX = g++
CXXFLAGS = -g -Wall -MMD
OBJECTS = main.o game/characters/shade.o game/game.o game/gameobject.o game/livingentity.o game/turn.o game/player.o game/controller.o tests/playerInputTests.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = ChamberCrawler3000

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}
.PHONY : clean
clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
