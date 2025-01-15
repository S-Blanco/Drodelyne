#include "Orchestra.h"



Orchestra::Orchestra(std::string Background){
    // Load background music
    mBackground = Mix_LoadMUS(Background.c_str());
    #ifdef DEBUG
        if( mBackground == nullptr ){
        std::cout <<  "[Error] Failed to load music! SDL_mixer Error: "  << Mix_GetError() << std::endl;
        }
    #endif
    Mix_VolumeMusic(SoundVolume);
    
    }

Orchestra::~Orchestra(){
    Mix_FreeMusic(mBackground);
}
void Orchestra::PlaySound(Mix_Chunk* sound){ Mix_PlayChannel(-1, sound, 0); }
void Orchestra::PlayMusic(){ Mix_PlayMusic(mBackground, -1); }


void Orchestra::LowerMusic(){
    // TODO: add proper sound volume code, perception is log, not linear 
    SoundVolume -= SDL_MIX_MAXVOLUME / 10;
    if (SoundVolume < 0) SoundVolume = 0;
    Mix_VolumeMusic(SoundVolume);
}
void Orchestra::IncreaseMusic(){
    SoundVolume += SDL_MIX_MAXVOLUME / 10;
    if (SoundVolume > SDL_MIX_MAXVOLUME) SoundVolume = SDL_MIX_MAXVOLUME;
    Mix_VolumeMusic(SoundVolume);
}
    
    
    
    