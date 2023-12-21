#include <iostream>
#include <Globals.h>
#include <Util.h>
#include <Player.h>
#include <Obstacle.h>
#include <GameManager.h>
#include <cstring>

int main( int argc, char *argv[] )
{


    if (!init())
    {
        SDL_Log( "##SDL## Failed to initialize!%s\n", SDL_GetError());
    }
    else
    {
        if (!loadMedia()){
            SDL_Log( "##SDL## Failed to initialize!%s\n", SDL_GetError());
        }
        else {
            bool quit = false;
            SDL_Event e;
            Player player;
            int scrollingOffset = 0;

            //deltaTime
            Uint32 startTime = 0;
            Uint32 NOW = SDL_GetTicks();
            Uint32 LAST;
            double deltaTime = 0;

            //FPS
            int countedFrames = 0;
            fpsTimer.start();
            while (!quit)
            {
                LAST = NOW;
                NOW = SDL_GetTicks();
                deltaTime = NOW - LAST;
                if (nObstacles < 2){
                    if (SDL_GetTicks() - startTime > 2500){
                        createObstacle();
                        startTime = SDL_GetTicks();
                    }
                }
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//Handle button events
                    player.handleEvent(&e);
				}
                //FPS
                float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
                if( avgFPS > 2000000 )
                {
                    avgFPS = 0;
                }
                //Render Elements
                SDL_RenderClear( gRenderer );
                player.move(deltaTime);
                gameManager.moveObstacles();
                // Render elements here
                ++scrollingOffset;
                if (scrollingOffset > gBackgroundTexture.getHeight()){
                    scrollingOffset = 0;
                }
                gBackgroundTexture.render(0, scrollingOffset,nullptr, &gScreenRect);
                gBackgroundTexture.render(0, scrollingOffset - gBackgroundTexture.getHeight(),nullptr, &gScreenRect);
                player.render();
                gameManager.renderObstacles();
                gameManager.checkCollision(&player);
//                obstacle.render();
                SDL_RenderPresent( gRenderer );

                int frameTicks = capTimer.getTicks();
                if( frameTicks < SCREEN_TICKS_PER_FRAME )
                {
                    //Wait remaining time
                    SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
                }
            }
        }
    }
    
    close();
    // std::cout << "Press Enter to exit...";    
    // std::cin.get();
    return 0;
}
