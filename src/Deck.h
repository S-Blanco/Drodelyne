#pragma once

#include <array>
#include <string>

inline std::array<std::string,10> Player1DeckFile{ // TODO : Use proper storage of deck
        "../assets/img/cards/player1/bigJump.png",
        "../assets/img/cards/player1/bigKnight.png",
        "../assets/img/cards/player1/center.png",
        "../assets/img/cards/player1/corner.png",
        "../assets/img/cards/player1/diagonal.png",
        "../assets/img/cards/player1/free.png",
        "../assets/img/cards/player1/jump.png",
        "../assets/img/cards/player1/knight.png",
        "../assets/img/cards/player1/neighbour.png",
        "../assets/img/cards/player1/side.png"
    };

inline std::array<std::string,10> Player2DeckFile{ // TODO : Use proper storage of deck
        "../assets/img/cards/player2/free.png",
        "../assets/img/cards/player2/free.png",
        "../assets/img/cards/player2/free.png",
        "../assets/img/cards/player2/free.png",
        "../assets/img/cards/player2/free.png",
        "../assets/img/cards/player2/free.png",
        "../assets/img/cards/player2/free.png",
        "../assets/img/cards/player2/free.png",
        "../assets/img/cards/player2/free.png",
        "../assets/img/cards/player2/free.png",
    };

inline std::array<int,10> Player1DeckID{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
inline std::array<int,10> Player2DeckID{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };