#include <Globals.h>

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

LTexture gBackgroundTexture;
LTexture gPlayerTexture;
LTexture gObstacleTexture;

SDL_Rect gScreenRect;
GameManager gameManager;

LTimer fpsTimer;
LTimer capTimer;

int nObstacles = 0;

SDL_Color textColor = { 0, 0, 0 };