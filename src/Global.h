#pragma once

#include <SDL.h>

namespace Config{
    const int TARGET_FPS = 30;
    const int FRAME_DELAY = 1000 / TARGET_FPS;
}

namespace Colors{
    // https://paletton.com/#uid=53y0k0kMHXunrVSudX5WGF0UArj
    SDL_Color Primary[5]{{76,166,241},{29,147,244},{7,137,245},{2,106,193},{2,78,140}};
    SDL_Color Secondary_1[5]{{86,117,242},{42,82,245},{13,59,246},{3,42,199},{4,32,148}};
    SDL_Color Secondary_2[5]{{64,240,216},{14,243,212},{0,245,211},{0,190,164},{0,137,118}};

}

