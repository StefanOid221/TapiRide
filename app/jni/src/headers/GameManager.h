//
// Created by stefu on 12/12/2023.
//

#ifndef ANDROID_PROJECT_GAMEMANAGER_H
#define ANDROID_PROJECT_GAMEMANAGER_H

#include "Cola.h"
#include "Player.h"
#include "LTexture.h"

class GameState
{
public:
    //State transitions
    virtual bool enter() = 0;
    virtual bool exit() = 0;

    //Main loop functions
    virtual void handleEvent( SDL_Event& e ) = 0;
    virtual void update() = 0;
    virtual void render() = 0;

    //Make sure to call child destructors
    virtual ~GameState(){};
};

class IntroState : public GameState
{
public:
    //Static accessor
    static IntroState* get();

    //Transitions
    bool enter();
    bool exit();

    //Main loop functions
    void handleEvent( SDL_Event& e );
    void update();
    void render();

private:
    //Static instance
    static IntroState sIntroState;

    //Private constructor
    IntroState();

    //Intro background
    LTexture mBackgroundTexture;

    //Intro message
    LTexture mMessageTexture;
};

class ExitState: public GameState{
public:
    static ExitState* get();

    bool enter();
    bool exit();

    //Main loop functions
    void handleEvent( SDL_Event& e );
    void update();
    void render();
private:
    //Static instance
    static ExitState sExitState;

    //Private constructor
    ExitState();
};


class TitleState : public GameState
{
public:
    //Static accessor
    static TitleState* get();

    //Transitions
    bool enter();
    bool exit();

    //Main loop functions
    void handleEvent( SDL_Event& e );
    void update();
    void render();

private:
    //Static instance
    static TitleState sTitleState;

    //Private constructor
    TitleState();

    //Intro background
    LTexture mBackgroundTexture;

    //Intro message
    LTexture mMessageTexture;
};

class OverWorldState : public GameState {
public:
    //Static accessor
    static OverWorldState *get();

    //Transitions
    bool enter();

    bool exit();

    //Main loop functions
    void handleEvent(SDL_Event &e);

    void update();

    void render();
private:

    OverWorldState();

    static OverWorldState sOverWorldState;

    int scrollingOffset = 0;
    Uint32 startTime = 0;
    Uint32 NOW{}, LAST{};



};

class GameManager{
public:
    Cola cola;

    void moveObstacles();

    bool checkCollision(Player* player);

    void newObstacle(Obstacle* obs);

    void renderObstacles();



};

#endif //ANDROID_PROJECT_GAMEMANAGER_H
