//
// Created by Victor Navarro on 13/02/24.
// Modified and now owned by Samlo
//

#ifndef RPG_ENEMY_H
#define RPG_ENEMY_H
#include "../Character/Character.h"
#include "../Player/Player.h"
#include "../Combat/Action.h"

struct Action;
class Player;

class Enemy: public Character {
public:
    Enemy(char[30], int, int, int, int, int);
    void flee();
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;

    void levelUp(float);

    Character* getTarget(vector<Player*> teamMembers);
    Action takeAction(vector<Player*> player);
};


#endif //RPG_ENEMY_H
