#ifndef GLOBALS_H
#define GLOBALS_H

#include "LTexture.h"
#include "LButton.h"
#include "GameManager.h"
#include "Player.h"
#include "LTimer.h"

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

extern LTexture gBackgroundTexture;
extern LTexture gPlayerTexture;
extern LTexture gObstacleTexture;

extern int nObstacles;
extern GameManager gameManager;

extern Player player;

extern LTimer fpsTimer;
extern LTimer capTimer;

void setNextState( GameState* nextState );
void changeState();

extern GameState* gCurrentState;
extern GameState* gNextState;

extern double deltaTime;

extern SDL_Rect gScreenRect;

extern SDL_Color textColor;
#endif