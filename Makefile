CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = straights
OBJECTS = main.o table.o player.o game.o gamestate.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
