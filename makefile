SOURCES = $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard *.h) $(wildcard */*.ch)

enigma: main.o Enigma.o Plugboard.o Reflector.o Rotor.o
	g++ -Wall main.o Enigma.o Plugboard.o Reflector.o Rotor.o -o enigma

main.o: main.cpp Enigma.h Plugboard.h
	g++ -Wall -g -c main.cpp

Enigma.o: Enigma.cpp Enigma.h
	g++ -Wall -g -c Enigma.cpp Enigma.h

Plugboard.o: Plugboard.cpp Plugboard.h
	g++ -Wall -g -c Plugboard.cpp Plugboard.h

Reflector.o: Reflector.cpp Reflector.h
	g++ -Wall -g -c Reflector.cpp Reflector.h

Rotor.o: Rotor.cpp Rotor.h
	g++ -Wall -g -c Rotor.cpp Rotor.h

clean:
	rm -f *.o enigma
