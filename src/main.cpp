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

    std::string TutosImg[8] = {"../assets/img/screens/tuto1_1.png", 
                             "../assets/img/screens/tuto1_2.png", 
                             "../assets/img/screens/tuto1_3.png", 
                             "../assets/img/screens/tuto2_1.png", 
                             "../assets/img/screens/tuto2_2.png",
                             "../assets/img/screens/tuto3_0.png", 
                             "../assets/img/screens/tuto3_1.png", 
                             "../assets/img/screens/tuto3_2.png"};
    
    std::string TutosText[8] = {"This is your debt to pay at the end of the game", 
                                "This is your hand, chose a card to play your unit on a square",
                                "This is your draw pile, You draw a card each time you play and shuffle the card played when your draw pile is empty",
                                "Click on the card shows where you can place your unit",
                                "Click on the square to place the unit in this spot",
                                "The game ends when the borders are established between the 2 players",
                                "Any square surrounded by blue units give 1 point to blue",
                                "Any square surrounded by red units give 1 point to red",
                                };
    SDL_Rect TutosRect[8] = {{300,100,600,600},
                             {300,400,600,600},
                             {300,300,650,600},
                             {450,475,550,300},
                             {450,475,600,300},
                             {950,200,350,600},
                             {950,200,350,300},
                             {950,200,350,300}};
    std::array<Screen*, 7> ScenesPtr;
    StartScreen Start{"../assets/img/screens/P1_turn.png"};
    GameScreen P1Game{{XStart, YStart, EmptyBoardWidth, EmptyBoardHeight}};
    std::cout << std::format("GameScreen characteristics : {} {}  - {} {}", XStart, YStart, EmptyBoardWidth, EmptyBoardHeight) << std::endl;
    TransitionScreen P1Transition{"../assets/img/screens/P2_turn.png", "Press space to continue", {100,100,500,500}, GAME};
    TransitionScreen P2Transition{"../assets/img/screens/P1_turn.png", "Press space to continue", {100,100,500,500}, GAME};
    TutorialScreen Tutorial{TutosImg, TutosText, TutosRect};
    SettingsScreen Settings{"../assets/img/screens/P1_turn.png"};
    DeckScreen Deck{"../assets/img/screens/deck.jpg", "Deck building screen",{0,0,1366, 768}};

    ScenesPtr[0] = &Start;
    ScenesPtr[1] = &P1Game;
    ScenesPtr[2] = &P1Transition;
    ScenesPtr[3] = &P2Transition;
    ScenesPtr[4] = &Tutorial;
    ScenesPtr[5] = &Settings;
    ScenesPtr[6] = &Deck;
    
    int SceneIndex{0};

    Orchestra Conductor("../assets/sounds/background.wav",
                        "../assets/sounds/validPlay.wav",
                        "../assets/sounds/invalidPlay.wav");
    Conductor.PlayMusic();
    int SoundVolume{SDL_MIX_MAXVOLUME/2};
    Mix_VolumeMusic(SoundVolume);
    
    SDL_Event Event;
    bool shouldQuit{false};

    std::vector<int> Triggers{SDLK_ESCAPE, SDLK_SPACE, SDLK_KP_ENTER};
    std::vector<int> Links{START, GAME, P1_TRANSITION};

    while (!shouldQuit) {
        Uint32 frameStart = SDL_GetTicks();

        // Event processing loop
        while(SDL_PollEvent(&Event)){
            if (Event.type == SDL_QUIT) [[unlikely]]{
                shouldQuit=true;
            }else if (Event.type == Events::VOLUME_DOWN)
            {
                SoundVolume -= SDL_MIX_MAXVOLUME / 10;
                if (SoundVolume < 0) SoundVolume = 0;
                Mix_VolumeMusic(SoundVolume);
    
            }else if (Event.type == Events::VOLUME_UP)
            {
                SoundVolume += SDL_MIX_MAXVOLUME / 10;
                if (SoundVolume > SDL_MIX_MAXVOLUME) SoundVolume = SDL_MIX_MAXVOLUME;
                Mix_VolumeMusic(SoundVolume);
    
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