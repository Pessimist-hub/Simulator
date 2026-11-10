CPPFLAGS = -std=c++17

all: IslandCleaner.exe

IslandCleaner.exe: Point.o Item.o Player.o Map.o EventListener.o Renderer.o AudioController.o GameEngine.o Main.o
	g++ $(CPPFLAGS) -o IslandCleaner.exe Point.o Item.o Player.o Map.o EventListener.o Renderer.o AudioController.o GameEngine.o Main.o

Point.o: Point.cpp Point.hpp
	g++ $(CPPFLAGS) -c Point.cpp -o Point.o

Item.o: Item.cpp Item.hpp Point.hpp
	g++ $(CPPFLAGS) -c Item.cpp -o Item.o

Player.o: Player.cpp Player.hpp Point.hpp
	g++ $(CPPFLAGS) -c Player.cpp -o Player.o

Map.o: Map.cpp Map.hpp Item.hpp
	g++ $(CPPFLAGS) -c Map.cpp -o Map.o

EventListener.o: EventListener.cpp EventListener.hpp
	g++ $(CPPFLAGS) -c EventListener.cpp -o EventListener.o

Renderer.o: Renderer.cpp Renderer.hpp AbstractRenderer.hpp Map.hpp Player.hpp
	g++ $(CPPFLAGS) -c Renderer.cpp -o Renderer.o

AudioController.o: AudioController.cpp AudioController.hpp
	g++ $(CPPFLAGS) -c AudioController.cpp -o AudioController.o

GameEngine.o: GameEngine.cpp GameEngine.hpp
	g++ $(CPPFLAGS) -c GameEngine.cpp -o GameEngine.o

Main.o: Main.cpp Point.hpp Item.hpp Player.hpp Map.hpp GameEngine.hpp
	g++ $(CPPFLAGS) -c Main.cpp -o Main.o

clean:
	rm -f *.o *.exe