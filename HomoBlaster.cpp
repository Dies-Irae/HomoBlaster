#pragma comment(lib,"winmm.lib") 

#include "stdafx.h"
#include <array>
#include <vector>
#include <string>
#include <windows.h>
#include "obj.h"
#include "func.h"


#define PI 3.14159
using namespace std;

IMAGE ene_bul_ima_1;
IMAGE ene;
IMAGE over, win;
Bullet ene_bullet_1(250, 170, 4, PI / 2, 0, true, &ene_bul_ima_1);//random route
Bullet ene_bullet_2(250, 170, 4, PI / 2, 0, false, &ene_bul_ima_1);
vector<Bullet> activated_Bullet;

int main()
{

	loadimage(&ene_bul_ima_1, _T("./res/ene_bullet_1.bmp"));
	loadimage(&over, _T("./res/over.bmp"));
	loadimage(&ene, _T("./res/Chi_chan.bmp"));
	loadimage(&win, _T("./res/win.bmp"));

	initgraph(500, 900);   

	Player p1;
	Enemy e1(6000, 250, 100, &ene);
	int cnt = 0;
	while (1)
	{

		p1.Display();
		e1.Display();
		p1.Move();
		for (vector<Bullet>::iterator iter = activated_Bullet.begin(); iter != activated_Bullet.end();)
		{
			//display position of bullets
			iter->Update();
			iter->Display();
			//erase bullets out of bound
			if (iter->Out_of_bound())
				iter = activated_Bullet.erase(iter);
			//hit effect
			else if (abs(p1.posx - iter->posx) < 15 && abs(p1.posy - iter->posy) < 15)
			{
				iter = activated_Bullet.erase(iter), p1.health--;
				if (p1.health > 0)
					PlaySound(TEXT("./res/hit.wav"), NULL, SND_FILENAME | SND_SYNC);
				else
				{
					PlaySound(TEXT("./res/death.wav"), NULL, SND_FILENAME | SND_ASYNC);
					goto LOSE;
				}
			}
			else if (abs(e1.posx - iter->posx) < 60 && abs(e1.posy - iter->posy) < 60)
			{
				e1.hp -= iter->damage;
				iter = activated_Bullet.erase(iter);
				if (e1.hp <= 0)
				{
					PlaySound(TEXT("./res/win.wav"), NULL, SND_FILENAME | SND_ASYNC);
					goto WIN;

				}
			}
			else
				iter++;
			if (abs(p1.posx - e1.posx) < 50 && abs(p1.posy - e1.posy) < 50)
			{
				PlaySound(TEXT("./res/death.wav"), NULL, SND_FILENAME | SND_ASYNC);
				goto LOSE;
			}
				
		}
		Sleep(15);

		//Stage Design
		if (cnt == 0)
		{
			if (e1.hp >= 4000)
				Emitter(ene_bullet_2, "curve", 15);
			else if (e1.hp >= 2000)
				Emitter(ene_bullet_2, "fan", 20);
			else
				Emitter(ene_bullet_1, "line", 0);
		}
		cnt = (cnt + 1) % 10;

		clearcliprgn();
	}
LOSE:
	putimage(50, 400, &over);
	Sleep(3000);
	_getch();            
	closegraph();
	return 0;
WIN:
	putimage(50, 400, &win);
	Sleep(3000);
	_getch();              
	closegraph();
	return 0;
}