#include "EventListener.hpp"
#include <iostream>
#include <cctype>

char EventListener::GetEvent() {
    char key;
    std::cin >> key;
    return (char)toupper(key);
}