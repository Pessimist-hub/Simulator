#include "Item.hpp"

Item::Item() : name(""), position(), value(0) {}

Item::Item(const std::string& _name, const Point& _position, int _value)
    : name(_name), position(_position), value(_value) {}

Item::Item(const Item& other)
    : name(other.name), position(other.position), value(other.value) {}

Item& Item::operator=(const Item& other) {
    name = other.name;
    position = other.position;   
    value = other.value;
    return *this;
}

bool Item::operator==(const Item& other) const {
    return name == other.name && position == other.position && value == other.value;
}

std::istream& operator>>(std::istream& in, Item& item) {
    std::string name;
    Point position;
    int value;
    in >> name >> position >> value;   
    item = Item(name, position, value);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Item& item) {
    out << item.name << " " << item.position << " " << item.value;
    return out;
}