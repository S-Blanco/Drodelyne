#include "DeckScreen.h"

DeckScreen::DeckScreen(std::string File, std::string Content, SDL_Rect DestRect)
    : mBackground{File}, mMessage{DestRect.w, DestRect, Content}, mBackButton{"Back", {50,700, 200, 60}}{}


void DeckScreen::Render(SDL_Surface* Surface){
    mBackground.Render(Surface);
    mMessage.Render(Surface);
    mBackButton.Render(Surface);
}
void DeckScreen::Update(){
    ;
}
void DeckScreen::HandleEvent(SDL_Event& E){
    if (E.type == SDL_MOUSEBUTTONDOWN){
        if (mBackButton.IsWithinBounds(E.motion.x, E.motion.y)){
            SDL_Event ChangeScene{Events::CHANGE_SCENE};
            ChangeScene.motion.which = START;
            SDL_PushEvent(&ChangeScene);
        }
    }
}


