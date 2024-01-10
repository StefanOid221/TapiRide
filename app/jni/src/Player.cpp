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
    isInit = false;
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
    if( ( posX  < 0 ) || ( posX > gScreenRect.w - 2*gPlayerTexture.getWidth()))
    {
        //Move back
        posX -= static_cast<int>(velX);
        collissionDetected = true;
    }

    //Move the dot up or down
    posY += static_cast<int>(velY);


    //If the dot went too far up or down
    if( ( posY < 0 ) || ( posY > gScreenRect.h - collider.h - collider.h/2 - 15))
    {
        posY -=  static_cast<int>(velY);
        collissionDetected = true;
    }

    collider.x = posX + dstRect.w/2 - dstRect.w/8;
    collider.y = posY;
}

void Player:: render() {

    SDL_SetRenderDrawColor( gRenderer, 200, 40, 0, 1 );
    SDL_RenderFillRect( gRenderer, &collider );
    gPlayerTexture.render(posX, posY, nullptr, &dstRect);

}

void Player::logPosition() {
    SDL_Log("Player X %d",posX);
    SDL_Log("Player Y %d",posY);
}

void Player::setPosition() {
    posX = gScreenRect.w/2 - gPlayerTexture.getWidth();
    posY = gScreenRect.h/2;
}

void Player::setYVelocity(float y) {
    velY = y;
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
