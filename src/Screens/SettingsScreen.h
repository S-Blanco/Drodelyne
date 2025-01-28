#pragma once

#include <format>


#include "Screen.h"
#include "../Button.h"
#include "../Events.h"
#include "../Global.h"
#include "../Image.h"
#include "../Layout.h"
#include "../Scene.h"

class SettingsScreen : public Screen{
    public:
    SettingsScreen(std::string File);
    Image mBackground;
    Text mSoundText{mVolumeBarWidth, {3*(Layout::ScreenWidth - mVolumeBarWidth)/7, 175, mVolumeBarWidth, 80}, "Volume"};
    int mVolume{4};
    const int mNbrVolumeStep{8};
    const int mVolumeBarWidth{300};
    Rectangle mVolumeBarBackground{(Layout::ScreenWidth - mVolumeBarWidth)/2, 250,
                         mVolumeBarWidth, 80,
                         {25,90,170}};

    Rectangle mVolumeBar{(Layout::ScreenWidth - mVolumeBarWidth)/2, 250,
                         mVolume * mVolumeBarWidth / mNbrVolumeStep, 80,
                         {40,150,255}};

    TextButton mSoundDownButton{"-", {(Layout::ScreenWidth-50)/3,250,50,80},   Colors::DarkBlueButton};
    TextButton mSoundUpButton{"+",   {2*(Layout::ScreenWidth-50)/3,250,50,80}, Colors::DarkBlueButton};
    TextButton mBackButton{"Back",   {(Layout::ScreenWidth-250)/2,500,250,80}, Colors::BlueButton};

    void Render(SDL_Surface* Surface);
    void Update();
    void HandleEvent(const SDL_Event& E);
};