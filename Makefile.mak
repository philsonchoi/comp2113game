#level.o, in which depends on level.cpp and level.h

level.o: level.cpp level.h
	g++ -c level.cpp

level: level.o
	g++ level.o -o level


#main.o, which depends on main.cpp and the level.h file

main.o: main.cpp level.h
	g++ -c main.cpp

#the main is linked with the level functions here

main: main.o level.o
	g++ main.o level.o -o main

#made to clean main, main.o and level.o after used

clean:
	rm -f main.o level.o main

# a .phony is required as a placeholder while main.o, level.o and main doesn't exist.
.PHONY: clean
