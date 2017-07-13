#ifndef HRD_WIN
#define HRD_WIN

#include<windows.h>
#include"hrd.h"

void CreateGame(HWND hwnd);

int TransferPos(int mx, int my);

int DispatchCode(int nCode);

Pgame_coord GetCoord(int n);

int CanMove(game_coord p, int i, int flag);

#endif // !HRD_WIN

