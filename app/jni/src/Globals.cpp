#include <Globals.h>

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

LTexture gBackgroundTexture;
LTexture gPlayerTexture;
LTexture gObstacleTexture;
LTexture gFontTexture;

SDL_Rect gScreenRect;
GameManager gameManager;
Player player;

TTF_Font* gFont = nullptr;

LTimer fpsTimer;
LTimer capTimer;

GameState* gCurrentState = nullptr;
GameState* gNextState = nullptr;
double deltaTime;

int nObstacles = 0;
int actualScore = 0;
int recordScore = 0;

SDL_Color textColor = { 0, 0, 0 };