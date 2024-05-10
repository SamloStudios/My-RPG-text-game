//
// Created by Victor Navarro on 13/02/24.
// Modified and now owned by Samlo
//

#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H
#include<string>
#include "../Combat/Action.h"
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define OWNER   "Samlo"
#define BLINK   "\033[5m"
#define STYLE   "\033[3m"
#define GRAY    "\033[90m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"

using namespace std;

class Character {
protected:
    char name[30] = { 'U','n','n','a','m','e','d' };
    int health;
    int maxHealth;
    int attack;
    int defense;
    int speed;
    int xp = 0;
    int plevel = 1;
    int maXp = 100;
    bool isPlayer;
    bool fleed;

public:
    Character(char[30], int, int, int, int, bool);

    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;
    
    void levelUp (int levels);
    void setName(char [30]);
    string getName();
    void setHealth(int);
    int getHealth();
    void setAttack(int);
    int getAttack();
    void setDefense(int);
    int getDefense();
    void setSpeed(int);
    int getSpeed();
    void setXp(int);
    int getXp();
    void setPowerlevel(int);
    int getPowerlevel();
    string toString();
    bool getIsPlayer();
    bool hasFleed();
    bool isThisPlagiarised(string);
};


#endif //RPG_SAMLO_H
