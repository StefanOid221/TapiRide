//
// Created by stefu on 05/12/2023.
//

#include <Player.h>
#include <Globals.h>
#include <iostream>
#include <vector>
#include <cmath>

struct Touch {
    int id;
    SDL_Point startPos;
    SDL_Point endPos;

};

std::vector<Touch> activeTouches;

Player::Player() {
    posX = gScreenRect.w/2;
    posY = gScreenRect.h*3/4;
    velX = velY = 0;

    collider.w = gPlayerTexture.getWidth();
    collider.h = gPlayerTexture.getHeight()*2;

    SDL_Log("Player Col w %d", collider.w);
    SDL_Log("Player Col h %d", collider.h);
}

void Player::getPosition(int* x, int* y) {
    *x = posX;
    *y = posY;
}

void Player::handleEvent(SDL_Event *e) {
    auto handleSwipe = [&](int deltaX,int deltaY,int swipeMagnitude){
        int moveX = -deltaX;
        int moveY = -deltaY;
        applyImpulse(moveX, moveY, swipeMagnitude);

    };
    if (e->type == SDL_FINGERDOWN){
        Touch touch{};
        touch.id = e->tfinger.fingerId;
        touch.startPos = {static_cast<int>(e->tfinger.x* gScreenRect.w),
                          static_cast<int>(e->tfinger.y * gScreenRect.h)};
        activeTouches.push_back(touch);
    } else if (e->type == SDL_FINGERUP) {
        for (size_t i = 0; i < activeTouches.size(); ++i) {
            if (activeTouches[i].id == e->tfinger.fingerId) {
                activeTouches[i].endPos = { static_cast<int>(e->tfinger.x * gScreenRect.w),
                                            static_cast<int>(e->tfinger.y * gScreenRect.h) };
                int deltaX = activeTouches[i].endPos.x - activeTouches[i].startPos.x;
                int deltaY = activeTouches[i].endPos.y - activeTouches[i].startPos.y;

                // Calculate swipe distance and direction
                int swipeMagnitude = std::sqrt(deltaX * deltaX + deltaY * deltaY);
                if (swipeMagnitude > 50) { // Adjust this threshold for sensitivity
                        handleSwipe(deltaX, deltaY, swipeMagnitude);
                    }
                }
            activeTouches.erase(activeTouches.begin() + i);
            break;
        }
    }
}

void Player::applyImpulse(int x, int y, int swipeMagnitude) {
    float impulseStrength = 0.05f;
    velX = x*impulseStrength;
    velY += y*impulseStrength;
    SDL_Log(" ##SDL## VelX: %f", velX);
}


void Player::move(double deltatime){
    if (velX < 0) {
        velX += static_cast<float>(abs(deltatime * 0.05));
        if (velX > 0){
            velX = 0;
        }
    }
    else if(velX > 0){
        velX -= static_cast<float>(abs(deltatime * 0.05));
        if (velX < 0){
            velX = 0;
        }
    }
    if ( velY > 2){
        velY = 15;
    }
    else if (velY != 0){
//        velX -= velX/static_cast<float>(deltatime);
        velY += static_cast<float>(abs(deltatime * 0.1));

    }
    posX +=  static_cast<int>(velX);
    //If the dot went too far to the left or right
    if( ( posX  < 0 ) || ( posX > gScreenRect.w - 2*collider.w ) )
    {
        //Move back
        posX -= static_cast<int>(velX);
    }

    //Move the dot up or down
    posY += static_cast<int>(velY);


    //If the dot went too far up or down
    if( ( posY < 0 ) || ( posY > gScreenRect.h - collider.h - collider.h/2 - 15))
    {
        posY -=  static_cast<int>(velY);
    }

    collider.x = posX + gPlayerTexture.getWidth()/2;
    collider.y = posY;
}

void Player:: render() {
    SDL_Rect gDimension;

    gDimension.w = gPlayerTexture.getWidth()*2;
    gDimension.h = gPlayerTexture.getHeight()*2;

//    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
//    SDL_RenderFillRect( gRenderer, &collider );

    gPlayerTexture.render(posX, posY, nullptr, &gDimension);
}

void Player::logPosition() {
    SDL_Log("Player X %d",posX);
    SDL_Log("Player Y %d",posY);
}

