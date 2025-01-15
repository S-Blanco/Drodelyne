#include "Events.h"

namespace Events{
    const Uint32 UNIT_PLAYED{SDL_RegisterEvents(1)};
    const Uint32 ILLEGAL_MOVE{SDL_RegisterEvents(1)};
    const Uint32 CARD_SELECTED{SDL_RegisterEvents(1)};
    const Uint32 CARD_UNSELECTED{SDL_RegisterEvents(1)};
    const Uint32 CARD_PLAYED{SDL_RegisterEvents(1)};
    const Uint32 CHANGE_SCENE{SDL_RegisterEvents(1)};


    const Uint32 TO_STARTMENU{SDL_RegisterEvents(1)};
    const Uint32 TO_P1SCREEN{SDL_RegisterEvents(1)};
    const Uint32 TO_P1TRANSITION{SDL_RegisterEvents(1)};
    const Uint32 TO_P2SCREEN{SDL_RegisterEvents(1)};
    const Uint32 TO_P2TRANSITION{SDL_RegisterEvents(1)};

    const Uint32 VOLUME_UP{SDL_RegisterEvents(1)};
    const Uint32 VOLUME_DOWN{SDL_RegisterEvents(1)};

    const Uint32 STOP_ANIMATION{SDL_RegisterEvents(1)};

    const Uint32 RED_PASSED{SDL_RegisterEvents(1)};
    const Uint32 BLUE_PASSED{SDL_RegisterEvents(1)};
    const Uint32 SCORE_GAME{SDL_RegisterEvents(1)};

}
 