# This is the Makefile for Group 1 project
graphic.o: graphic.cpp graphic.h
	g++ -c graphic.cpp

fileIO.o: fileIO.cpp fileIO.h
	g++ -c fileIO.cpp

check_card.o: graphic.h check_card.cpp check_card.h
	g++ -c check_card.cpp

generateCard.o: graphic.h generateCard.cpp generateCard.h
	g++ -c generateCard.cpp

main.o: main.cpp
	g++ -c main.cpp

main: graphic.o fileIO.o check_card.o generateCard.o main.o
	g++ -pedantic-errors -std=c++11 graphic.o fileIO.o check_card.o generateCard.o main.o -o main

clean:
	rm -f graphic.o fileIO.o check_card.o generateCard.o main.o main

.PHONY: clean