#pragma once

#include <array>
#include <string>

#include "Card.h"
#include "DrawPile.h"
#include "Global.h"

class Player{

    public:
        Player()=default;
        Player(std::string Name,
               std::array<std::string, GameSetting::DeckSize> DeckFile,
               std::array<int, GameSetting::DeckSize> DeckID,
               std::string DrawingPileFile = "../assets/img/cards/card.png");
        Player(std::array<std::string, GameSetting::DeckSize> DeckFile,
               std::array<int, GameSetting::DeckSize> DeckID);

        std::array<std::string, GameSetting::DeckSize> mDeckFile;
        std::array<int, GameSetting::DeckSize> mDeckID;
        std::string mDrawingPileFile;
        
        std::string mName;
        Card mCardSpots[GameSetting::HandSize];
        DrawPile mDeckSpot;
        Card mPreviewSpot;

        int mCardIndex{0}; // index of the current card to be drawn
        int mObligation{0}; // Points to deduct because of card sacrifice
        std::array<int, GameSetting::DrawingSize> mShufflePile{-1,-1,-1,-1,-1,-1,-1}; // Contains all the cards to be shuffled when at the bottom of the deck.
        std::array<int, GameSetting::DrawingSize> mGraveyardPile{-1,-1,-1,-1,-1,-1,-1}; // TODO : Change this name once the Drawing/Shuffling situation in clearer

};