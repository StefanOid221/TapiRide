//
// Created by stefu on 12/12/2023.
//

#include "GameManager.h"
#include "Cola.h"

void GameManager::newObstacle(Obstacle *obs) {
    cola.encolar(obs);
}

void GameManager::moveObstacles() {
    cola.moveObstacles();
}

void GameManager::renderObstacles() {
    cola.renderObstacles();
}

bool GameManager::checkCollision(Player *player) {
    return cola.checkColission(player);
}