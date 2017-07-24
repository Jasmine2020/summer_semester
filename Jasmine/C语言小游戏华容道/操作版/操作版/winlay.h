#ifndef HRD_WIN
#define HRD_WIN

#include<windows.h>
#include"hrd.h"

#define IMAGINE_PAPER   "paper.bmp"

void CreateGame(HWND hwnd);

int TransferPos(int mx, int my);

int DispatchCode(int nCode[2]);

Pgame_coord GetCoord(int n);

int CanMove(game_coord p, int i, int flag,int j);

void Dispatch(int code);

#endif // !HRD_WIN

