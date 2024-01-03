//
// Created by stefu on 12/12/2023.
//

#include "GameManager.h"
#include "Globals.h"
#include "Cola.h"
#include "Util.h"

IntroState* IntroState::get()
{
    //Get static instance
    return &sIntroState;
}

bool IntroState::enter()
{
    //Loading success flag
    bool success = true;

    //Load background
//    if( !mBackgroundTexture.loadFromFile( "06_state_machines/introbg.png" ) )
//    {
//        printf( "Failed to intro background!\n" );
//        success = false;
//    }
//
//    //Load text
//    SDL_Color textColor = { 0x00, 0x00, 0x00, 0xFF };
//    if( !mMessageTexture.loadFromRenderedText( "Lazy Foo' Productions Presents...", textColor ) )
//    {
//        printf( "Failed to render intro text!\n" );
//        success = false;
//    }

    return success;
}

void IntroState::handleEvent( SDL_Event& e )
{
    //If the user pressed enter
    if(e.type == SDL_FINGERDOWN)
    {
        //Move onto title state
        setNextState( TitleState::get() );
    }
}

void IntroState::update()
{

}

void IntroState::render()
{
    //Show the background
    gBackgroundTexture.render( 0,0, nullptr, &gScreenRect);

    //Show the message
//    mMessageTexture.render( ( SCREEN_WIDTH - mMessageTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - mMessageTexture.getHeight() ) / 2 );
}

bool IntroState::exit()
{
    //Free background and text
    mBackgroundTexture.free();
    mMessageTexture.free();

    return true;
}
IntroState IntroState::sIntroState;

IntroState::IntroState()
{
    //No public instantiation
}

ExitState* ExitState::get()
{
    return &sExitState;
}

bool ExitState::enter()
{
    return true;
}

bool ExitState::exit()
{
    return true;
}

void ExitState::handleEvent( SDL_Event& e )
{

}

void ExitState::update()
{

}

void ExitState::render()
{

}

ExitState ExitState::sExitState;

ExitState::ExitState()
{

}

TitleState* TitleState::get(){
    return &sTitleState;
}

bool TitleState::enter()
{
    //Loading success flag
    bool success = true;

//    //Load background
//    if( !mBackgroundTexture.loadFromFile( "06_state_machines/titlebg.png" ) )
//    {
//        printf( "Failed to title background!\n" );
//        success = false;
//    }
//
//    //Load text
//    SDL_Color textColor = { 0x00, 0x00, 0x00, 0xFF };
//    if( !mMessageTexture.loadFromRenderedText( "A State Machine Demo", textColor ) )
//    {
//        printf( "Failed to render title text!\n" );
//        success = false;
//    }

    return success;
}

bool TitleState::exit()
{
    //Free background and text
    mBackgroundTexture.free();
    mMessageTexture.free();

    return true;
}

void TitleState::handleEvent( SDL_Event& e )
{
    //If the user pressed enter
    if(  e.type == SDL_FINGERDOWN  )
    {
        //Move to overworld
        setNextState( OverWorldState::get() );
    }
}

void TitleState::update()
{

}

void TitleState::render()
{
    //Show the background
    gBackgroundTexture.render( 0, 0, nullptr, &gScreenRect );
    gPlayerTexture.render(gScreenRect.w/2, gScreenRect.h/2);

    //Show the message
//    mMessageTexture.render( ( SCREEN_WIDTH - mMessageTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - mMessageTexture.getHeight() ) / 2 );
}

//Declare static instance
TitleState TitleState::sTitleState;

TitleState::TitleState()
{
    //No public instantiation
}

OverWorldState* OverWorldState::get() {
    return &sOverWorldState;
}

bool OverWorldState::enter() {
    bool success = true;
    deltaTime = 0;
    player.setPosition();
    player.logPosition();
    return success;
}

bool OverWorldState::exit(){

}

void OverWorldState::update() {

    LAST = NOW;
    NOW = SDL_GetTicks();
    deltaTime = NOW - LAST;
    if (nObstacles < 2){
        if (SDL_GetTicks() - startTime > 2500){
            createObstacle();
            startTime = SDL_GetTicks();
        }
    }

    player.move(deltaTime);
    gameManager.moveObstacles();
}

void OverWorldState::render() {
    ++scrollingOffset;
    if (scrollingOffset > gBackgroundTexture.getHeight()){
        scrollingOffset = 0;
    }
    gBackgroundTexture.render(0, scrollingOffset,nullptr, &gScreenRect);
    gBackgroundTexture.render(0, scrollingOffset - gBackgroundTexture.getHeight(),nullptr, &gScreenRect);
    gameManager.renderObstacles();
    gameManager.checkCollision(&player);
    player.render();
}

void OverWorldState::handleEvent(SDL_Event &e) {
    player.handleEvent(&e);
}

OverWorldState OverWorldState::sOverWorldState;

OverWorldState::OverWorldState()= default;

void GameManager::newObstacle(Obstacle *obs) {
    cola.encolar(obs);
}

void GameManager::moveObstacles() {
    cola.moveObstacles();
}

void GameManager::renderObstacles() {
    cola.renderObstacles();
}

bool GameManager::checkCollision(Player *player) {
    return cola.checkColission(player);
}