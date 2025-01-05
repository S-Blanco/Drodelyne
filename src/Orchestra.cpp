#include "Orchestra.h"



Orchestra::Orchestra(std::string Background, std::string PlaySound, std::string IllegalMoveSound){
    // Load background music
    mBackground = Mix_LoadMUS(Background.c_str());
    #ifdef DEBUG
        if( mBackground == nullptr ){
        std::cout <<  "[Error] Failed to load music! SDL_mixer Error: "  << Mix_GetError() << std::endl;
        }
    #endif

    // Load "unit played" sound effect
    mPlaySound = Mix_LoadWAV(PlaySound.c_str());
    #ifdef DEBUG
        if(mPlaySound == nullptr){
            std::cout << "[Error] Failed to load \"Unit played\" sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
        }
    #endif

    // Load "illegal move" sound effects
    mIllegalSound = Mix_LoadWAV(IllegalMoveSound.c_str());
    #ifdef DEBUG
        if(mIllegalSound == nullptr){
            std::cout << "[Error] Failed to load \"Illegal move\" sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
        }
    #endif
    Mix_VolumeMusic(SoundVolume);
    
    }

Orchestra::~Orchestra(){
    Mix_FreeMusic(mBackground);
    Mix_FreeChunk(mPlaySound);
    Mix_FreeChunk(mIllegalSound);
}

void Orchestra::HandleEvent(const SDL_Event& E){
    if(E.type == Events::UNIT_PLAYED){ PlaySound(mPlaySound); }
    else if(E.type == Events::ILLEGAL_MOVE){ PlaySound(mIllegalSound); }
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
    
    
    
    