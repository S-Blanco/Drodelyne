#pragma once

/*
Pixels positions of each element of the game
TODO : Currently fixed but should adapt to the size of the window later
*/
namespace Layout{

int ScreenWidth{1366};
int ScreenHeight{768};

int GobanWidth{675};
int GobanHeight{675};

int GobanTopX{static_cast<int>((ScreenWidth - 1.3*GobanWidth)/2)};
int GobanTopY{(ScreenHeight - GobanHeight)/2};

int CardWidth{200};
int CardHeight{static_cast<int>(1.44*CardWidth)};

int BigCardWidth{300};
int BigCardHeight{static_cast<int>(1.44*BigCardWidth)};

int CardMarginX{(ScreenWidth - GobanTopX - GobanWidth - 2*CardWidth)/3};
int CardMarginY{(GobanHeight - 2*CardHeight)/4};

int BigModeX{GobanTopX + GobanWidth + (ScreenWidth - GobanTopX - GobanWidth - BigCardWidth)/2};
int BigModeY{GobanTopY + (GobanHeight - BigCardHeight)/2};

int TopHandX{GobanTopX + GobanWidth + CardMarginX};
int TopHandY{GobanTopY + CardMarginY};

int TopDeckX{CardMarginX};
int TopDeckY{GobanTopY + GobanHeight - CardHeight};

int InterRowY{(GobanHeight - 2*(CardMarginY + CardHeight))/2};
}