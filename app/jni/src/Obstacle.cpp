//
// Created by stefu on 12/12/2023.
//

#include <Obstacle.h>
#include <Globals.h>

Obstacle::Obstacle(int x, float vel){

    velocity = vel;
    invisible = false;
    posX = x;
    posY = -4*gObstacleTexture.getHeight();

    oCollider.w = gObstacleTexture.getWidth()*3;
    oCollider.h = gObstacleTexture.getHeight()*5;
    oCollider.x = posX + gObstacleTexture.getWidth();
}

void Obstacle::render(){

    if (!invisible){
        SDL_Rect gDimension;

        gDimension.w = gObstacleTexture.getWidth()*5;
        gDimension.h = gObstacleTexture.getWidth()*5;

//        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
//        SDL_RenderFillRect( gRenderer, &oCollider );

        gObstacleTexture.render(posX, posY, nullptr, &gDimension);
    }
}

void Obstacle::move() {
    posY += static_cast<int>(velocity);
    oCollider.y = posY;

}

bool Obstacle::checkPosition() {
    if (posY > gScreenRect.h){
        posY = -4*gObstacleTexture.getHeight();
        return true;
    }
    return false;
}

void Obstacle::correctPosition() {
    posY = -4*gObstacleTexture.getHeight();
}

void Obstacle::logPosition() {
    SDL_Log("Obstacle X %d",posX);
    SDL_Log("Obstacle Y %d",posY);
}