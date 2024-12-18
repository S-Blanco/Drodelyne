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
#include "Scene.h"
#include "Screens/DeckScreen.h"
#include "Screens/GameScreen.h"
#include "Screens/SettingsScreen.h"
#include "Screens/StartScreen.h"
#include "Screens/TransitionScreen.h"
#include "Screens/TutorialScreen.h"
#include "Text.h"
#include "DrawPile.h"


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


    // get screen size to start window
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int EmptyBoardWidth{675};
    int EmptyBoardHeight{675};
    int XStart = (DM.w - 1.3*EmptyBoardWidth)/2;
    int YStart = (DM.h - EmptyBoardHeight)/2;
    Window GameWindow(DM.w, DM.h);

    std::array<Screen*, 8> ScenesPtr;
    StartScreen Start{"../assets/img/screens/P1_turn.png"};
    GameScreen P1Game{{XStart, YStart, EmptyBoardWidth, EmptyBoardHeight}};
    std::cout << std::format("GameScreen characteristics : {} {}  - {} {}", XStart, YStart, EmptyBoardWidth, EmptyBoardHeight) << std::endl;
    TransitionScreen P1Transition{"../assets/img/screens/P2_turn.png", "Press space to continue", {100,100,500,500}, P2_GAME};
    GameScreen P2Game{{XStart, YStart, EmptyBoardWidth, EmptyBoardHeight}};
    TransitionScreen P2Transition{"../assets/img/screens/P1_turn.png", "Press space to continue", {100,100,500,500}, P1_GAME};
    TutorialScreen Tutorial{"../assets/img/screens/tutorial.png", "Learn how to play the game", {500,400,866,300}};
    SettingsScreen Settings{"../assets/img/screens/P1_turn.png"};
    DeckScreen Deck{"../assets/img/screens/deck.jpg", "Deck building screen",{0,0,1366, 768}};

    ScenesPtr[0] = &Start;
    ScenesPtr[1] = &P1Game;
    ScenesPtr[2] = &P1Transition;
    ScenesPtr[3] = &P2Game;
    ScenesPtr[4] = &P2Transition;
    ScenesPtr[5] = &Tutorial;
    ScenesPtr[6] = &Settings;
    ScenesPtr[7] = &Deck;
    
    int SceneIndex{0};

    Orchestra Conductor("../assets/sounds/abackground.wav",
                        "../assets/sounds/validPlay.wav",
                        "../assets/sounds/invalidPlay.wav");
    Conductor.PlayMusic();
    
    SDL_Event Event;
    bool shouldQuit{false};

    std::vector<int> Triggers{SDLK_ESCAPE, SDLK_SPACE, SDLK_KP_ENTER};
    std::vector<int> Links{START, P1_GAME, P1_TRANSITION};

    while (!shouldQuit) {
        Uint32 frameStart = SDL_GetTicks();

        // Event processing loop
        while(SDL_PollEvent(&Event)){
            if (Event.type == SDL_QUIT) [[unlikely]]{
                shouldQuit=true;
            }
            else if(Event.key.keysym.sym == SDLK_ESCAPE) [[unlikely]]{
                    SDL_Event Quit{SDL_QUIT};
                    SDL_PushEvent(&Quit);
                }
            else if (Event.type == Events::CHANGE_SCENE){
                SceneIndex = Event.motion.which;
            }
            ScenesPtr[SceneIndex]->HandleEvent(Event);
        }
        
        // Rendering
        GameWindow.Render();
        ScenesPtr[SceneIndex]->Render(GameWindow.GetSurface());
        GameWindow.Update();
    }
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}