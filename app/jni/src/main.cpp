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
            SDL_Event e;

            //FPS
            int countedFrames = 0;
            fpsTimer.start();

            gCurrentState = IntroState::get();
            gCurrentState->enter();

            while (gCurrentState != ExitState::get() )
            {
				while( SDL_PollEvent( &e ) != 0 )
				{
                    gCurrentState->handleEvent( e );
					//User requests quit
					if( e.type == SDL_QUIT )
					{
                        setNextState( ExitState::get() );
					}
				}
                //FPS
                float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
                if( avgFPS > 2000000 )
                {
                    avgFPS = 0;
                }
                gCurrentState->update();
                changeState();
                //Render Elements
//                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                gCurrentState->render();
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
