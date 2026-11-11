CXX = g++
AR = ar
CPPFLAGS = -std=c++17 -Wall
LDLIBS = -lsqlite3
ifeq ($(OS),Windows_NT)
REMOVE_BUILD_FILES = powershell -NoProfile -Command "Remove-Item -Force -ErrorAction SilentlyContinue *.o,*.a,*.exe"
else
REMOVE_BUILD_FILES = rm -f *.o *.a *.exe
endif

DATA_LIBS = libmap.a libplayer.a libitem.a libpoint.a
OBJECTS = EventListener.o Renderer.o AudioController.o GameEngine.o \
	SQLiteMapStorage.o Main.o

all: IslandCleaner.exe

IslandCleaner.exe: $(DATA_LIBS) $(OBJECTS)
	$(CXX) $(CPPFLAGS) -o $@ $(OBJECTS) $(DATA_LIBS) $(LDLIBS)

libpoint.a: Point.o
	$(AR) rcs $@ Point.o

libitem.a: Item.o libpoint.a
	$(AR) rcs $@ Item.o

libplayer.a: Player.o libpoint.a
	$(AR) rcs $@ Player.o

libmap.a: Map.o libitem.a libpoint.a
	$(AR) rcs $@ Map.o

Point.o: Point.cpp Point.hpp
	$(CXX) $(CPPFLAGS) -c Point.cpp -o $@

Item.o: Item.cpp Item.hpp Point.hpp
	$(CXX) $(CPPFLAGS) -c Item.cpp -o $@

Player.o: Player.cpp Player.hpp Point.hpp
	$(CXX) $(CPPFLAGS) -c Player.cpp -o $@

Map.o: Map.cpp Map.hpp Item.hpp Point.hpp
	$(CXX) $(CPPFLAGS) -c Map.cpp -o $@

EventListener.o: EventListener.cpp EventListener.hpp
	$(CXX) $(CPPFLAGS) -c EventListener.cpp -o $@

Renderer.o: Renderer.cpp Renderer.hpp AbstractRenderer.hpp Map.hpp Player.hpp
	$(CXX) $(CPPFLAGS) -c Renderer.cpp -o $@

AudioController.o: AudioController.cpp AudioController.hpp
	$(CXX) $(CPPFLAGS) -c AudioController.cpp -o $@

GameEngine.o: GameEngine.cpp GameEngine.hpp Map.hpp Player.hpp
	$(CXX) $(CPPFLAGS) -c GameEngine.cpp -o $@

SQLiteMapStorage.o: SQLiteMapStorage.cpp SQLiteMapStorage.hpp Map.hpp Item.hpp Point.hpp
	$(CXX) $(CPPFLAGS) -c SQLiteMapStorage.cpp -o $@

Main.o: Main.cpp Point.hpp Item.hpp Player.hpp Map.hpp GameEngine.hpp SQLiteMapStorage.hpp
	$(CXX) $(CPPFLAGS) -c Main.cpp -o $@

clean:
	$(REMOVE_BUILD_FILES)

.PHONY: all clean