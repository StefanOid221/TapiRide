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
    //Intro message
    LTexture mMessageTexture;
    LTexture playButton;
    TTF_Font* introFont;
    SDL_Color introColor = { 0, 0, 0 };
    SDL_Rect buttonDimension;
    SDL_Rect buttonDimension2;
    SDL_Rect buttonDimension3;

};

class GameOverState: public GameState{
public:
    static GameOverState* get();

    bool enter();
    bool exit();

    //Main loop functions
    void handleEvent( SDL_Event& e );
    void update();
    void render();
private:
    //Static instance
    static GameOverState sExitState;

    LTexture exitMessageTexture;
    LTexture exitScoreTexture;
    LTexture exitRecordTexture;
    TTF_Font* exitFont;
    SDL_Color exitColor = { 0, 0, 0 };
    LTexture restartTexture;
    SDL_Rect buttonDimension;
    SDL_Rect buttonDimension2;
    SDL_Rect buttonDimension3;

    //Private constructor
    GameOverState();
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

    Uint32 startTime = 0;
    bool directionRigth = false;
    Uint32 NOW{}, LAST{};

    double degrees = -30;

    //Private constructor
    TitleState();

    LTexture titleMessageTexture;
    LTexture tapIn;
    LTexture tapOut;
    LTexture mobileTexture;
    LTexture tiltText;
    TTF_Font* titleFont;
    SDL_Color titleColor = { 0, 0, 0 };
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
    int lastScore = 0;
    Uint32 startTime = 0;
    Uint32 NOW{}, LAST{};

    LTexture gameScoreTexture;
    TTF_Font* gameFont;
    SDL_Color gameColor = { 0, 0, 0 };

};

class ExitState : public GameState {
public:
    static ExitState *get();

    bool enter();

    bool exit();

    //Main loop functions
    void handleEvent(SDL_Event &e);

    void update();

    void render();

private:

    ExitState();

    static ExitState sExitState;
};

class GameManager{
public:
    Cola cola;

    void moveObstacles();

    bool checkCollision(Player* player);

    void newObstacle(Obstacle* obs);

    void renderObstacles();

    void correctObstaclePosition();

};

#endif //ANDROID_PROJECT_GAMEMANAGER_H
