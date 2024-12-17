#include "Player.h"



Player::Player(std::string Name,
               std::array<std::string, GameSetting::DeckSize> DeckFile,
               std::array<int, GameSetting::DeckSize> DeckID,
               std::string DrawingPileFile)
    : mName{Name}, mDeckFile{DeckFile}, mDeckID{DeckID}, mDeckSpot{DrawingPileFile, GameSetting::DrawingSize}{};

Player::Player(std::array<std::string, GameSetting::DeckSize>DeckFile,
               std::array<int, GameSetting::DeckSize> DeckID)
    : mDeckFile{DeckFile}, mDeckID{DeckID}{};