//
// Created by stefu on 12/12/2023.
//

#include <cmath>
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

    introColor = { 255, 165, 0,0 };
    SDL_Color blackColor = {0,0,0,0};
    introFont = TTF_OpenFont("fonts/MOSKOMAPPA.otf", 200);
    if( introFont == nullptr )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    if(!mMessageTexture.loadFromRenderedText("TapiRide", introColor, introFont)){
        SDL_Log("Failed font texture");
        success= false;
    }
    if(!playButton.loadFromRenderedText("Play", blackColor, introFont)){
        SDL_Log("Failed font texture");
        success= false;
    }
    buttonDimension.w = playButton.getWidth();
    buttonDimension.h = playButton.getHeight();
    buttonDimension2.w = buttonDimension.w + 20;
    buttonDimension2.h = buttonDimension.h + 20;
    buttonDimension3.w = buttonDimension2.w + 20;
    buttonDimension3.h = buttonDimension2.h + 20;
    buttonDimension.x = gScreenRect.w/2 - playButton.getWidth()/2;
    buttonDimension.y = gScreenRect.h * 3/4 - 10;
    buttonDimension2.x = buttonDimension.x - 10;
    buttonDimension2.y = buttonDimension.y - 10;
    buttonDimension3.x = buttonDimension.x - 20;
    buttonDimension3.y = buttonDimension.y - 20;
    Mix_HaltChannel(-1);
    return success;
}

void IntroState::handleEvent( SDL_Event& e )
{
    //If the user pressed enter
    if(e.type == SDL_FINGERUP)
    {
        bool inside = true;
        int x, y;
        SDL_GetMouseState( &x, &y );

        if (x < buttonDimension3.x){
            inside = false;
        }
        else if (x > buttonDimension3.x + buttonDimension3.w){
            inside = false;
        }
        else if(y < buttonDimension3.y){
            inside = false;
        }
        else if (y > buttonDimension3.y + buttonDimension3.h){
            inside = false;
        }
        if (inside){
            setNextState( TitleState::get() );
        }
    }
}

void IntroState::update()
{

}

void IntroState::render()
{

    //Show the background
    gBackgroundTexture.render( 0,0, nullptr, &gScreenRect);
    mMessageTexture.render(gScreenRect.w/2 - mMessageTexture.getWidth()/2, 200);
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
    SDL_RenderFillRect( gRenderer, &buttonDimension3 );
    SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 0 );
    SDL_RenderFillRect( gRenderer, &buttonDimension2 );
    SDL_SetRenderDrawColor( gRenderer, 255, 165, 0, 0 );
    SDL_RenderFillRect( gRenderer, &buttonDimension );
    playButton.render(gScreenRect.w/2 - playButton.getWidth()/2, gScreenRect.h * 3/4);
}

bool IntroState::exit()
{
    //Free background and text
    mMessageTexture.free();
    playButton.free();
    introFont = nullptr;

    return true;
}
IntroState IntroState::sIntroState;

IntroState::IntroState()
{
    //No public instantiation
}

GameOverState* GameOverState::get()
{
    return &sExitState;
}

bool GameOverState::enter()
{
    Mix_PlayChannel(-1, gMusicSound, 0);
    SDL_Log("Exit state enter");
    bool success = true;
    exitColor = { 255, 165, 0,0 };
    SDL_Color blackColor = {0,0,0,0};
    exitFont = TTF_OpenFont("fonts/MOSKOMAPPA.otf", 120);
    if( exitFont == nullptr )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    if(!exitMessageTexture.loadFromRenderedText("Game Over!", exitColor, exitFont)){
        SDL_Log("Failed font texture");
        success= false;
    }
    if(!exitRecordTexture.loadFromRenderedText(("Your Record: " + std::to_string(recordScore)), exitColor, exitFont)){
        SDL_Log("Failed font texture");
        success= false;
    }
    if(!exitScoreTexture.loadFromRenderedText(("Your Score: " + std::to_string(actualScore)), exitColor, exitFont)){
        SDL_Log("Failed font texture");
        success= false;
    }
    if(!restartTexture.loadFromRenderedText("Restart", blackColor, exitFont)){
        SDL_Log("Failed font texture");
        success= false;
    }
    buttonDimension.w = restartTexture.getWidth();
    buttonDimension.h = restartTexture.getHeight();
    buttonDimension2.w = buttonDimension.w + 20;
    buttonDimension2.h = buttonDimension.h + 20;
    buttonDimension3.w = buttonDimension2.w + 20;
    buttonDimension3.h = buttonDimension2.h + 20;
    buttonDimension.x = gScreenRect.w/2 - restartTexture.getWidth()/2;
    buttonDimension.y = gScreenRect.h * 3/4 - 10;
    buttonDimension2.x = buttonDimension.x - 10;
    buttonDimension2.y = buttonDimension.y - 10;
    buttonDimension3.x = buttonDimension.x - 20;
    buttonDimension3.y = buttonDimension.y - 20;
    return success;
}

