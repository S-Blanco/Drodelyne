#include "Events.h"

namespace Events{
    const Uint32 HOVER_EVENT{SDL_RegisterEvents(1)};
    const Uint32 UNIT_PLAYED{SDL_RegisterEvents(1)};
    const Uint32 ILLEGAL_MOVE{SDL_RegisterEvents(1)};
    const Uint32 CARD_SELECTED{SDL_RegisterEvents(1)};
    const Uint32 CARD_UNSELECTED{SDL_RegisterEvents(1)};
    const Uint32 CARD_PLAYED{SDL_RegisterEvents(1)};
    
}
 