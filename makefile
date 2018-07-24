oni: main.o game.o
	g++ -std=c++14 -o oni main.cpp -lncursesw

main.o: main.cpp
	g++ -std=c++14 -c main.cpp -o main.o -lncursesw

game.o: game.hpp
	g++ -std=c++14 -c game.hpp -o game.o -lncursesw

menu.o: menu.hpp
	g++ -std=c++14 -c menu.hpp -o menu.o -lncursesw

help.o: help.hpp
	g++ -std=c++14 -c help.hpp -o help.o -lncursesw

ai.o: ai.hpp
	g++ -std=c++14 -c ai.hpp -o ai.o -lncursesw

result.o: result.hpp
	g++ -std=c++14 -c result.hpp -o result.o -lncursesw

create_maze.o: create_maze.hpp
	g++ -std=c++14 -c create_maze.hpp -o create_maze.o

params.p: params.hpp
	g++ -std=c++14 -c params.hpp -o params.o

clear:
	rm  oni
