/*
Name: Karina Shah
Date: 4/27/23
Description: Zombie class with the function implementation
*/

#include "zombie_shah.h"
#include <iostream>
using namespace std;

// Empty Constructor
Zombie::Zombie(){

}

// Constructor: Sets char t to type
Zombie::Zombie(char t){
    type = t;
}

// Getter and Setter
char Zombie::getType() const{
    return type;
}

void Zombie::setType(char t){
    type = t;
}

// == operator overload; checks to see if the types are equal
bool Zombie::operator==(Zombie z){
    if(type == z.getType()){
        return true;
    }
    return false;
}

// << operator overload; prints out type with brackets
ostream& operator<<(ostream& out, const Zombie &z){
    return out << "[" << z.getType() << "]";
}