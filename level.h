#ifndef LEVEL_H
#define LEVEL_H
#include <string>
using namespace std;

// all struct declarations are made here as both level.cpp and main.cpp require them.

struct player
{
    string name;
    int health = 100;
    int mana = 40;
    int charm;
    int strength;
    int agility;
    int mindamage = strength - 1;
    int maxdamage = strength * 4;
    int stagelevel = 0;
    string levelonechoice;
};

struct enemy
{
  int health;
  int strength;
  int mindamage;
  int maxdamage;
  string weakness;
  string resist;
};

// function declarations are made here as main.cpp call level functions that do not exist in main.cpp

void level1(player& playerone);
void level2(player& playerone);
void level3(player& playerone);
void loadgame(player& playerone);



#endif
