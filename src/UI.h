#pragma once

#include <SDL.h>
#include <array>
#include <algorithm>
#include <chrono>
#include <random>

#include "Settings.h"
#ifdef DEBUG
    #include <format>
#endif


#include "Card.h"
#include "Events.h"
#include "Player.h"
#include "Scene.h"
#include "Button.h"
#include "Text.h"

/*
 * Handles the deck, the player's hand and the preview spot
 // TODO : ADD Mulligan mechanic
*/
class UI {
    public:
        UI()=default;
        UI(std::string Name1, std::array<std::string, 10> Player1DeckFile, std::array<int, 10> Player1DeckID, std::string P1DrawFile,
           std::string Name2, std::array<std::string, 10> Player2DeckFile, std::array<int, 10> Player2DeckID, std::string P2DrawFile);
        
        void Render(SDL_Surface* Surface);
        void DrawCard(Card& spot);
        void HandleEvent(const SDL_Event& E);
    
        Text mWrite;

    protected:

        // Button mDiscard {950, 80, 180, 80, {217,150,0,255}};
        // Button mCancel {1150, 80, 180, 80, {177,122,0,255}};
        int mCurrentMove{0};
        Player* mCurrentPlayer{nullptr};
        void Render(SDL_Surface* Surface, Player* Player);
        void DrawCard(Card& spot, Player* Player);
        void HandleEvent(const SDL_Event& E, Player* Player);
        static const int mHandSize{4};
        static const int mDeckSize{10};
        static const int mDrawingSize{mDeckSize - mHandSize +1}; // Shuffling when card played so 3 cards in hand, the rest on the pile
        
        
        int mCardWidth;
        int mCardHeight{static_cast<int>(1.44*mCardWidth)};
        int mCardGapX;
        int mCardGapY;
        
        bool mClickedOnHand{false};
        
        Player mPlayers[2];

        void SetupHand(Player* Player);
        void SwapGraveyardAndShuffle(Player* Player);

};