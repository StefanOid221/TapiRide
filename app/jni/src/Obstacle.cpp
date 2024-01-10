//
// Created by stefu on 12/12/2023.
//

#include <Obstacle.h>
#include <Globals.h>

Obstacle::Obstacle(int x, float vel){

    velocity = vel;
    invisible = false;
    obstacleTurn = 0;
    scorePoints = false;
    posY = -4*gObstacleTexture.getHeight();

    float scaleX = static_cast<float>(gScreenRect.w) / gObstacleTexture.getWidth();
    float scaleY = static_cast<float>(gScreenRect.h) / gObstacleTexture.getHeight();

    float scale = std::min(scaleX, scaleY); // Use the smaller scale factor to maintain aspect ratio

    int scaledWidth = static_cast<int>(gObstacleTexture.getWidth() * scaleX);
    int scaledHeight = static_cast<int>(gObstacleTexture.getHeight() * scaleY);

    dstRect = { (gScreenRect.w - scaledWidth) / 2, (gScreenRect.h - scaledHeight) / 2, scaledWidth/2, scaledHeight/4 };

    oCollider.w = dstRect.w/2;
    oCollider.h = dstRect.h;
    if (x ==0){
        posX = x * dstRect.w/2 - dstRect.w/10;
    }
    else if (x == 1){
        posX = x * dstRect.w/2 ;
    }
    else {
        posX = x * dstRect.w/2 + dstRect.w/10;
    }

    oCollider.x = posX + gObstacleTexture.getWidth();
}

void Obstacle::render(){

    if (!invisible){
        SDL_Rect gDimension;
//        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
//        SDL_RenderFillRect( gRenderer, &oCollider );

        gObstacleTexture.render(posX, posY, nullptr, &dstRect);
    }
}

void Obstacle::move() {
    posY += static_cast<int>(velocity);
    oCollider.y = posY;

}

bool Obstacle::checkPosition() {
    if (posY > gScreenRect.h){
        posY = -2500*obstacleTurn;
        return true;
    }
    return false;
}

void Obstacle::correctPosition() {
    posY = -2500*obstacleTurn;
}

void Obstacle::logPosition() {
    SDL_Log("Obstacle X %d",posX);
    SDL_Log("Obstacle Y %d",posY);
}