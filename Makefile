CXX = g++
CXXFLAGS = -g -Wall -MMD
OBJECTS = main.o Game/gameobject.o Game/livingentity.o Game/turn.o Game/player.o Game/controller.o tests/playerInputTests.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = ChamberCrawler3000

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}
.PHONY : clean
clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
