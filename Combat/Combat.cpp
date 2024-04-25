//
// Created by Victor Navarro on 19/02/24.
// Modified and now owned by Samlo
//
#include "Combat.h"
#include <iostream>
#include <algorithm>
#include <conio.h>

using namespace std;

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(vector<Character *> _participants) {
    participants = std::move(_participants);
    for(auto participant: participants) {
        if(participant->getIsPlayer()) {
            teamMembers.push_back((Player*)participant);
        }
        else {
            enemies.push_back((Enemy*)participant);
        }
    }
}

Combat::Combat(vector<Player*> _teamMembers, vector<Enemy*> _enemies) {
    teamMembers = std::move(_teamMembers);
    enemies = std::move(_enemies);
}

Combat::Combat() {
    participants = vector<Character*>();
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
    if(participant->getIsPlayer()) {
        teamMembers.push_back((Player*)participant);
    }
    else {
        enemies.push_back((Enemy*)participant);
    }
}

void Combat::prepareCombat() {
    sort(participants.begin(), participants.end(), compareSpeed);
    //cout << "Participants: " << endl;
    //for (auto participant : participants) {
    //    cout << participant->getName() <<" - participant " << endl;
    //}
}

void Combat::doCombat() {
    prepareCombat();

    //Este while es 1 iteracion por ronda
    while(enemies.size() != 0 && teamMembers.size() != 0) {
        registerActions();
        executeActions();
    }

    //No se imprime el nombre del ganador
    if(enemies.size() == 0) {
        cout<<"You have won the combat"<<endl;
    }
    else {
        cout<<"The enemies have won the combat - Game Over"<<endl;
        _beep(180, 800);
        _beep(120, 650);
        _beep(90, 1000);
        cout << "Goodluck next time lol" << endl;
        getch();
    }
}

void Combat::registerActions() {
    vector<Character*>::iterator participant = participants.begin();
    //Una iteracion por turno de cada participante (player y enemigo)
    while(participant != participants.end()) {
        Character* target = nullptr;
        Action currentAction;
        if((*participant)->getIsPlayer()) {
            currentAction = ((Player*)*participant)->takeAction(enemies);
        }
        else {
            currentAction = ((Enemy*)*participant)->takeAction(teamMembers);
        }
        actions.push(currentAction);
        participant++;
    }
}

//Aqui se ejecutan las acciones
void Combat::executeActions() {
    while(!actions.empty()) {
        Action currentAction = actions.top(); //currentAction set

        if (currentAction.subscriber->getHealth() > 0) { // If actor is alive
            //cout <<MAGENTA<< currentAction.subscriber->getName() << " is alive and ready to act" <<RESET<< endl;
            if (checkActionAvailability(currentAction, 2)) {
                currentAction.action();
                actions.pop(); //remove action from queue
            }
            else if (checkActionAvailability(currentAction, 1)) {
                currentAction.action();
                actions.pop();
                
                checkForFlee(currentAction.subscriber);
                if (checkActionAvailability(currentAction, 3)) { // if player fleed
                    while (!actions.empty()) {
                        actions.pop();
                    }
                }
            } else actions.pop();
            checkParticipantStatus(currentAction.subscriber);
            checkParticipantStatus(currentAction.target);
            
        } else actions.pop(); //actor is dead, skip to next turn
        
    } 
    cout << endl; //space after all actions
}

void Combat::checkParticipantStatus(Character* participant) {
    if (participant == nullptr) return;
    if(participant->getHealth() <= 0) {
        if(participant->getIsPlayer()) {
            //cout << "Removed " << participant->getName() << endl;
            teamMembers.erase(remove(teamMembers.begin(), teamMembers.end(), participant), teamMembers.end());
        }
        else {
            enemies.erase(remove(enemies.begin(), enemies.end(), participant), enemies.end());
        }
        participants.erase(remove(participants.begin(), participants.end(), participant), participants.end());
    }
}

void Combat::checkForFlee(Character *character) {
    bool fleed = character->hasFleed();
    if(character->getHealth() > 0 && fleed) {
        if(character->getIsPlayer()) {
            cout<<YELLOW<<"You have fled the combat"<<RESET<<endl;
            teamMembers.erase(remove(teamMembers.begin(), teamMembers.end(), character), teamMembers.end());
        }
        else {
            cout<<MAGENTA<<character->getName()<<" has fled the combat"<<RESET<<endl;
            enemies.erase(remove(enemies.begin(), enemies.end(), character), enemies.end());
        }
        participants.erase(remove(participants.begin(), participants.end(), character), participants.end());
    }
}

/// <summary>
/// Checks if the current action can be preformed.
/// </summary>
/// <param name="a.">Input an (Action) variable of the current action.</param>
/// <param name="b.">Input checkType: 1 = Can flee?, 2 = Can attack target?, 3. Player has fleed? </param>
/// <returns>Returns true or false.</returns>
bool Combat::checkActionAvailability(Action currentAction, int checkType) {
    bool check = false;
    switch (checkType)
    {
    case 1: //Check if: Actor is alive and can flee (hasnt fleed yet)
        if (currentAction.target == nullptr) {
            if (currentAction.subscriber->getHealth() > 0 && !currentAction.subscriber->hasFleed()) check = true;
        }
        break;
    case 2: //Check if: Both target and actor are alive and target hasnt fleed (if there is a target)
        if (currentAction.target != nullptr) {
            if (currentAction.target->getHealth() > 0 && currentAction.subscriber->getHealth() > 0 && !currentAction.target->hasFleed()) check = true;
        }
        break;
    case 3: //Check if: Actor is player and has fleed
        if (currentAction.subscriber->getIsPlayer() && currentAction.subscriber->hasFleed()) check = true;
        break;
    default:
        cout << "Undefined checktype, returned "<<RED<< "FALSE" <<RESET<< endl;
        break;
    }
    return check;
}

string Combat::participantsToString() {
    string result = "";
    for (int i = 0; i < participants.size(); i++) {
        result += participants[i]->toString() + "\n";
    }
    return result;
}