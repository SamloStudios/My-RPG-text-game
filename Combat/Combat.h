//
// Created by Victor Navarro on 19/02/24.
// Modified and now owned by Samlo
//

#ifndef RPG_COMBAT_H
#define RPG_COMBAT_H
#pragma once
#include "../Character/Character.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "Action.h"
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Combat {
private:
    //Realmente sigo necesitando este vector?
    vector<Character*> participants;
    vector<Player*> teamMembers;
    vector<Enemy*> enemies;
    //Priority queue de acciones
    priority_queue<Action> actions;

    void prepareCombat();
    void registerActions();
    void executeActions();


    void checkParticipantStatus(Character* participant);
    void checkForFlee(Character* character);
    void rewardPlayer(Character* slayedEnemy);

    bool checkActionAvailability(Action currentAction, int checkType);

public:
    Combat(vector<Character*> _participants);
    Combat(vector<Player*> _teamMembers, vector<Enemy*> _enemies);
    Combat();
    void addParticipant(Character *participant);
    void doCombat();
    string participantsToString();
};


#endif //RPG_COMBAT_H
