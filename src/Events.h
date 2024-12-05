 #pragma once

 #include <SDL.h>

namespace Events{
    extern const Uint32 HOVER_EVENT; // mouse hover over a board's cell
    extern const Uint32 UNIT_PLAYED; // player clicked on a board's cell to add a unit and succeded
    extern const Uint32 ILLEGAL_MOVE; // player clicked on a board's cell to add a unit but move is illegal
    extern const Uint32 CARD_PLAYED; // player confirmed the use of a card to play a move
}
 