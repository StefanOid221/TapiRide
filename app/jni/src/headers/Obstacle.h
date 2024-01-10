//
// Created by stefu on 12/12/2023.
//

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>

class Obstacle {

public:

    float velocity;

    int obstacleTurn;

    bool invisible;

    bool scorePoints;

    Obstacle(int x, float velocity);

    SDL_Rect oCollider;

    SDL_Rect dstRect;

    //~Obstacle();

    void render();

    void move();

    bool checkPosition();

    void correctPosition();

    void logPosition();

private:

    int posX, posY;

};

#endif //ANDROID_PROJECT_OBSTACLE_H