bool GameOverState::exit()
{
    exitMessageTexture.free();
    exitScoreTexture.free();
    exitRecordTexture.free();
    restartTexture.free();
    exitFont = nullptr;
    return true;
}

void GameOverState::handleEvent( SDL_Event& e )
{
    if(e.type == SDL_FINGERUP)
    {
        bool inside = true;
        int x, y;
        SDL_GetMouseState( &x, &y );

        if (x < buttonDimension3.x){
            inside = false;
        }
        else if (x > buttonDimension3.x + buttonDimension3.w){
            inside = false;
        }
        else if(y < buttonDimension3.y){
            inside = false;
        }
        else if (y > buttonDimension3.y + buttonDimension3.h){
            inside = false;
        }
        if (inside){
            setNextState( IntroState::get() );
        }
    }
}

void GameOverState::update()
{

}

void GameOverState::render()
{
    gBackgroundTexture.render( 0,0, nullptr, &gScreenRect);
    exitMessageTexture.render(gScreenRect.w/2 - exitMessageTexture.getWidth()/2, 200);
    exitScoreTexture.render(gScreenRect.w/2 - exitScoreTexture.getWidth()/2, 600);
    exitRecordTexture.render(gScreenRect.w/2 - exitRecordTexture.getWidth()/2, 800);
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
    SDL_RenderFillRect( gRenderer, &buttonDimension3 );
    SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 0 );
    SDL_RenderFillRect( gRenderer, &buttonDimension2 );
    SDL_SetRenderDrawColor( gRenderer, 255, 165, 0, 0 );
    SDL_RenderFillRect( gRenderer, &buttonDimension );
    restartTexture.render(gScreenRect.w/2 - restartTexture.getWidth()/2, gScreenRect.h * 3/4);

}

GameOverState GameOverState::sExitState;

GameOverState::GameOverState()
{

}

TitleState* TitleState::get(){
    return &sTitleState;
}

bool TitleState::enter()
{
    //Loading success flag
    bool success = true;

    titleColor = { 255, 165, 0,0 };
    titleFont = TTF_OpenFont("fonts/MOSKOMAPPA.otf", 140);
    if( titleFont == nullptr )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    if(!titleMessageTexture.loadFromRenderedText("Touch to start!", titleColor, titleFont)){
        SDL_Log("Failed font texture");
        success= false;
    }
    if (!tapIn.loadFromFile("images/tapIn.png")){
        SDL_Log( "##SDL## Failed to load tutorial texture!%s\n", SDL_GetError() );
        success = false;
    }
    if (!tapOut.loadFromFile("images/tapOut.png")){
        SDL_Log( "##SDL## Failed to load tutorial texture!%s\n", SDL_GetError() );
        success = false;
    }
    if (!tiltText.loadFromFile("images/messageTilt.png")){
        SDL_Log( "##SDL## Failed to load tutorial texture!%s\n", SDL_GetError() );
        success = false;
    }
    if (!mobileTexture.loadFromFile("images/movilGirador.png")){
        SDL_Log( "##SDL## Failed to load tutorial texture!%s\n", SDL_GetError() );
        success = false;
    }
    if (!player.isInit){
        player.initPlayer();
    }
    degrees = 0;
    return success;
}

bool TitleState::exit()
{
    //Free background and text
    titleMessageTexture.free();
    titleFont = nullptr;
    tapIn.free();
    tapOut.free();
    mobileTexture.free();
    tiltText.free();
    return true;
}

void TitleState::handleEvent( SDL_Event& e )
{
    //If the user pressed enter
    if(  e.type == SDL_FINGERDOWN  )
    {
        setNextState( OverWorldState::get() );
    }
}

void TitleState::update()
{
    LAST = NOW;
    NOW = SDL_GetTicks();
    deltaTime = NOW - LAST;
}

