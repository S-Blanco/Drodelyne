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
#include "Text.h"

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

    
    int SceneIndex{1};

    Image StartScreen{"../assets/img/screens/start.png"};
    Image Player1Waiting{"../assets/img/screens/P1_turn.png"};
    Image Player2Waiting{"../assets/img/screens/P2_turn.png"};

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

    
    #include "Deck.h"

    // Game CurrentGame;
    UI GameUI("Alice", Player1DeckFile, Player1DeckID,
              "Bob", Player2DeckFile, Player2DeckID);
    Board Arena{XStart, YStart, EmptyBoardWidth, EmptyBoardHeight};
    
    SDL_Event Event;
    bool shouldQuit{false};

    std::vector<int> Triggers{SDLK_ESCAPE, SDLK_SPACE, SDLK_KP_ENTER};
    std::vector<int> Links{START, P1_GAME, P1_TRANSITION};

    while (!shouldQuit) {
        Uint32 frameStart = SDL_GetTicks();

        while(SDL_PollEvent(&Event)){
            if (Event.type == SDL_QUIT) [[unlikely]]{ shouldQuit=true; }
            if (Event.type == Events::CHANGE_SCENE){
                std::cout << std::format("Change the scene index") << std::endl;
                SceneIndex = Event.motion.which;
                }

            if(Event.key.keysym.sym == SDLK_ESCAPE){
                    SDL_Event Quit{SDL_QUIT};
                    SDL_PushEvent(&Quit);
                }
            
            // Dispatch events only to current scene
            if (SceneIndex == START){
                
                for (int i=0; i<Triggers.size(); ++i){
                    if (Event.key.keysym.sym == Triggers[i]){
                        std::cout << std::format("Must change to scene: {}", Links[i]) << std::endl;
                        SDL_Event ChangeScene{Events::CHANGE_SCENE};
                        ChangeScene.motion.which = Links[i];
                        SDL_PushEvent(&ChangeScene);
                    }
                }
                
            } else if (SceneIndex == P1_GAME){
                if (Event.type == Events::UNIT_PLAYED){
                    Conductor.HandleEvent(Event);   // Play sound
                    Arena.HandleEvent(Event);       // Change board state
                    GameUI.HandleEvent(Event);      // Draw new card
                }else{
                    GameUI.HandleEvent(Event);
                    Arena.HandleEvent(Event);
                }
            } else if (SceneIndex == P1_TRANSITION){
                if (Event.key.keysym.sym == SDLK_SPACE){
                        SDL_Event ChangeScene{Events::CHANGE_SCENE};
                        ChangeScene.motion.which = P2_GAME;
                        SDL_PushEvent(&ChangeScene);
                }

            } else if (SceneIndex == P2_GAME){
                if (Event.type == Events::UNIT_PLAYED){
                    Conductor.HandleEvent(Event);   // Play sound
                    Arena.HandleEvent(Event);       // Change board state
                    GameUI.HandleEvent(Event);      // Draw new card
                }else{
                    GameUI.HandleEvent(Event);
                    Arena.HandleEvent(Event);
                }

            } else if (SceneIndex == P2_TRANSITION){
                if (Event.key.keysym.sym == SDLK_SPACE){
                        SDL_Event ChangeScene{Events::CHANGE_SCENE};
                        ChangeScene.motion.which = P2_GAME;
                        SDL_PushEvent(&ChangeScene);
                }

            }
        }
        Arena.CheckHover(); // useless now?


        GameWindow.Render();
        // Dispatch events only to current scene
        if (SceneIndex == START){
            StartScreen.Render(GameWindow.GetSurface());
        } else if (SceneIndex == P1_GAME){
            GameUI.Render(GameWindow.GetSurface());
            Arena.Render(GameWindow.GetSurface());


        } else if (SceneIndex == P1_TRANSITION){
            Player1Waiting.Render(GameWindow.GetSurface());
            Arena.Render(GameWindow.GetSurface());
        } else if (SceneIndex == P2_GAME){
            GameUI.Render(GameWindow.GetSurface());
            Arena.Render(GameWindow.GetSurface());
        } else if (SceneIndex == P2_TRANSITION){
            Player2Waiting.Render(GameWindow.GetSurface());
            Arena.Render(GameWindow.GetSurface());
        }
        GameWindow.Update();
    }
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}