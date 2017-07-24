#include<Windows.h>
#include<math.h>
#include"winlay.h"


void CreateGame(HWND hwnd)
{
	SetBoundary();
	CreateSoldier();
	CreateGeneral();
	CreateCMAN();
	CreateEmpty();
}


int TransferPos(int mx, int my)
{
	int dx = mx - 11;
	int dy = my - 11;
	int i = 0;

	i = dx / 80 + (dy / 80) * 4 + 1;

	return i;
}

Pgame_coord GetCoord(int n)
{
	game_coord t;
	switch (n)
	{
	case 1:
	case 2:
	case 3:
	case 4:
		t.x = n - 1;
		t.y = 0;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
		t.x = n - 5;
		t.y = 1;
		break;
	case 9:
	case 10:
	case 11:
	case 12:
		t.x = n - 9;
		t.y = 2;
		break;
	case 13:
	case 14:
	case 15:
	case 16:
		t.x = n - 13;
		t.y = 3;
		break;
	case 17:
	case 18:
	case 19:
	case 20:
		t.x = n - 17;
		t.y = 4;
		break;
	}
	return &t;
}
//
int DispatchCode(int nCode[2])
{
	int i, j, k;
	i = j = k = -1;
	int pi, pj, pk;
	Pgame_coord Code;
	game_coord p, q;
	int flag = 0;
	Code = GetCoord(nCode[0]);
	p = *Code;
	Code = GetCoord(nCode[1]);
	q = *Code;
	//判断是否选中了小兵
	for (pi = 0;pi < 4;pi++)
	{
		if (CoordEqual(&p, GetSoldier(pi)))
		{
			i = pi;
			flag = 1;
		}
	}
	//判断是否选中了将
	for (pi = 0;pi<5;pi++)
	{
		//Pgame_coord m;
		for (pj = 0;pj < 2;pj++)
		{
			if (CoordEqual(&p, GetGeneral(pi, pj)))
			{
				i = pi;
				flag = 2;
			}
		}
	}
	//判断是否选中曹操
	for (pi = 0;pi < 4;pi++)
	{
		if (CoordEqual(&p, GetCMAN(pi)))
		{
			flag = 3;
		}
	}

	//判断是否选中了空白
	for(pj=0;pj<2;pj++)
	{
		if (CoordEqual(&q, GetEmpty(pj)))
		{
			j = pj;
		}
	}
	//判断是否可以移动
	return CanMove(p, i, flag,j);


}