void TitleState::render()
{
    SDL_Rect insRect;
    insRect.w = player.dstRect.w*2;
    insRect.h = player.dstRect.h*2;
    insRect.x = gScreenRect.w;
    insRect.y = gScreenRect.h;
    //Show the background
    gBackgroundTexture.render( 0, 0, nullptr, &gScreenRect );
    gPlayerTexture.render(gScreenRect.w/2 -player.dstRect.w/2, gScreenRect.h/2, nullptr, &player.dstRect);
    titleMessageTexture.render(gScreenRect.w/2 - titleMessageTexture.getWidth()/2, 400);
    if (SDL_GetTicks() - startTime > 500){
        tapIn.render(gScreenRect.w/4 - insRect.w/2, gScreenRect.h*3/4 -  insRect.h/2, nullptr, &insRect);
        if (SDL_GetTicks() - startTime > 1000)
            startTime = SDL_GetTicks();
    }
    else{
        tapOut.render(gScreenRect.w/4- insRect.w/2, gScreenRect.h*3/4 -  insRect.h/2, nullptr, &insRect);
    }
    if (!directionRigth){
        degrees -= 0.7;
        if (degrees < -12){
            directionRigth = true;
        }
    }
    else{
        degrees += 0.7;
        if (degrees > 12){
            directionRigth = false;
        }
    }

    mobileTexture.render(gScreenRect.w/4 + insRect.w/2, gScreenRect.h*3/4 -  insRect.h/2, nullptr, &insRect, degrees,
                         nullptr, SDL_FLIP_HORIZONTAL);
    tiltText.render(gScreenRect.w/4 + insRect.w/2, gScreenRect.h*3/4-  insRect.h/2, nullptr, &insRect);



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
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( gSkateMusicSound, -1 );
    }
    gameManager.correctObstaclePosition();
    bool success = true;
    deltaTime = 0;
    player.setPosition();

    player.setYVelocity(30);

    actualScore = 0;
    lastScore = 0;

    gameColor = { 255, 165, 0,0 };
    gameFont = TTF_OpenFont("fonts/MOSKOMAPPA.otf", 140);
    if( gameFont == nullptr )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    if(!gameScoreTexture.loadFromRenderedText("0", gameColor, gameFont)){
        SDL_Log("Failed font texture");
        success= false;
    }
    return success;
}

bool OverWorldState::exit(){
    Mix_HaltMusic();
    gameScoreTexture.free();
    gameFont = nullptr;
    if (recordScore < actualScore){
        recordScore = actualScore;
        savePointsRecord(recordScore);
    }
    gameManager.correctObstaclePosition();
    return true;
}

void OverWorldState::update() {

    LAST = NOW;
    NOW = SDL_GetTicks();
    deltaTime = NOW - LAST;
    if (nObstacles < 3){
        createObstacle();
        SDL_GetTicks();
    }
    if (deltaTime < 100){
        player.move(deltaTime);
    }
    gameManager.moveObstacles();
    if (player.collissionDetected){
        player.collissionDetected = false;
        setNextState(GameOverState::get());
    }
    if(player.pointScored){
        actualScore += 1;
        player.pointScored = false;
    }
    if (lastScore != actualScore){
        if(!gameScoreTexture.loadFromRenderedText(std::to_string(actualScore), gameColor, gameFont)){
            SDL_Log("Failed font texture");
        }
        lastScore = actualScore;
    }

}

void OverWorldState::render() {
    ++scrollingOffset;
    if (scrollingOffset > gBackgroundTexture.getHeight()){
        scrollingOffset = 0;
    }
    gBackgroundTexture.render(0, scrollingOffset,nullptr, &gScreenRect);
    gBackgroundTexture.render(0, scrollingOffset - gBackgroundTexture.getHeight(),nullptr, &gScreenRect);
    gameManager.renderObstacles();
    player.render();
    gameManager.checkCollision(&player);
    gameScoreTexture.render(gScreenRect.w/2 - gameScoreTexture.getWidth()/2, 200);

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

void GameManager::correctObstaclePosition() {
    cola.correctAllObstacles();
}

ExitState *ExitState::get() {
    return &sExitState;
}

bool ExitState::enter() {
    return true;
}

bool ExitState::exit() {
    return true;
}

void ExitState::handleEvent(SDL_Event &e) {

}

void ExitState::update() {

}

void ExitState::render() {

}
ExitState ExitState::sExitState;
ExitState::ExitState() = default;
