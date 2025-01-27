#pragma once

#include <SDL.h>

#include "Screen.h"
#include "../UI.h"
#include "../Board.h"
#include "../Scoring.h"

#include "../Deck.h"


class GameScreen : public Screen{
    public:
    GameScreen(SDL_Rect ArenaPos);
    void Render(SDL_Surface* Surface);
    void Update();
    void HandleEvent(const SDL_Event& E);
    
    Board mArena;
    protected:
    int mCurrentMove{0};
    bool mP1HasPassed{false};
    bool mP2HasPassed{false};
    bool mScoringPhase{false};
    
    Scoring Score;
    UI mGameUI{"Player 1", Player1DeckFile, Player1DeckID, "../assets/img/cards/card_p1.png",
               "Player 2", Player2DeckFile, Player2DeckID, "../assets/img/cards/card_p2.png"};
    

    
};
