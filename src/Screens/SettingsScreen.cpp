#include "SettingsScreen.h"

SettingsScreen::SettingsScreen(std::string File):mBackground{File}{}

void SettingsScreen::Render(SDL_Surface* Surface){
    mBackground.Render(Surface);
    mSoundUpButton.Render(Surface);
    mSoundDownButton.Render(Surface);
    mBackButton.Render(Surface);
    mVolumeBarBackground.Render(Surface);
    mVolumeBar.Render(Surface);
    mSoundText.Render(Surface);
}
void SettingsScreen::Update(){
    ;
}
void SettingsScreen::HandleEvent(SDL_Event& E){
    if (E.type == SDL_MOUSEBUTTONDOWN && E.button.button == SDL_BUTTON_LEFT){
        if (mSoundUpButton.IsWithinBounds(E.motion.x, E.motion.y)){
            if (mVolume < 10){
                ++mVolume;
            }
            mVolumeBar.SetWidth(mVolume * mVolumeBarWidth / mNbrVolumeStep);
            SDL_Event ChangeScene{Events::VOLUME_UP};
            SDL_PushEvent(&ChangeScene);

        } else if (mSoundDownButton.IsWithinBounds(E.motion.x, E.motion.y)){
             if (mVolume > 0){
                --mVolume;
            }
            mVolumeBar.SetWidth(mVolume * mVolumeBarWidth / mNbrVolumeStep);
            SDL_Event ChangeScene{Events::VOLUME_DOWN};
            SDL_PushEvent(&ChangeScene);

        } else if (mBackButton.IsWithinBounds(E.motion.x, E.motion.y)){
            SDL_Event ChangeScene{Events::CHANGE_SCENE};
            ChangeScene.motion.which = START;
            SDL_PushEvent(&ChangeScene);
        }
    }
}


