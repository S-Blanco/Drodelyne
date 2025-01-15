#include "GameScreen.h"

GameScreen::GameScreen(SDL_Rect ArenaPos):mArena{ArenaPos.x, ArenaPos.y, ArenaPos.w , ArenaPos.h}{}
        
void GameScreen::Render(SDL_Surface* Surface){
    mArena.Render(Surface);
    mGameUI.Render(Surface);
}

void GameScreen::Update(){;}

void GameScreen::HandleEvent(SDL_Event& E){
    if (E.type == Events::TURN_ENDED) { ++mCurrentMove; }
    mArena.HandleEvent(E, mCurrentMove);
    mGameUI.HandleEvent(E, mCurrentMove);
}