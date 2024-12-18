#include "SettingsScreen.h"

SettingsScreen::SettingsScreen(std::string File):mBackground{File}{}

void SettingsScreen::Render(SDL_Surface* Surface){
    mBackground.Render(Surface);
    mStartButton.Render(Surface);
    mQuitButton.Render(Surface);
}
void SettingsScreen::Update(){
    ;
}
void SettingsScreen::HandleEvent(SDL_Event& E){
    if (E.type == SDL_KEYDOWN && E.key.keysym.sym == SDLK_SPACE){
        std::cout << std::format("Press space") << std::endl;
        SDL_Event ChangeScene{Events::CHANGE_SCENE};
        SDL_PushEvent(&ChangeScene);
    }
}


