/*
Name: Karina Shah
Date: 4/27/23
Description: Zombie class with the function declarations
*/

#pragma once
#ifndef zombie_shah_h
#define zombie_shah_h
#include <iostream>
using namespace std;

// Zombie class (function declarations)
class Zombie{
    public:
    Zombie();
    Zombie(char);
    char getType() const;
    void setType(char);
    bool operator==(Zombie z);
    friend ostream& operator<<(ostream&, const Zombie&);
    private:
    char type;
};

#endif