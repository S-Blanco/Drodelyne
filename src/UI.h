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
        UI(std::array<std::string, 10> PlayerDeckFile, std::array<int, 10> PlayerDeckID);
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
        
        bool mClickedOnHand{false};
        
        Card mCardSpots[mHandSize];
        Card mDeckSpot; // TODO : Create a class for deck that shows how many cards remain
        Card mPreviewSpot;

        std::array<std::string, mDeckSize> mPlayer1DeckFile;
        std::array<int, mDeckSize> mPlayer1DeckID;
        
        // Contains all the cards to be shuffled when at the bottom of the deck.
        // TODO : Change this name once the Drawing/Shuffling situation in clearer
        std::array<int, mDrawingSize> mShufflePile{-1,-1,-1,-1,-1,-1,-1}; 
        std::array<int, mDrawingSize> mGraveyardPile{-1,-1,-1,-1,-1,-1,-1};
        
        
        void SwapGraveyardAndShuffle();

        bool IsWithinBounds(int x, int y, Card& Card);
        




};