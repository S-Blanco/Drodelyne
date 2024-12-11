#include "Player.h"


Player::Player(std::array<std::string, GameSetting::DeckSize>DeckFile,
               std::array<int, GameSetting::DeckSize> DeckID)
    : mDeckFile{DeckFile}, mDeckID{DeckID}{};