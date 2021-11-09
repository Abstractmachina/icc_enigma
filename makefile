SOURCES = $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard *.h) $(wildcard */*.ch) 

enigma: main.o enigma.o plugboard.o
	g++ -Wall main.o enigma.o plugboard.o -o enigma#

main.o: main.cpp Enigma.h Plugboard.h
	g++ -Wall -g -c main.cpp

enigma.o: Enigma.cpp Enigma.h
	g++ -Wall -g -c Enigma.cpp Enigma.h

plugboard.o: Plugboard.cpp Plugboard.h
	g++ -Wall -g -c Plugboard.cpp Plugboard.h

clean:
	rm -f *.o enigma
