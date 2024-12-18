#include "TutorialScreen.h"

TutorialScreen::TutorialScreen(std::string File, std::string Content, SDL_Rect DestRect)
    : mBackground{File}, mMessage{DestRect.w, DestRect, Content}{}

void TutorialScreen::Render(SDL_Surface* Surface){
    mBackground.Render(Surface);
    mMessage.Render(Surface);
    mPreviousButton.Render(Surface);
    mNextButton.Render(Surface);
}
void TutorialScreen::Update(){
    ;
}
void TutorialScreen::HandleEvent(SDL_Event& E){
    if (E.type == SDL_KEYDOWN && E.key.keysym.sym == SDLK_SPACE){
        SDL_Event ChangeScene{Events::CHANGE_SCENE};
        ChangeScene.motion.which = START;
        SDL_PushEvent(&ChangeScene);
    }
}


