#include "StartScreen.h"

StartScreen::StartScreen(std::string File):mBackground{File}{}

void StartScreen::Render(SDL_Surface* Surface){
    mBackground.Render(Surface);
    mStartButton.Render(Surface);
    mTutorialButton.Render(Surface);
    mDeckButton.Render(Surface);
}
void StartScreen::Update(){
    ;
}
void StartScreen::HandleEvent(SDL_Event& E){
    if (E.type == SDL_MOUSEBUTTONDOWN
    &&  E.button.button == SDL_BUTTON_LEFT){
        int x = E.button.x;
        int y = E.button.y;
        if (mStartButton.IsWithinBonds(x, y)){
            SDL_Event ChangeScene(Events::CHANGE_SCENE);
            ChangeScene.motion.which = P1_GAME;
            SDL_PushEvent(&ChangeScene);
        }else if (mTutorialButton.IsWithinBonds(x, y)){
            SDL_Event ChangeScene(Events::CHANGE_SCENE);
            ChangeScene.motion.which = TUTORIAL;
            SDL_PushEvent(&ChangeScene);
            
        }else if (mDeckButton.IsWithinBonds(x, y)){
            SDL_Event ChangeScene(Events::CHANGE_SCENE);
            ChangeScene.motion.which = DECK;
            SDL_PushEvent(&ChangeScene);
        }
    }
    if (E.type == SDL_KEYDOWN && E.key.keysym.sym == SDLK_SPACE){
        std::cout << std::format("Press space") << std::endl;
        SDL_Event ChangeScene{Events::CHANGE_SCENE};
        SDL_PushEvent(&ChangeScene);
    }
}

