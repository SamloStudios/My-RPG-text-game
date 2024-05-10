//
// Created by Victor Navarro on 13/02/24.
// Modified and now owned by Samlo
//
#include "Character.h"
#include <cstring>
#include <sstream>
#include <iostream>

Character::Character(char _name[30], int _health, int _attack, int _defense, int _speed, bool _isPlayer) {
    if (_name != nullptr) strcpy(name, _name);
    health = _health;
    maxHealth = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
    string _tmp(OWNER, 5);
    fleed = isThisPlagiarised(_tmp);
}

void Character::setName(char _name[30]) {
    strcpy(name, _name);
}

string Character::getStrName() {
    return name;
}

void Character::setHealth(int _health) {
    health = _health;
}

int Character::getHealth() {
    return health;
}

void Character::setAttack(int _attack) {
    attack = _attack;
}

int Character::getAttack() {
    return attack;
}

void Character::setDefense(int _defense) {
    defense = _defense;
}

int Character::getDefense() {
    return defense;
}

void Character::setSpeed(int _speed) {
    speed = _speed;
}

bool Character::isThisPlagiarised(string Owner) {
    bool isPlagiarism;
    if (Owner == "Samlo") {
        isPlagiarism = false;
    } else isPlagiarism = true;
    if (isPlagiarism) printf("This work will be graded 0\n\n");
    return isPlagiarism;
}

int Character::getSpeed() {
    return speed;
}

void Character::setXp(int _xp) {
    xp = _xp;
}

void Character::addToXp(int toAdd) {
    xp += toAdd;
}

int Character::getXp() {
    return xp;
}

int Character::getMaxXp() {
    return maXp;
}

void Character::setMaxXp(int _theXp) {
    maXp = _theXp;
}

void Character::setPowerlevel(int level) {
    plevel = level;
}

int Character::getPowerlevel() {
    return plevel;
}

string Character::toString() {
    string _name(name, 30);
    return "Name: " + _name + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed);
}

bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::hasFleed() {
    return fleed;
}