 #pragma once

 #include <SDL.h>

namespace Events{
    extern const Uint32 UNIT_PLAYED;     // player clicked on a board's cell to add a unit and succeded
    extern const Uint32 ILLEGAL_MOVE;    // player clicked on a board's cell to add a unit but move is illegal
    extern const Uint32 CARD_SELECTED;   // player selected a card to view the effect on the board
    extern const Uint32 CARD_UNSELECTED; // player unselected a card, back to showing the hand
    extern const Uint32 CARD_PLAYED;     // player confirmed the use of a card to play a move

    extern const Uint32 CHANGE_SCENE;

    extern const Uint32 TO_STARTMENU;
    extern const Uint32 TO_P1SCREEN;
    extern const Uint32 TO_P1TRANSITION;
    extern const Uint32 TO_P2SCREEN;
    extern const Uint32 TO_P2TRANSITION;

    extern const Uint32 VOLUME_UP;
    extern const Uint32 VOLUME_DOWN;

    extern const Uint32 STOP_ANIMATION;

    extern const Uint32 P2_PASSED;
    extern const Uint32 P1_PASSED;
    extern const Uint32 SCORE_GAME;
}
 