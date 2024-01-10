//
// Created by stefu on 12/12/2023.
//

#ifndef ANDROID_PROJECT_COLA_H
#define ANDROID_PROJECT_COLA_H

#include "Obstacle.h"
#include "Player.h"

class Cola {

    struct Nodo {
        Obstacle* dato;
        Nodo * siguiente;
        Nodo(Obstacle*);
    };

    Nodo * primero;
    Nodo * ultimo;

    void mostrar(Nodo *) const;

public:

    Cola();

    void encolar(Obstacle*);

    void desencolar();

    void moveObstacles();

    void renderObstacles();

    bool checkColission(Player* player);

    void correctAllObstacles();

};

#endif //ANDROID_PROJECT_COLA_H
