#ifndef HRD_H
#define HRD_H

#include<Windows.h>


//游戏坐标
typedef struct _coord
{
	short x;
	short y;
	int select;
}game_coord, *Pgame_coord;

game_coord solider[4];
game_coord empty[2];
game_coord General[5][2];
game_coord CMAN[4];

//游戏函数声明

//设置边界坐标
void SetBoundary();
//获得边界坐标
Pgame_coord GetBoundary();
//生成小兵
void CreateSoldier();
//获得小兵坐标
Pgame_coord GetSoldier(int x);
//兵移动
int SoldierMove();
//生成将
void CreateGeneral();
//将移动
int GeneralMove();
//获得将的坐标
Pgame_coord GetGeneral(int i, int j);
//生成核心滑块
void CreateCMAN();
//获得核心滑块坐标
Pgame_coord GetCMAN(int i);
//生成空白区域
void CreateEmpty();
//获取空白区域坐标
Pgame_coord GetEmpty(int i);
//判断坐标是否重合
int CoordEqual(Pgame_coord a, Pgame_coord b);
//交换坐标
void CoordExchange(Pgame_coord a, Pgame_coord b);

#endif // !HRD_H