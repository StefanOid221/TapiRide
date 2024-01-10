//
// Created by stefu on 05/12/2023.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

class Player {

public:

    int velocity = 10;

    SDL_Rect collider;

    SDL_Rect dstRect;

    Player();

    bool collissionDetected;

    bool pointScored;

    bool isInit;

//    ~Player();

    void handleEvent( SDL_Event* e );

    void render();

    void move(double deltatime);

    void getPosition(int* x, int* y);

    void applyImpulse(int x, int y, int swipeMagnitude);

    void logPosition();

    void setPosition();

    void setYVelocity(float y);

    void initPlayer();

private:

    int posX, posY;

    float velX, velY;

};

#endif //ANDROID_PROJECT_PLAYER_H
