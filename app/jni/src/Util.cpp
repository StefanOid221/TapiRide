#include <Globals.h>
#include <GameManager.h>
#include <random>
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		SDL_Log( "##SDL## SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			SDL_Log( "##SDL## Warning: Linear texture filtering not enabled!" );
		}
		SDL_DisplayMode displayMode;

		if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 )
		{
			gScreenRect.w = displayMode.w;
			gScreenRect.h = displayMode.h;
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gScreenRect.w, gScreenRect.h, SDL_WINDOW_SHOWN );
		if( gWindow == nullptr )
		{
            SDL_Log( "##SDL## Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED);
			if( gRenderer == nullptr )
			{
                SDL_Log( "##SDL## Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
                    SDL_Log( "##SDL## SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load press texture
	if( !gPlayerTexture.loadFromFile( "images/tapir.png" ) )
	{
        SDL_Log( "##SDL## Failed to load tablero texture!%s\n", SDL_GetError() );
		success = false;
	}
	if( !gBackgroundTexture.loadFromFile( "images/fondo.png" ) )
	{
		SDL_Log( "##SDL## Failed to load tablero texture!%s\n", SDL_GetError() );
		success = false;
	}
	SDL_Log("f %d", gBackgroundTexture.getWidth());
    if( !gObstacleTexture.loadFromFile( "images/car.png" ) )
    {
        SDL_Log( "##SDL## Failed to load tablero texture!%s\n", SDL_GetError() );
        success = false;
    }

	return success;
}

void close()
{
	//Free loaded images
	gBackgroundTexture.free();
	gPlayerTexture.free();
    gObstacleTexture.free();
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = nullptr;
	gRenderer = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void createObstacle() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(0, 2);
	int randomNumber = distribution(gen);
//	double scaleFactor = static_cast<float>(gScreenRect.w) / static_cast<float>(gBackgroundTexture.getWidth());
	for (int i = 0; i < 3; ++i) {
		auto* obstacle = new Obstacle( static_cast<int>(i*(2*gObstacleTexture.getWidth() + gObstacleTexture.getWidth())), 10.0);
		if (randomNumber == i){
			obstacle->invisible = true;
		}
		gameManager.newObstacle(obstacle);
	}
	nObstacles++;
}