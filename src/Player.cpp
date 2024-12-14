#include "Player.h"



Player::Player(std::string Name, std::array<std::string, GameSetting::DeckSize>DeckFile,
               std::array<int, GameSetting::DeckSize> DeckID)
    : mName{Name}, mDeckFile{DeckFile}, mDeckID{DeckID}{};

Player::Player(std::array<std::string, GameSetting::DeckSize>DeckFile,
               std::array<int, GameSetting::DeckSize> DeckID)
    : mDeckFile{DeckFile}, mDeckID{DeckID}{};