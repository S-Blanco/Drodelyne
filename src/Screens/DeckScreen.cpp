#include "DeckScreen.h"

DeckScreen::DeckScreen(std::string File, std::string Content, SDL_Rect DestRect)
    : mBackground{File}, mMessage{DestRect.w, DestRect, Content}{}

void DeckScreen::Render(SDL_Surface* Surface){
    mBackground.Render(Surface);
    mMessage.Render(Surface);
}
void DeckScreen::Update(){
    ;
}
void DeckScreen::HandleEvent(SDL_Event& E){
    if (E.type == SDL_KEYDOWN && E.key.keysym.sym == SDLK_SPACE){
        SDL_Event ChangeScene{Events::CHANGE_SCENE};
        SDL_PushEvent(&ChangeScene);
    }
}


