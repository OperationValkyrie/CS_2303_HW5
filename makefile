# Jonathan Chang
# CS 2303 C02 18
# Assignment 5
# makefile

all: Sim

CFLAGS = -c -g -Wall

Sim: Sim.o Grid.o Organism.o Ant.o Doodlebug.o *.h
	g++ *.o -lm
	
Sim.o: Sim.cpp *.h
	gcc $(CFLAGS) Sim.cpp
	
Grid.o: Grid.cpp *.h
	gcc $(CFLAGS) Grid.cpp
	
Organism.o: Organism.cpp *.h
	gcc $(CFLAGS) Organism.cpp
	
Ant.o: Ant.cpp *.h
	gcc $(CFLAGS) Ant.cpp
	
Doodlebug.o: Doodlebug.cpp *.h
	gcc $(CFLAGS) Doodlebug.cpp
	
clean:
	rm -f *.o qSim
	rm -f -r html latex

docs:
	doxygen
	# Following lines are only needed if we want to access doc pages
	#   using a Web server.
	#chmod go+r html/*
	#cp html/* ~/public_html/cs2303assig3
