#include "GameScreen.h"

GameScreen::GameScreen(SDL_Rect ArenaPos):mArena{ArenaPos.x, ArenaPos.y, ArenaPos.w , ArenaPos.h}{}
        
void GameScreen::Render(SDL_Surface* Surface){
    mArena.Render(Surface);
    if (mScoringPhase) {
        Score.Render(Surface);
    } else {
        mGameUI.Render(Surface);
    }
    
}

void GameScreen::Update(){;}

void GameScreen::HandleEvent(const SDL_Event& E){
    if (mScoringPhase){
        Score.HandleEvent(E);
    } else{
        if (E.type == Events::UNIT_PLAYED){
            ++mCurrentMove;
            mP1HasPassed = false;
            mP2HasPassed = false;
        } else if (E.type == Events::P1_PASSED){
            ++mCurrentMove;
            mP1HasPassed = true;
            if (mP2HasPassed){
                SDL_Event Score{Events::SCORE_GAME};
                SDL_PushEvent(&Score);
                mScoringPhase = true;
            }
        } else if (E.type == Events::P2_PASSED){
            ++mCurrentMove;
            mP2HasPassed : true;
            if (mP1HasPassed){
                SDL_Event Score{Events::SCORE_GAME};
                SDL_PushEvent(&Score);
                mScoringPhase = true;
            }
        }
        mArena.HandleEvent(E, mCurrentMove);
        mGameUI.HandleEvent(E, mCurrentMove);
    }
}