//
// Created by stefu on 12/12/2023.
//

#ifndef ANDROID_PROJECT_GAMEMANAGER_H
#define ANDROID_PROJECT_GAMEMANAGER_H

#include "Cola.h"
#include "Player.h"

class GameManager{
public:
    Cola cola;

    void moveObstacles();

    bool checkCollision(Player* player);

    void newObstacle(Obstacle* obs);

    void renderObstacles();

};
#endif //ANDROID_PROJECT_GAMEMANAGER_H