int CanMove(game_coord p, int i, int flag,int j)
{
	Pgame_coord emp;
	Pgame_coord e1, e2;
	int pj, k;

	//选中空白无操作
	if (flag == 0||j==-1)
	{
		return 0;
	}
	//选中小兵
	if (flag == 1)
	{
		if ((abs(p.x - empty[j].x) == 1 && p.y == empty[j].y) || (abs(p.y - empty[j].y) == 1 && p.x == empty[j].x))
		{
			CoordExchange(&solider[i], &empty[j]);
			return 1;
		}
	}

	//选中将
	if(flag==2)
	{
		Pgame_coord gen1,gen2;
		switch (i)
		{
		case 0:
		case 1:
		case 2:
		case 4:
			//竖将
			if (empty[j].x == GetGeneral(i, 0)->x && empty[j].y == GetGeneral(i, 0)->y - 1)
			{
				CoordExchange(&General[i][0], &empty[j]);
				CoordExchange(&General[i][1], &empty[j]);
				return 1;
			}
			else if (empty[j].x == GetGeneral(i, 0)->x && empty[j].y == GetGeneral(i, 1)->y + 1)
			{
				CoordExchange(&General[i][1], &empty[j]);
				CoordExchange(&General[i][0], &empty[j]);
				return 1;
			}

			//确定空白1，2位置
			if (empty[0].x > empty[1].x || empty[0].y > empty[1].y)
			{
				CoordExchange(&empty[0], &empty[1]);
			}
			e1 = GetEmpty(0);
			e2 = GetEmpty(1);
			if (e1->y == GetGeneral(i, 0)->y&&e2->y == GetGeneral(i, 1)->y)
			{
				if ((e1->x == GetGeneral(i, 0)->x - 1 && e2->x == GetGeneral(i, 1)->x - 1) 
					|| (e1->x == GetGeneral(i, 0)->x + 1 && e2->x == GetGeneral(i, 1)->x + 1))
				{
					CoordExchange(&General[i][0], &empty[0]);
					CoordExchange(&General[i][1], &empty[1]);
					return 1;
				}
			}
			break;
		case 3:
			//横将
			if (empty[j].y == GetGeneral(i, 0)->y && empty[j].x == GetGeneral(i, 0)->x - 1)
			{
				CoordExchange(&General[i][0], &empty[j]);
				CoordExchange(&General[i][1], &empty[j]);
				return 1;
			}
			else if (empty[j].y == GetGeneral(i, 0)->y && empty[j].x == GetGeneral(i, 1)->x + 1)
			{
				CoordExchange(&General[i][1], &empty[j]);
				CoordExchange(&General[i][0], &empty[j]);
				return 1;
			}

			//确定空白1，2位置
			if (empty[0].x > empty[1].x || empty[0].y > empty[1].y)
			{
				CoordExchange(&empty[0], &empty[1]);
			}
			e1 = GetEmpty(0);
			e2 = GetEmpty(1);
			if (e1->x == GetGeneral(i, 0)->x&&e2->x == GetGeneral(i, 1)->x)
			{
				if ((e1->y == GetGeneral(i, 0)->y - 1 && e2->y == GetGeneral(i, 1)->y - 1)
					|| (e1->y == GetGeneral(i, 0)->y + 1 && e2->y == GetGeneral(i, 1)->y + 1))
				{
					CoordExchange(&General[i][0], &empty[0]);
					CoordExchange(&General[i][1], &empty[1]);
					return 1;
				}
			}
			break;
		}
	
	}
	
	//选中曹操
	if(flag==3)
	{
		//确定空白1，2位置
		if (empty[0].x > empty[1].x || empty[0].y > empty[1].y)
		{
			CoordExchange(&empty[0], &empty[1]);
		}
		e1 = GetEmpty(0);
		e2 = GetEmpty(1);

		//判断是否可以移动
		if (e1->x == GetCMAN(0)->x&&e1->y == GetCMAN(0)->y - 1 && e2->x == GetCMAN(1)->x&&e2->y == GetCMAN(1)->y - 1)
		{
			CoordExchange(&empty[0], &CMAN[0]);
			CoordExchange(&empty[1], &CMAN[1]);
			CoordExchange(&empty[0], &CMAN[3]);
			CoordExchange(&empty[1], &CMAN[2]);
			return 1;
		}
		else if (e1->x == GetCMAN(3)->x&&e1->y == GetCMAN(3)->y + 1 && e2->x == GetCMAN(2)->x&&e2->y == GetCMAN(2)->y + 1)
		{
			CoordExchange(&empty[0], &CMAN[3]);
			CoordExchange(&empty[1], &CMAN[2]);
			CoordExchange(&empty[0], &CMAN[0]);
			CoordExchange(&empty[1], &CMAN[1]);
			return 1;
		}
		else if (e1->y == GetCMAN(0)->y&&e1->x == GetCMAN(0)->x - 1 && e2->y == GetCMAN(3)->y&&e2->x == GetCMAN(3)->y - 1)
		{
			CoordExchange(&empty[0], &CMAN[0]);
			CoordExchange(&empty[1], &CMAN[3]);
			CoordExchange(&empty[0], &CMAN[1]);
			CoordExchange(&empty[1], &CMAN[2]);
			return 1;
		}
		else if (e1->y == GetCMAN(1)->y&&e1->x == GetCMAN(1)->x + 1 && e2->y == GetCMAN(2)->y&&e2->x == GetCMAN(2)->x + 1)
		{
			CoordExchange(&empty[0], &CMAN[1]);
			CoordExchange(&empty[1], &CMAN[2]);
			CoordExchange(&empty[0], &CMAN[0]);
			CoordExchange(&empty[1], &CMAN[3]);
			return 1;
		}
		return 0;
	}
}

void Dispatch(int code)
{
	int i, j, k;
	i = j = k = -1;
	int pi, pj, pk;
	Pgame_coord Code;
	game_coord p, q;
	Code = GetCoord(code);
	p = *Code;
	//判断是否选中了小兵
	for (pi = 0;pi < 4;pi++)
	{
		if (CoordEqual(&p, GetSoldier(pi)))
		{
			solider[pi].select = 1;
		}
	}
	//判断是否选中了将
	for (pi = 0;pi<5;pi++)
	{
		for (pj = 0;pj < 2;pj++)
		{
			if (CoordEqual(&p, GetGeneral(pi, pj)))
			{
				General[pi][0].select = 1;
			}
		}
	}
	//判断是否选中曹操
	for (pi = 0;pi < 4;pi++)
	{
		if (CoordEqual(&p, GetCMAN(pi)))
		{
			CMAN[0].select = 1;
		}
	}
}