#include"hrd.h"

//兵
game_coord solider[4];
//将
PLIST general_1, general_2, general_3, general_4, general_5;
//核心
game_coord CMAN[4];
//边界
game_coord boundary;
//空白
game_coord empty[2];


int CoordEqual(Pgame_coord a, Pgame_coord b)
{
	if (a->x == b->x&&a->y == b->y)
		return 1;
	return 0;
}

void CoordExchange(Pgame_coord a, Pgame_coord b)
{
	Pgame_coord c;
	c = (Pgame_coord)malloc(sizeof(game_coord));
	c->x = a->x;c->y = a->y;
	a->x = b->x;a->y = b->y;
	b->x = c->x;b->y = c->y;
}

void SetBoundary()
{
	boundary.x = 3;
	boundary.y = 4;
}

Pgame_coord GetBoundary()
{
	return &boundary;
}

void CreateSoldier()
{
	solider[0].x = 0;
	solider[0].y = 4;

	solider[1].x = 1;
	solider[1].y = 3;

	solider[2].x = 2;
	solider[2].y = 3;

	solider[3].x = 3;
	solider[3].y = 4;
}

//获得小兵坐标
Pgame_coord GetSoldier(int i)
{
	return &solider[i];
}

void CreateGeneral()
{
	Pgame_coord s1, s2, s3, s4, s5;
	Pgame_coord new1, new2, new3, new4, new5;
	Pgame_coord c1, c2, c3, c4;

	General[0][0].x = 0;
	General[0][0].y = 0;
	General[0][1].x = 0;
	General[0][1].y = 1;

	General[1][0].x = 3;
	General[1][0].y = 0;
	General[1][1].x = 3;
	General[1][1].y = 1;

	General[2][0].x = 0;
	General[2][0].y = 2;
	General[2][1].x = 0;
	General[2][1].y = 3;

	General[3][0].x = 1;
	General[3][0].y = 2;
	General[3][1].x = 2;
	General[3][1].y = 2;

	General[4][0].x = 3;
	General[4][0].y = 2;
	General[4][1].x = 3;
	General[4][1].y = 3;
}
Pgame_coord GetGeneral(int i, int j)
{
	return &General[i][j];
}

void CreateCMAN()
{
	CMAN[0].x = 1;
	CMAN[0].y = 0;

	CMAN[1].x = 2;
	CMAN[1].y = 0;

	CMAN[2].x = 2;
	CMAN[2].y = 1;

	CMAN[3].x = 1;
	CMAN[3].y = 1;
}

Pgame_coord GetCMAN(int i)
{
	return &CMAN[i];
}

void CreateEmpty()
{
	empty[0].x = 1;
	empty[0].y = 4;

	empty[1].x = 2;
	empty[1].y = 4;
}

Pgame_coord GetEmpty(int i)
{
	return &empty[i];
}