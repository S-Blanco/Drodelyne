#pragma once

#include <array>
#include <string>

#include "Card.h"
#include "Global.h"

class Player{

    public:
        Player()=default;
        Player(std::array<std::string, GameSetting::DeckSize> DeckFile,
               std::array<int, GameSetting::DeckSize> DeckID);

        std::array<std::string, GameSetting::DeckSize> mDeckFile;
        std::array<int, GameSetting::DeckSize> mDeckID;
        
        
        Card mCardSpots[GameSetting::HandSize];
        Card mDeckSpot; // TODO : Create a class for deck that shows how many cards remain
        Card mPreviewSpot;

        int mCardIndex{0}; // index of the current card to be drawn
        int mObligation{0}; // Points to deduct because of card sacrifice
        std::array<int, GameSetting::DrawingSize> mShufflePile{-1,-1,-1,-1,-1,-1,-1}; // Contains all the cards to be shuffled when at the bottom of the deck.
        std::array<int, GameSetting::DrawingSize> mGraveyardPile{-1,-1,-1,-1,-1,-1,-1}; // TODO : Change this name once the Drawing/Shuffling situation in clearer

};