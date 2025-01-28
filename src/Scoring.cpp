#include "Scoring.h"


void Scoring::Render(SDL_Surface* Surface){
    if (mBlueRegions.size() > 0){
        for (DrawRectangle& Rect : mBlueRegions){
			Rect.Render(Surface);
		}
    }
    if (mRedRegions.size() > 0){
        for (DrawRectangle& Rect : mRedRegions){
			Rect.Render(Surface);
		}
    }
    mBlueScoreButton.Render(Surface);
    mRedScoreButton.Render(Surface);
    mBlueScoreText.Render(Surface);
    mRedScoreText.Render(Surface);
    mComputeScore.Render(Surface);
}


void Scoring::HandleEvent(const SDL_Event& Event){
    if (Event.type == SDL_MOUSEBUTTONDOWN
        && Event.button.button == SDL_BUTTON_LEFT){
        if (Event.button.x >= Layout::GobanTopX && Event.button.x <= Layout::GobanTopX + Layout::GobanWidth
         && Event.button.y >= Layout::GobanTopY && Event.button.y <= Layout::GobanTopY + Layout::GobanHeight){
            mBlueIsActive ? mBlueRegions.emplace_back(0, 0, 0, 0, Layout::TerritoryBorderSize, mIndex++, mBlueColor[0], mBlueColor[1])
                          :  mRedRegions.emplace_back(0, 0, 0, 0, Layout::TerritoryBorderSize, mIndex++, mRedColor[0],  mRedColor[1]);
        }
    }
    if (Event.type == SDL_MOUSEBUTTONDOWN){
        if (mBlueScoreButton.IsWithinBounds(Event.button.x, Event.button.y)){
            mBlueIsActive = true;
            mBlueScoreButton.SetColor(mBlueColor[1]);
            mRedScoreButton.SetColor(mRedColor[0]);
        } else if (mRedScoreButton.IsWithinBounds(Event.button.x, Event.button.y)){
            mBlueIsActive = false;
            mBlueScoreButton.SetColor(mBlueColor[0]);
            mRedScoreButton.SetColor(mRedColor[1]);
        } else if(mComputeScore.IsWithinBounds(Event.button.x, Event.button.y)){
            mBlueScore = 0;
            mRedScore = 0;
            for (DrawRectangle& Rect : mBlueRegions){ mBlueScore += Rect.GetScore(); }
            for (DrawRectangle& Rect : mRedRegions) { mRedScore += Rect.GetScore(); }
            mBlueScoreText.mContent = std::format("Blue Score :\n {}",mBlueScore);
            mRedScoreText.mContent = std::format("Red Score :\n {}",mRedScore);
        }
    }
    if (mBlueIsActive){
        if (mBlueRegions.size() > 0){
            if (Event.type == SDL_MOUSEBUTTONDOWN
                && Event.button.button == SDL_BUTTON_RIGHT){
                for (DrawRectangle& Rect : mBlueRegions){
                    Rect.HandleEvent(Event);
                }
            } else if(Event.type == Events::DELETE_ZONE){
                int DeleteIdx{0};
                for (DrawRectangle& Rect : mBlueRegions){
                    if (Rect.GetIndex() == Event.motion.x){
                        mBlueRegions.erase(mBlueRegions.begin() + DeleteIdx);
                        break;
                    }
                    ++DeleteIdx;
                }
            }
            mBlueRegions.back().HandleEvent(Event);
        }
    } else {
        if (mRedRegions.size() > 0){
            if (Event.type == SDL_MOUSEBUTTONDOWN
                && Event.button.button == SDL_BUTTON_RIGHT){
                for (DrawRectangle& Rect : mRedRegions){
                    Rect.HandleEvent(Event);
                }
            } else if(Event.type == Events::DELETE_ZONE){
                int DeleteIdx{0};
                for (DrawRectangle& Rect : mRedRegions){
                    if (Rect.GetIndex() == Event.motion.x){
                        mRedRegions.erase(mRedRegions.begin() + DeleteIdx);
                        break;
                    }
                    ++DeleteIdx;
                }
            }
            mRedRegions.back().HandleEvent(Event);
        }
    }
}