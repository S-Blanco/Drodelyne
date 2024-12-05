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

/*
 * Handles the deck, the player's hand and the preview spot
 // TODO : ADD Mulligan mechanic
*/
class UI {
    public:
        UI(std::array<std::string, 10> PlayerDeck);
        UI();
        void HandleEvent(const SDL_Event& E);
        void Render(SDL_Surface* Surface);
        void DrawCard(Card& spot);

    protected:
        
        static const int mHandSize{4};
        static const int mDeckSize{10};
        static const int mDrawingSize{mDeckSize - mHandSize +1}; // Shuffling when card played so 3 cards in hand, the rest on the pile
        
        
        int mCardWidth;
        int mCardHeight{static_cast<int>(1.44*mCardWidth)};
        int mCardGapX;
        int mCardGapY;
        
        int mCardIndex; // index of the current card to be drawn
        
        bool mClickedOnCard{false};
        
        Card mCardSpots[mHandSize];
        Card mDeckSpot; // TODO : Create a class for deck that shows how many cards remain
        Card mPreviewSpot;

        std::array<std::string, mDeckSize> mPlayer1Deck;
        
        // Contains all the cards to be shuffled when at the bottom of the deck.
        std::array<int, mDrawingSize> mShufflePile{0}; // TODO : Change this name once the Drawing/Shuffling situation in clearer
        std::array<int, mDrawingSize> mGraveyardPile{0};
        
        std::array<int, 10> mDrawingPile{0,1,2,3,4,5,6,7,8,9};


        bool IsWithinBounds(int x, int y, Card& Card);
        




};