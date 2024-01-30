//
// Created by stefu on 05/12/2023.
//

#include <Player.h>
#include <Globals.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "../SDL2/src/core/android/SDL_android.h"

Player::Player() {
    isInit = false;
}

void Player::handleEvent(SDL_Event *e) {
    if (e->type == SDL_FINGERDOWN){
        SDL_Log("Y velocity: %f", velY);
        if (velY > 0)
            velY = 0;
        velY -= 25;
    }
}

void Player::move(double deltatime){
    Android_JNI_GetAccelerometerValues(accelValues);
    if (accelValues[0] < -0.05){
        velX = static_cast<float>(accelValues[0] * deltatime * 4);
    }
    if (accelValues[0] > 0.05){
        velX = static_cast<float>(accelValues[0] * deltatime * 4);
    }

    if ( velY > 30){
        velY = 30;
    }
    else if (velY != 0){
        velY += static_cast<float>(abs(deltatime * 0.1));

    }
    posX +=  static_cast<int>(velX);
    //If the dot went too far to the left or right
    if( ( posX  < -collider.w/2 ) || ( posX > gScreenRect.w - 3*collider.w - collider.w/2))
    {
        //Move back
        posX -= static_cast<int>(velX);
        collissionDetected = true;
    }

    //Move the dot up or down
    posY += static_cast<int>(velY);


    //If the dot went too far up or down
    if( ( posY < 0 ) || ( posY > gScreenRect.h - collider.h - collider.h/2))
    {
        posY -=  static_cast<int>(velY);
        collissionDetected = true;
    }

    collider.x = posX + dstRect.w/2 - dstRect.w/8;
    collider.y = posY;
}

void Player:: render() {

//    SDL_SetRenderDrawColor( gRenderer, 200, 40, 0, 1 );
//    SDL_RenderFillRect( gRenderer, &collider );
    gPlayerTexture.render(posX, posY, nullptr, &dstRect);

}

void Player::setPosition() {
    posX = gScreenRect.w/2 - gPlayerTexture.getWidth();
    posY = gScreenRect.h/2;
}

void Player::setYVelocity(float y) {
    velY = -y;
}

void Player::initPlayer() {
    posY = gScreenRect.h*3/4;
    velX = velY = 0;

    collissionDetected = false;
    pointScored = false;
    isInit = false;

    collider.w = gPlayerTexture.getWidth();
    collider.h = gPlayerTexture.getHeight()*2;

    float scaleX = static_cast<float>(gScreenRect.w) / gPlayerTexture.getWidth();
    float scaleY = static_cast<float>(gScreenRect.h) / gPlayerTexture.getHeight();

    float scale = std::min(scaleX, scaleY); // Use the smaller scale factor to maintain aspect ratio

    int scaledWidth = static_cast<int>(gPlayerTexture.getWidth() * scaleX);
    int scaledHeight = static_cast<int>(gPlayerTexture.getHeight() * scaleY);

    dstRect = { (gScreenRect.w - scaledWidth) / 2, (gScreenRect.h - scaledHeight) / 2, scaledWidth/4, scaledHeight/8 };

    collider.w = dstRect.w/4;
    collider.h = dstRect.h;

    posX = gScreenRect.w/2;
}
