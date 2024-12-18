#include "TransitionScreen.h"

TransitionScreen::TransitionScreen(std::string File, std::string Content, SDL_Rect DestRect, Scenes TransitionTo)
    : mBackground{File}, mMessage{DestRect.w, DestRect, Content}, mTransitionTo{TransitionTo}{}

void TransitionScreen::Render(SDL_Surface* Surface){
    mBackground.Render(Surface);
    mMessage.Render(Surface);
}
void TransitionScreen::Update(){
    ;
}
void TransitionScreen::HandleEvent(SDL_Event& E){
    if (E.type == SDL_KEYDOWN && E.key.keysym.sym == SDLK_SPACE){
        SDL_Event ChangeScene{Events::CHANGE_SCENE};
        ChangeScene.motion.which = mTransitionTo;
        SDL_PushEvent(&ChangeScene);
    }
}


