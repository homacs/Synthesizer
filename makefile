

CPPFLAGS= -g -Wall
CC=g++





%.o : %.cpp
	$(CC) -c $(CPPFLAGS) -o $@ $< 


BINARIES=synthesizer

all: depend $(BINARIES)

clean:
	rm -f synthesizer *.o

SRCS=$(shell ls *.cpp)
OBJECTS=$(SRCS:.cpp=.o)

synthesizer: $(OBJECTS) -lSDL2 -lpthread
	$(CC) -o $@ $^ 	








depend: depend.mak

depend.mak: $(shell ls *.cpp *.h)
	@echo "building dependencies file depend.mak"
	@rm -f depend.mak
	@for s in *.cpp ; do \
		g++ -MM -MG $$s >> depend.mak ;\
	done

include depend.mak
