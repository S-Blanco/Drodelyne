#pragma once

#include "Button.h"
#include "Global.h"
#include "Layout.h"
#include "DrawRectangle.h"
#include <vector>

class Scoring {
    public:
	Scoring()=default;
    void Render(SDL_Surface* Surface);
    void HandleEvent(const SDL_Event& Event);

    protected:
	int idx{0};

	int mBlueScore{0};
	int mRedScore{0};

    bool mBlueIsActive{true};
    SDL_Color mBlueColor[2]{Colors::DarkBlueButton, Colors::BlueButton};
    SDL_Color mRedColor[2]{Colors::DarkRedButton, Colors::RedButton};
	Text mBlueScoreText{200, {0,0,200, 200},"Blue Score :\n -"};
	Text mRedScoreText{200, {0,200,200, 200},"Red Score :\n -"};
    TextButton mBlueScoreButton{"Select blue territories",
                          {Layout::GobanTopX + Layout::GobanWidth + Layout::CardMarginX,
                           Layout::GobanTopY,
                            2*Layout::CardWidth + Layout::CardMarginX,
                            150},
                            mBlueColor[0]
                          };
    TextButton mRedScoreButton{"Select red territories",
                         {Layout::GobanTopX + Layout::GobanWidth + Layout::CardMarginX,
                           Layout::GobanTopY + Layout::CardHeight,
                           2*Layout::CardWidth + Layout::CardMarginX,
                           150},
                           mRedColor[0]    
                        };

    std::vector<DrawRectangle> mBlueRegions;
	std::vector<DrawRectangle> mRedRegions;
    private:
};