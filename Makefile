all: start

start:
	g++ -c main.cpp -I/home/ahmed/fun/sfml/SFML-2.6.1/include
	g++ main.o -o sfml-app -L/home/ahmed/fun/sfml/SFML-2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
	export LD_LIBRARY_PATH=/home/ahmed/fun/sfml/SFML-2.6.1/lib
	./sfml-app