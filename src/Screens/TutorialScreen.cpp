#include "TutorialScreen.h"

TutorialScreen::TutorialScreen(std::string File[8], std::string Content[8], SDL_Rect DestRect[8])
    : mBackground{File[0], File[1], File[2], File[3], File[4], File[5], File[6], File[7]}, 
    mMessage{{DestRect[0].w, DestRect[0], Content[0]},
             {DestRect[1].w, DestRect[1], Content[1]},
             {DestRect[2].w, DestRect[2], Content[2]},
             {DestRect[3].w, DestRect[3], Content[3]},
             {DestRect[4].w, DestRect[4], Content[4]},
             {DestRect[5].w, DestRect[5], Content[5]},
             {DestRect[6].w, DestRect[6], Content[6]},
             {DestRect[7].w, DestRect[7], Content[7]}}{}

void TutorialScreen::Render(SDL_Surface* Surface){
    mBackground[mSlideIndex].Render(Surface);
    mMessage[mSlideIndex].Render(Surface);
    mPreviousButton.Render(Surface);
    mNextButton.Render(Surface);
}
void TutorialScreen::Update(){
    ;
}
void TutorialScreen::HandleEvent(SDL_Event& E){
    if (E.type = SDL_MOUSEBUTTONDOWN
        && E.button.button == SDL_BUTTON_LEFT){
        
        if (mPreviousButton.IsWithinBounds(E.motion.x, E.motion.y)){
            if (mSlideIndex==0){
                SDL_Event ChangeScene{Events::CHANGE_SCENE};
                ChangeScene.motion.which = START;
                SDL_PushEvent(&ChangeScene);
            }
            else {
                std::cout << std::format("Reduce index") << std::endl;
                --mSlideIndex;
            }
        }else if (mNextButton.IsWithinBounds(E.motion.x, E.motion.y)){
            if (mSlideIndex==7){
                SDL_Event ChangeScene{Events::CHANGE_SCENE};
                ChangeScene.motion.which = START;
                SDL_PushEvent(&ChangeScene);
            }
            else {
                std::cout << std::format("Augment index") << std::endl;
                ++mSlideIndex;
            }

        }
    }
}


