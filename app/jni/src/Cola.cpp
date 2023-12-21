//
// Created by stefu on 12/12/2023.
//

#include <iostream>
#include <string>
#include <random>
using namespace std;

#include "Cola.h"

Cola::Nodo::Nodo(Obstacle* d) : dato{d}, siguiente{nullptr} {
}

Cola::Cola() : primero{nullptr}, ultimo{nullptr} {
}

void Cola::encolar(Obstacle* d) {
    Nodo * nuevo = new Nodo(d);

    if (primero == nullptr) // Tambien valdria if (estaVacia()); asi nos ahorramos la llamada
        primero = nuevo;
    else
        ultimo->siguiente = nuevo;
    ultimo = nuevo;
}

void Cola::desencolar() {
    if (primero == nullptr)
        SDL_Log("Intentando desencolar en una cola vacia");

    Nodo * aux = primero;
    primero = primero->siguiente;
    delete aux;
    if (primero == nullptr)
        ultimo = nullptr;
}

void Cola::mostrar(Nodo * aux) const {
    if (aux != nullptr) {
        cout << aux->dato;
        if (aux != ultimo)
            cout << ", ";
        mostrar(aux->siguiente);
    }
}

void Cola::moveObstacles() {
    for(Nodo* aux = primero; aux != nullptr; aux = aux->siguiente){
        aux->dato->move();
    }
}

void Cola::renderObstacles() {
    for(Nodo* aux = primero; aux != nullptr; aux = aux->siguiente->siguiente->siguiente){
        if (aux->dato->checkPosition()){
            aux->siguiente->dato->correctPosition();
            aux->siguiente->siguiente->dato->correctPosition();
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> distribution(1, 3);
            int randomNumber = distribution(gen);

            if (randomNumber == 1){
                aux->dato->invisible = true;
                aux->siguiente->dato->invisible = false;
                aux->siguiente->siguiente->dato->invisible = false;
            }
            else if (randomNumber == 2){
                aux->dato->invisible = false;
                aux->siguiente->dato->invisible = true;
                aux->siguiente->siguiente->dato->invisible = false;
            }
            else{
                aux->dato->invisible = false;
                aux->siguiente->dato->invisible = false;
                aux->siguiente->siguiente->dato->invisible = true;
            }
        }
        aux->dato->render();
        aux->siguiente->dato->render();
        aux->siguiente->siguiente->dato->render();

    }
}

bool Cola::checkColission(Player *player) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    bool isCol = false;

    for(Nodo* aux=primero; aux!=nullptr; aux = aux->siguiente) {
        if (!aux->dato->invisible) {
            SDL_Rect a = aux->dato->oCollider;
            SDL_Rect b = player->collider;
            leftA = a.x;
            rightA = a.x + a.w;
            topA = a.y;
            bottomA = a.y + a.h;

            leftB = b.x;
            rightB = b.x + b.w;
            topB = b.y;
            bottomB = b.y + b.h;

            if (bottomA <= topB) {
                isCol = false;
            } else if (topA >= bottomB) {
                isCol = false;
            } else if (rightA <= leftB) {
                isCol = false;
            } else if (leftA >= rightB) {
                isCol = false;
            } else {
                return true;
            }
        }
    }
    return isCol;
}
