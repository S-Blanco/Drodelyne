#pragma once

/*
Pixels positions of each element of the game
TODO : Currently fixed but should adapt to the size of the window later
*/
namespace Layout{

inline const int CellWidth{35}; //Note: box sprite = 33px but 2 px for edges
inline const int CellHeight{35};
inline const int EdgeWidth{5};

inline const int ScreenWidth{1366};
inline const int ScreenHeight{768};

inline const int GobanWidth{675};
inline const int GobanHeight{675};

inline const int GobanTopX{static_cast<int>((ScreenWidth - 1.3*GobanWidth)/2)};
inline const int GobanTopY{(ScreenHeight - GobanHeight)/2};

inline const int CardWidth{200};
inline const int CardHeight{static_cast<int>(1.44*CardWidth)};

inline const int BigCardWidth{300};
inline const int BigCardHeight{static_cast<int>(1.44*BigCardWidth)};

inline const int CardMarginX{(ScreenWidth - GobanTopX - GobanWidth - 2*CardWidth)/3};
inline const int CardMarginY{0};

inline const int BigModeX{GobanTopX + GobanWidth + (ScreenWidth - GobanTopX - GobanWidth - BigCardWidth)/2};
inline const int BigModeY{GobanTopY + (GobanHeight - BigCardHeight)/2};

inline const int TopHandX{GobanTopX + GobanWidth + CardMarginX};
inline const int TopHandY{GobanTopY + CardMarginY};

inline const int TopDeckX{CardMarginX};
inline const int TopDeckY{GobanTopY + GobanHeight - CardHeight};

inline const int PassButtonHeight{75};
inline const int PassButtonMarginY{10};
inline const int InterRowY{(GobanHeight - 2*CardHeight - CardMarginY - PassButtonHeight + PassButtonMarginY)/2};
}