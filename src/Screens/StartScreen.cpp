#include "StartScreen.h"

StartScreen::StartScreen(std::string File):mBackground{File}{
    mGameTitle.SetFontSize(150);
}

void StartScreen::Render(SDL_Surface* Surface){
    mBackground.Render(Surface);
    mGameTitle.Render(Surface);
    mStartButton.Render(Surface);
    mTutorialButton.Render(Surface);
    mDeckButton.Render(Surface);
    mSettings.Render(Surface);
}
void StartScreen::Update(){
    ;
}
void StartScreen::HandleEvent(SDL_Event& E){
    if (E.type == SDL_MOUSEBUTTONDOWN
    &&  E.button.button == SDL_BUTTON_LEFT){
        int x = E.button.x;
        int y = E.button.y;
        if (mStartButton.IsWithinBounds(x, y)){
            SDL_Event ChangeScene(Events::CHANGE_SCENE);
            ChangeScene.motion.which = GAME;
            SDL_PushEvent(&ChangeScene);
        }else if (mTutorialButton.IsWithinBounds(x, y)){
            SDL_Event ChangeScene(Events::CHANGE_SCENE);
            ChangeScene.motion.which = TUTORIAL;
            SDL_PushEvent(&ChangeScene);
            
        }else if (mDeckButton.IsWithinBounds(x, y)){
            SDL_Event ChangeScene(Events::CHANGE_SCENE);
            ChangeScene.motion.which = DECK;
            SDL_PushEvent(&ChangeScene);
        }else if (mSettings.IsWithinBounds(x,y)){
            SDL_Event ChangeScene(Events::CHANGE_SCENE);
            ChangeScene.motion.which = SETTINGS;
            SDL_PushEvent(&ChangeScene);
        }
    }
    if (E.type == SDL_KEYDOWN && E.key.keysym.sym == SDLK_SPACE){
        std::cout << std::format("Press space") << std::endl;
        SDL_Event ChangeScene{Events::CHANGE_SCENE};
        SDL_PushEvent(&ChangeScene);
    }
}


