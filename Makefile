all: IslandCleaner

IslandCleaner: Point.o Item.o Player.o Map.o EventListener.o Renderer.o AudioController.o GameEngine.o main.o
	g++ -o IslandCleaner.exe Point.o Item.o Player.o Map.o EventListener.o Renderer.o AudioController.o GameEngine.o main.o

Point.o:
	g++ -std=c++17 Point.cpp -o Point.o -c

Item.o:
	g++ -std=c++17 Item.cpp -o Item.o -c

Player.o:
	g++ -std=c++17 Player.cpp -o Player.o -c

Map.o:
	g++ -std=c++17 Map.cpp -o Map.o -c

EventListener.o:
	g++ -std=c++17 EventListener.cpp -o EventListener.o -c

Renderer.o:
	g++ -std=c++17 Renderer.cpp -o Renderer.o -c

AudioController.o:
	g++ -std=c++17 AudioController.cpp -o AudioController.o -c

GameEngine.o:
	g++ -std=c++17 GameEngine.cpp -o GameEngine.o -c

main.o:
	g++ -std=c++17 main.cpp -o main.o -c

clean:
	rm -f *.o *.exe