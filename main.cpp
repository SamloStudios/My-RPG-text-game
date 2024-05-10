//13/3/2024
//CREATED BY SAMLO

#include <iostream>
#include "Enemy/Enemy.h"
#include "Player/Player.h"
#include "Combat/Combat.h"
#include <queue>

using namespace std;

int main() {
    string codeOwner = "Samlo";

    Player *player = new Player("Victor", 50, 7, 2, 5);
    // char name[30], int health, int attack, int defense, int speed, int _plevel
    Enemy *enemy = new Enemy("Goblin", 10, 5, 2, 7, 1);
    enemy->addToXp(250); // ADDED XP WITH DEMONSTRATION PURPOSES
    Enemy *enemy2 = new Enemy("Orc", 20, 4, 2, 2, 1);
    Enemy* enemy3 = new Enemy(NULL, 20, 4, 2, 2, 1); //Character names can now be NULL!

    player->isThisPlagiarised(codeOwner);
    vector<Character*> participants;
    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);
    participants.push_back(enemy3);

    player->motd(codeOwner);
    Combat* combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete enemy2;
    delete combat;

    return 0;
}
