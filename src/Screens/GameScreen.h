#pragma once

#include <SDL.h>

#include "Screen.h"
#include "../UI.h"
#include "../Board.h"

#include "../Deck.h"


class GameScreen : public Screen{
    public:
    GameScreen(SDL_Rect ArenaPos);
    
    UI mGameUI{"Alice", Player1DeckFile, Player1DeckID, "../assets/img/cards/card_p1.png",
              "Bob", Player2DeckFile, Player2DeckID,"../assets/img/cards/card_p2.png"};
    Board mArena;

    void Render(SDL_Surface* Surface);
    void Update();
    void HandleEvent(SDL_Event& E);
};
