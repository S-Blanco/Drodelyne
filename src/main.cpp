// TODO : Replace cursor with something more immersive
// 1. Because it will look cooler.
// 2. Because it seems that the coordinates given is the center of the arrow and not the tip
//    which can cause a lot of missclick.

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <array>
#include <vector>
#include <algorithm> // for the random shuffle
//#include <random> // for the random seed

#ifdef DEBUG
    #include <iostream>
    #include <format>
#endif

#include "Settings.h"
#include "Events.h"
#include "Global.h"
#include "Window.h"
#include "Image.h"
#include "UI.h"
#include "Unit.h"
#include "Board.h"
#include "Orchestra.h"



int main(int argc, char** argv) {

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS)<0){
        std::cout << "[Error] initializing SDL: " << SDL_GetError();
        return -1;
    }
    if(!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & (IMG_INIT_JPG | IMG_INIT_PNG))){
        std::cout << "[Error] initializing SDL_image: " << IMG_GetError();
        return -1;
    }
    if(TTF_Init()<0){
        std::cout << "[Error] initializing SDL_ttf: " << TTF_GetError();
        return -1;
    };
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        std::cout << "[Error] initializing SDL_mixer: " << Mix_GetError();
        return -1;
    }


    Orchestra Conductor("../assets/sounds/background.wav",
                        "../assets/sounds/validPlay.wav",
                        "../assets/sounds/invalidPlay.wav");
    Conductor.PlayMusic();
    
    // get screen size to start window
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int EmptyBoardWidth{675};
    int EmptyBoardHeight{675};
    int XStart = (DM.w - 1.3*EmptyBoardWidth)/2;
    int YStart = (DM.h - EmptyBoardHeight)/2;
    Window GameWindow(DM.w, DM.h);

    std::array<std::string,10> PlayerDeck{ // TODO : Use proper storage of deck
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

    UI GameUI(PlayerDeck);
    Board Arena{XStart, YStart, EmptyBoardWidth, EmptyBoardHeight};
    
    SDL_Event Event;
    bool shouldQuit{false};

    #ifdef DEBUG
        int i{0};
    #endif

    while (!shouldQuit) {
        #ifdef DEBUG
            ++i;
        #endif
        Uint32 frameStart = SDL_GetTicks();
        

        while(SDL_PollEvent(&Event)){
            if (Event.type == SDL_QUIT) [[unlikely]]{ shouldQuit=true; }
            if (Event.type == Events::UNIT_PLAYED){
                Conductor.HandleEvent(Event);   // Play sound
                Arena.HandleEvent(Event);       // Change board state
            }else{
                GameUI.HandleEvent(Event);
                Arena.HandleEvent(Event);
            }
        }
        Arena.CheckHover();


        GameWindow.Render();
        GameUI.Render(GameWindow.GetSurface());
        Arena.Render(GameWindow.GetSurface());
        GameWindow.Update();
    }
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}