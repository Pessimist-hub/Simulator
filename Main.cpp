#include <iostream>
#include <sstream>
#include "GameEngine.hpp"

int main() {
    
    Point a(1, 2, 3);
    Point b = a;                
    Point c;                     
    c = a;                       
    std::cout << "Point b: " << b << "\n";
    std::cout << "a == c: " << (a == c) << "\n";
    std::cout << "a != Point(): " << (a != Point()) << "\n";

 
    Item bottle("Bottle", Point(2, 0, 5), 10);
    Item copy = bottle;
    std::cout << "Item: " << bottle << "\n";
    std::cout << "bottle == copy: " << (bottle == copy) << "\n";

    
    Player player(Point(0, 0, 0), 5, 1.0f, 1.5f);
    std::cout << "Player: " << player << "\n";

    
    std::istringstream input("12 20 2 Bottle 1 0 1 10 Can 3 0 4 5");
    Map map;
    input >> map;
    std::cout << "Map:\n" << map << "\n";


    GameEngine game;
    game.Init();
    game.Run();
    return 0;
}