#pragma once

#include <SDL.h>

#include "Screen.h"
#include "../UI.h"
#include "../Board.h"

#include "../Deck.h"


class GameScreen : public Screen{
    public:
    GameScreen(SDL_Rect ArenaPos);
    void Render(SDL_Surface* Surface);
    void Update();
    void HandleEvent(SDL_Event& E);
    
    protected:
    int mCurrentMove{0};
    UI mGameUI{"Alice", Player1DeckFile, Player1DeckID, "../assets/img/cards/card_p1.png",
               "Bob",   Player2DeckFile, Player2DeckID,"../assets/img/cards/card_p2.png"};
    Board mArena;

    
};
