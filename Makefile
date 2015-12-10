CC = g++

CFLAGS = -std=c++11 -Wall -g

INCLUDES = -I./include

SRCS = $(wildcard src/*.cpp) $(wildcard src/Game/*.cpp) $(wildcard src/Game/Characters/*.cpp) $(wildcard src/Game/Statics/*.cpp) $(wildcard src/Global/*.cpp) $(wildcard src/View/*.cpp) $(wildcard src/Utils/*.cpp)

OBJS = $(SRCS:.cpp=.o)

MAIN = Dungeon

.PHONY: depend clean

all:	$(MAIN)
	@echo ${MAIN} has been compiled

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS) $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
