#pragma once

#include "Settings.h"
#include "Events.h"

#ifdef DEBUG
    #include <iostream>
#endif

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class Orchestra{
    public:
        Orchestra(std::string Background, std::string PlaySound, std::string IllegalMoveSound);
        ~Orchestra();
        Orchestra(const Orchestra&) = delete;
        Orchestra& operator=(const Orchestra&) = delete;
        
        void HandleEvent(const SDL_Event& E);
        void PlayMusic();
        void PlaySound(Mix_Chunk* sound);
    private:
        Mix_Music* mBackground{nullptr};
        Mix_Chunk* mPlaySound{nullptr};
        Mix_Chunk* mIllegalSound{nullptr};
        
};