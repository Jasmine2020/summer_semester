#ifndef HRD_H
#define HRD_H

#include<Windows.h>


//��Ϸ����
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

//��Ϸ��������

//���ñ߽�����
void SetBoundary();
//��ñ߽�����
Pgame_coord GetBoundary();
//����С��
void CreateSoldier();
//���С������
Pgame_coord GetSoldier(int x);
//���ƶ�
int SoldierMove();
//���ɽ�
void CreateGeneral();
//���ƶ�
int GeneralMove();
//��ý�������
Pgame_coord GetGeneral(int i, int j);
//���ɺ��Ļ���
void CreateCMAN();
//��ú��Ļ�������
Pgame_coord GetCMAN(int i);
//���ɿհ�����
void CreateEmpty();
//��ȡ�հ���������
Pgame_coord GetEmpty(int i);
//�ж������Ƿ��غ�
int CoordEqual(Pgame_coord a, Pgame_coord b);
//��������
void CoordExchange(Pgame_coord a, Pgame_coord b);

#endif // !HRD_H