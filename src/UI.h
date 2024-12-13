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

/*
 * Handles the deck, the player's hand and the preview spot
 // TODO : ADD Mulligan mechanic
*/
class UI {
    public:
        UI()=default;
        UI(std::array<std::string, 10> Player1DeckFile, std::array<int, 10> Player1DeckID,
           std::array<std::string, 10> Player2DeckFile, std::array<int, 10> Player2DeckID);
        
        void Render(SDL_Surface* Surface);
        void DrawCard(Card& spot);
        void HandleEvent(const SDL_Event& E);
    
    protected:
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
        // std::array<std::string, mDeckSize> mP1DeckFile;
        // std::array<int, mDeckSize> mP1DeckID;
        // int mP1Obligation{0}; // Points to deduct because of card sacrifice
        // int mP1CardIndex; // index of the current card to be drawn
        // Card mP1CardSpots[mHandSize];
        // Card mP1DeckSpot; // TODO : Create a class for deck that shows how many cards remain
        // Card mP1PreviewSpot;
        // std::array<int, mDrawingSize> mP1ShufflePile{-1,-1,-1,-1,-1,-1,-1}; // Contains all the cards to be shuffled when at the bottom of the deck.
        // std::array<int, mDrawingSize> mP1GraveyardPile{-1,-1,-1,-1,-1,-1,-1}; // TODO : Change this name once the Drawing/Shuffling situation in clearer
        
        
        // std::array<std::string, mDeckSize> mP2DeckFile;
        // std::array<int, mDeckSize> mP2DeckID;
        // int mP2Obligation{0}; // Points to deduct because of card sacrifice 
        // int mP2CardIndex; // index of the current card to be drawn
        // Card mP2CardSpots[mHandSize];
        // Card mP2DeckSpot; // TODO : Create a class for deck that shows how many cards remain
        // Card mP2PreviewSpot;
        // std::array<int, mDrawingSize> mP2ShufflePile{-1,-1,-1,-1,-1,-1,-1}; // Contains all the cards to be shuffled when at the bottom of the deck.
        // std::array<int, mDrawingSize> mP2GraveyardPile{-1,-1,-1,-1,-1,-1,-1}; // TODO : Change this name once the Drawing/Shuffling situation in clearer
        
        
        
        // void SetupHand(std::array<std::string, mDeckSize>& PlayerDeckFile,
        //                    std::array<int, mDeckSize>& PlayerDeckID,
        //                    std::array<int, mDrawingSize>& ShufflePile,
        //                    int& CardIndex, Card DeckSpot, Card CardSpots[4], Card PreviewSpot); // TODO : once stabilizedn create a player struct and pass it here
        
        void SetupHand(Player* Player);
        void SwapGraveyardAndShuffle(Player* Player);
        bool IsWithinBounds(int x, int y, Card& Card);
        




};