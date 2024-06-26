//
// Created by Victor Navarro on 13/02/24.
//
#include "Player.h"
#include <iostream>
#include "../Utils.h"
#include <algorithm>

using namespace std;
using namespace combat_utils;


bool compareSpeed(Enemy *a, Enemy *b) {
    return a->getSpeed() > b->getSpeed();
}

Player::Player(char name[30], int health, int attack, int defense, int speed) : Character(name, health, attack, defense,
                                                                                        speed, true) {
    experience = 0;
    level = 1;
    pass = false;
}

void Player::doAttack(Character* target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    cout << CYAN << "> You have atacked " << target->getStrName() <<RESET<< endl;
    target->takeDamage(trueDamage);
    if (target->getHealth() <= 0) emote(target);
}

void Player::takeDamage(int damage) {
    setHealth(health - damage);
    cout << "You have taken " << damage << " damage" << endl;
    if (health <= 0) {
        cout <<RED<< "You have died" <<RESET<<endl;
    }
}

void Player::flee(vector<Enemy *> enemies) {
    std::sort(enemies.begin(), enemies.end(), compareSpeed);
    Enemy *fastestEnemy = enemies[0];
    bool fleed = false;
    cout <<CYAN<<"> You have attempted to flee"<<RESET<< endl;
    if (this->getSpeed() > fastestEnemy->getSpeed()) {
        cout << "You are faster than all your enemies!" << endl;
        fleed = true;
    } else {
        srand(time(NULL));
        int chance = rand() % 100;
        cout << "your chance is: " << chance << endl;
        fleed = chance > 80;
    }
    if (!fleed)
    {
        cout << "you have failed to flee!"<< STYLE << GRAY << endl;
        srand(time(NULL));
        int emote_index = rand() % 4 + 1;
        switch (emote_index)
        {
        case 1:
            cout << "  Guess you didn't train enough..." << endl;
            break;
        case 2:
            cout << "  Seems like you are too slow..." << endl;
            break;
        case 3:
            cout << "  You could use some potions to increase your speed..." << endl;
            break;
        default:
            cout << "  Looks like " << fastestEnemy->getStrName() << " is faster than you..." << endl;
            break;
        }
        cout << RESET;
    }

    this->fleed = fleed;
}

void Player::emote(Character* target) {
    srand(time(NULL));
    int emote_index = rand() % 4 + 1;
    cout <<GRAY<<STYLE;
    switch (emote_index)
    {
    case 1:
        cout << "Guess " << target->getStrName() << " was just a joke..." << endl;
        break;
    case 2:
        cout << "My sister could have beaten " << target->getStrName() << endl;
        break;
    case 3:
        cout << "FATALITY" << endl;
        break;
    default:
        cout << "Guess " << target->getStrName() << " was just a noob lol" << endl;
        break;
    }
    cout << RESET;
}

void Player::levelUp(float multiplier) {
    while (xp > maXp) {
        plevel++;

        health = maxHealth * multiplier + 1;
        maxHealth = health;
        attack = (attack * multiplier) + 1;
        defense = (defense * multiplier) + 1;
        speed = (speed * multiplier) + 1;

        xp = xp - maXp;
        maXp = 100 * (plevel * multiplier);
    }
}

int Player::checkXptoPw() {
    int levelsUpgraded = 0;
    int _initiaLevel = this->getPowerlevel();
    if (this->getXp() > this->getMaxXp() && this->getHealth() != 0) {
        this->levelUp(1.2); // TODO - change 1.2 multiplier
        cout << CYAN << BOLD << this->getStrName() << " has leveled up!! \n his new level is: " << YELLOW << plevel << RESET << endl;
        levelsUpgraded = this->getPowerlevel() - _initiaLevel;
    }
    return levelsUpgraded;
}


void Player::motd(string owo) {
    string _Owner(OWNER, 5);
    if (_Owner != owo) {
        cout << "This work has been stolen from " << OWNER << "\n\n";
    }
    else cout << "Made by " << _Owner << "\n\n";
    pass = true;
}

Character* Player::getTarget(vector<Enemy*> enemies) {
    int targetIndex = 0;
    while (true)
    {
        cout << "Choose a target" << endl;
        for (int i = 0; i < enemies.size(); i++) {
            cout <<RED<< i + 1 << ". " << enemies[i]->getStrName()<<RESET << endl;
        }
        cin >> targetIndex;

        if ((targetIndex-1) >= enemies.size() || (targetIndex-1) < 0) {
            cout << "Invalid target\n" << endl;
        } else break;
        //Added input validation (SAMLO)
    }
    return enemies[targetIndex-1];
}

Action Player::takeAction(vector<Enemy *> enemies) {
    int option = 0;
    Character *target = nullptr;

    //Esta variable guarda accion, velocidad, actor, y objetivo
    Action myAction;

    myAction.speed = this->getSpeed();
    myAction.subscriber = this;
    string hp = GREEN;
    if (this->getHealth() < 8 && pass)
    {
        hp = RED;
    } else hp = GREEN;

    bool ok = false;
    do {
        cout << CYAN << " - [" << this->getStrName() << "]{" << xp << "/" << maXp << "}" << YELLOW << " ---- |+| ----(" << hp << "HP: " << this->getHealth() << YELLOW << ")---- |#| ----";
        cout <<"(" << BLUE << "DEF: "<<this->getDefense()<< YELLOW <<")----|%|----(" << RESET << "SP: " << this->getSpeed() << YELLOW <<")----" << RESET << endl;
        cout <<"Choose an action"<< endl;
        cout << "1. Attack" << endl;
        cout << "2. Flee" << endl;
        cin >> option;

        switch (option) {
            case 1:
                target = getTarget(enemies);
                cout << endl; //ESPACIO ///////
                myAction.target = target;
                //1.
                myAction.action = [this, target]() {
                    doAttack(target);
                };
                ok = true;
                break;
            case 2:
                cout << endl; //ESPACIO ///////
                myAction.action = [this, enemies]() {
                    flee(enemies);
                };
                ok = true;
                break;
            default:
                cout << "Invalid option" << endl;
                break;
        }
    } while (!ok && pass);
    

    return myAction;
}