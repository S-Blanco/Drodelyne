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
#include "Screens/GameScreen.h"
#include "Screens/SettingsScreen.h"
#include "Screens/StartScreen.h"
#include "Screens/TransitionScreen.h"
#include "Screens/TutorialScreen.h"
#include "Text.h"
#include "DrawPile.h"

int init_sdl(){
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
    return 0;
}
int main(int argc, char** argv) {

    init_sdl();

    bool RightClickAlreadyPressed{false};
    bool LeftClickAlreadyPressed{false};
    bool Player1HasPassed{false};
    bool Player2HasPassed{false};

    // get screen size to start window
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int EmptyBoardWidth{675};
    int EmptyBoardHeight{675};
    int XStart = (DM.w - 1.3*EmptyBoardWidth)/2;
    int YStart = (DM.h - EmptyBoardHeight)/2;
    Window GameWindow(DM.w, DM.h);
    SDL_WarpMouseInWindow(GameWindow.GetWindow(), DM.w/2, DM.h/5);

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
    std::array<Screen*, 6> ScenesPtr;
    StartScreen Start{"../assets/img/screens/P1_turn.png"};
    GameScreen P1Game{{XStart, YStart, EmptyBoardWidth, EmptyBoardHeight}};
    std::cout << std::format("GameScreen characteristics : {} {}  - {} {}", XStart, YStart, EmptyBoardWidth, EmptyBoardHeight) << std::endl;
    TransitionScreen P1Transition{"../assets/img/screens/P1_turn.png",
                                  "Press space to start your turn",
                                  {DM.w/2 - 250, DM.h/3, 500, 500},
                                  GAME};
    TransitionScreen P2Transition{"../assets/img/screens/P2_turn.png",
                                  "Press space to start your turn",
                                  {DM.w/2 - 250, DM.h/3, 500, 500},
                                  GAME};
    TutorialScreen Tutorial{TutosImg, TutosText, TutosRect};
    SettingsScreen Settings{"../assets/img/screens/P1_turn.png"};

    ScenesPtr[0] = &Start;
    ScenesPtr[1] = &P1Game;
    ScenesPtr[2] = &P1Transition;
    ScenesPtr[3] = &P2Transition;
    ScenesPtr[4] = &Tutorial;
    ScenesPtr[5] = &Settings;
    
    int SceneIndex{0};
    Orchestra Conductor("../assets/sounds/Battle Ready.mp3");
    Conductor.PlayMusic();
    
    SDL_Event Event;
    bool shouldQuit{false};

    int CheckTime{SDL_GetTicks64()};
    int FPS{0};
    int now;
    int last;

    while (!shouldQuit) {

        // Framerate limiter
        if (SDL_GetTicks64() >  (CheckTime + 1000/(Config::TARGET_FPS+1))){ //+1 since it is an upper limit
            CheckTime = SDL_GetTicks64();
            ++FPS;
            now = time(NULL);
            if(now!=last)
                {
                std::cout << "FPS: " << FPS/(now-last) << std::endl;
                last = now;
                FPS = 0;
                }

            // Event processing loop
            while(SDL_PollEvent(&Event)){
                if (Event.type == SDL_QUIT) [[unlikely]]{
                    shouldQuit=true;
                } else if(Event.key.keysym.sym == SDLK_ESCAPE) [[unlikely]]
                {
                    SDL_Event Quit{SDL_QUIT};
                    SDL_PushEvent(&Quit);
                } else if (Event.type == Events::VOLUME_DOWN)
                {
                    Conductor.LowerMusic();
                } else if (Event.type == Events::VOLUME_UP)
                {
                    Conductor.IncreaseMusic();
                }else if (Event.type == Events::CHANGE_SCENE){
                    SceneIndex = Event.motion.which;
                } else if (Event.type == SDL_MOUSEBUTTONDOWN){
                    if (Event.button.button == SDL_BUTTON_LEFT && !LeftClickAlreadyPressed){
                        LeftClickAlreadyPressed = true;
                        ScenesPtr[SceneIndex]->HandleEvent(Event);
                    }else if (Event.button.button == SDL_BUTTON_RIGHT && !RightClickAlreadyPressed){
                        RightClickAlreadyPressed = true;
                        ScenesPtr[SceneIndex]->HandleEvent(Event);
                    }
                }else if (Event.type == SDL_MOUSEBUTTONUP){
                    if (Event.button.button == SDL_BUTTON_LEFT){
                        LeftClickAlreadyPressed = false;
                    }else if (Event.button.button == SDL_BUTTON_RIGHT){
                        RightClickAlreadyPressed = false;
                    }
                } else if(Event.type == Events::BLUE_PASSED){
                    if (Player2HasPassed){
                        // score game
                        std::cout << "Score the game" << std::endl;
                        SDL_Event Quit{SDL_QUIT};
                        SDL_PushEvent(&Quit);
                        
                    } else{
                        Player1HasPassed = true;
                        std::cout << "P1 has passed" << std::endl;
                        ScenesPtr[SceneIndex]->HandleEvent(Event);
                    }
                } else if(Event.type == Events::RED_PASSED){
                    if (Player1HasPassed){
                        // score game
                        std::cout << "Score the game" << std::endl;
                        SDL_Event Quit{SDL_QUIT};
                        SDL_PushEvent(&Quit);
                    } else{
                        Player2HasPassed = true;
                        std::cout << "P2 has passed" << std::endl;
                        ScenesPtr[SceneIndex]->HandleEvent(Event);
                    }
                } else if (Event.type == Events::UNIT_PLAYED){
                    Player1HasPassed = false;
                    Player2HasPassed = false;
                    ScenesPtr[SceneIndex]->HandleEvent(Event);
                } else {
                    ScenesPtr[SceneIndex]->HandleEvent(Event);
                }
            }
            
            // Rendering
            GameWindow.Render();
            ScenesPtr[SceneIndex]->Render(GameWindow.GetSurface());

            GameWindow.Update();

        } else {
            SDL_Delay(2); // millisecond delay for frame limitation
        }
    }
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}