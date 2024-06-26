//
// Created by Victor Navarro on 13/02/24.
// Modified and now owned by Samlo
//
#include "Enemy.h"
#include <iostream>


using namespace std;

//TODO: Check the circular dependency
int getRolledAttack(int attack) {
    int lowerLimit = attack * .80;
    return (rand() % (attack - lowerLimit)) + lowerLimit;
}

Enemy::Enemy(char name[30], int health, int attack, int defense, int speed, int _plevel) : Character(name, health, attack, defense, speed, false) {
    plevel = _plevel;
    maXp *= plevel;
    xp = 10 * plevel;  //TODO - Refactor the constructor to encapsule a struct with all damn definitions
    //also make somethin here idk that gives the enemies random stats (based on the struct contents)
}

void Enemy::flee() {
    cout << "> " << this->getStrName() << " has fleed!" << endl;
    this->fleed = true;
    //cout << this->fleed << "fleed Enemy" << endl;
}

void Enemy::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    cout << "> " << this->getStrName() <<YELLOW<<" {lvl:" <<RED<< plevel <<YELLOW<< ", xp: " <<MAGENTA<< xp <<YELLOW<<"}"<<RESET<< " has attacked you!" << endl;
    target->takeDamage(trueDamage);
}

void Enemy::takeDamage(int damage) {
    setHealth(getHealth() - damage);
    if(getHealth() <= 0) {
        cout<<RED<<getStrName()<<" has died"<<RESET<<endl;
    }
    else {
        cout<<getStrName()<<" has taken " << damage << " damage" << endl;
    }
}

Character* Enemy::getTarget(vector<Player *> teamMembers) {
    // Obtiene el miembro del equipo con menos vida
    int targetIndex = 0;
    int lowestHealth = INT_MAX;
    for(int i=0; i < teamMembers.size(); i++) {
        if(teamMembers[i]->getHealth() < lowestHealth) {
            lowestHealth = teamMembers[i]->getHealth();
            targetIndex = i;
        }
    }

    return teamMembers[targetIndex];
}

void Enemy::levelUp(float multiplier) {
    plevel++;

    health = maxHealth * multiplier + 1;
    maxHealth = health;
    attack = (attack * multiplier) + 1;
    defense = (defense * multiplier) + 1;
    speed = (speed * multiplier) + 1;

    xp *= plevel * multiplier;
}

Action Enemy::takeAction(vector<Player *> player) {
    Action myAction;
    myAction.speed = getSpeed();
    myAction.subscriber = this;
    Character* target = getTarget(player);

    // flee if dying
    if ((this->getHealth() < (this->maxHealth * 0.50)) && rand() % 100 < 5) //Reajustar al 5%
    {
        myAction.action = [this, target]() {
            flee();
        };
    }
    else { // else attack
        myAction.target = target;
        myAction.action = [this, target]() {
            doAttack(target);
        };
    }

    return myAction;
}

