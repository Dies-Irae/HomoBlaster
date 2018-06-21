#include "stdafx.h"
#include <random>
#include <time.h>
#include <array>
#include <vector>
#include <string>
#include <graphics.h>      // Need EasyX library
#include <conio.h>
#include <windows.h>

#pragma comment(lib,"winmm.lib") 
#define PI 3.14159

using namespace std;
class Bullet;
class Player;
void Emitter(Bullet b_type, string trace, int num);

static vector<Bullet> activated_Bullet;
IMAGE pH1, pH2, pH3;
IMAGE ene_bul_ima_1;
IMAGE pla_bul_ima_1;
IMAGE ene;
IMAGE over, win;


class Player
{
public:
	Player(IMAGE *i, IMAGE *j, IMAGE *k) :p1(i), p2(j), p3(k) {} //不同HP下的自机图像
	void Display();
	void Move();
	int posx = 250, posy = 450;
	int health = 3; //Health range: 1~3
private:
	IMAGE *p1, *p2, *p3;
};

class Bullet
{
public:
	Bullet(double px, double py, int s, double s_a, int dmg, bool ran ,IMAGE *b_img) : posx(px), posy(py), speed(s), speed_angle(s_a), random(ran) ,damage(dmg), bul_img(b_img) {}
	void Update();
	void Display() { putimage(posx - 10, posy - 10, bul_img); }
	bool Out_of_bound() { return (posx < 0 || posx>500 || posy < 0 || posy>900); }
	double posx, posy;
	bool random;
	int damage;
	int speed;
	double speed_angle;
protected:

	IMAGE *bul_img;
};
//Bullet settings
//posx, posy, speed, angle, random, damage
Bullet pla_bullet_1(0, 0, 5, -PI / 2, 100, false ,&pla_bul_ima_1);
Bullet ene_bullet_1(250, 170, 4, PI / 2, 0,true, &ene_bul_ima_1);//random route
Bullet ene_bullet_2(250, 170, 4, PI / 2, 0, false, &ene_bul_ima_1);


class Enemy
{
public:
	Enemy(int h, int px, int py, IMAGE *img) : hp(h),posx(px),posy(py),ene_img(img) {}
	void Display() { putimage(posx - 60, posy - 60, ene_img); }
	int posx, posy;
	int hp;
protected:
	IMAGE *ene_img;
};

void Player::Move()
{
	static int cnt=0;
	if (GetKeyState(38) < 0 && posy >= 35)
	{
		if(GetKeyState(VK_SHIFT) < 0 )
			posy -= 2;
		else
			posy -= 4;
	}
	if (GetKeyState(40) < 0 && posy <= 865)
	{
		if (GetKeyState(VK_SHIFT) < 0 )
			posy += 2;
		else
			posy += 4;
	}
	if (GetKeyState(37) < 0 && posx >= 35)
	{
		if (GetKeyState(VK_SHIFT) < 0)
			posx -= 2;
		else
			posx -= 4;
	}
	if (GetKeyState(39) < 0 && posx <= 465)
	{
		if (GetKeyState(VK_SHIFT) < 0)
			posx += 2;
		else
			posx += 4;
	}
	if (cnt == 0 && GetKeyState(VK_CONTROL) < 0)
	{
		pla_bullet_1.posx = posx+7, pla_bullet_1.posy = posy-50;
		Emitter(pla_bullet_1,"line",1);
		PlaySound(TEXT("./res/shoot1.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	cnt=(cnt+1)%15;

}
void Player::Display()
{
	if (health == 3)
		putimage(posx - 35, posy - 35, p1);
	else if (health == 2)
		putimage(posx - 35, posy - 35, p2);
	else
		putimage(posx - 35, posy - 35, p3);
}


void Bullet::Update()
{
	static default_random_engine e(time(0));
	uniform_real_distribution<double> u(0, 3.14);
	if (random==0)
	{
		posx += speed * cos(speed_angle);
		posy += speed * sin(speed_angle);
	}
	else 
	{
		speed_angle = u(e);
		posx += speed *2.5* cos(speed_angle);
		posy += speed * sin(speed_angle);
	}
}


void Emitter(Bullet b_type, string trace, int num)
{
	if (trace == "line")
	{
		Bullet b1(b_type);
		activated_Bullet.push_back(b1);
	}
	else if (trace == "curve")
	{
		Bullet b1(b_type);
		static int init_angle=0;
		b1.speed_angle = init_angle%3/3.0;
		init_angle++;
		double step = PI / (double)num;
		for (int i = 0; i != num; i++)
		{
			b1.speed_angle += step;
			activated_Bullet.push_back(b1);
		}
	}
	else
	{
		Bullet b1(b_type);
		static double init_angle = 0.2;
		static int tmp;
		b1.speed_angle = init_angle ;
		tmp = tmp + 1 % 6;
		init_angle = abs(0.3-tmp/10.0);
		double step = PI / (double)num;
		for (int i = 0; i != num; i++)
		{
			b1.speed_angle += step;
			activated_Bullet.push_back(b1);
		}

	}
}

int main()
{
	loadimage(&pH1, _T("./res/Player.bmp"));
	loadimage(&pH2, _T("./res/Player2.bmp"));
	loadimage(&pH3, _T("./res/Player3.bmp"));
	loadimage(&ene_bul_ima_1, _T("./res/ene_bullet_1.bmp"));
	loadimage(&pla_bul_ima_1, _T("./res/player_bullet_1.bmp"));
	loadimage(&over, _T("./res/over.bmp"));
	loadimage(&ene, _T("./res/Chi_chan.bmp"));
	loadimage(&win, _T("./res/win.bmp"));

	initgraph(500, 900);   // 创建绘图窗口

	Player p1(&pH1, &pH2, &pH3);
	Enemy e1(6000, 250, 100, &ene);
	int cnt = 0;
	while (1)
	{

		p1.Display();
		e1.Display();
		p1.Move();
		for (vector<Bullet>::iterator iter= activated_Bullet.begin(); iter!=activated_Bullet.end();)
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
				if(p1.health!=0)
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
				if(e1.hp<=0)
				{
					PlaySound(TEXT("./res/win.wav"), NULL, SND_FILENAME | SND_ASYNC);
					goto WIN;

				}
					
			}
			else
				iter++;
		}
		Sleep(15);
		//Stage Design
		if (cnt == 0)
		{
			if(e1.hp>=4000)
				Emitter(ene_bullet_2, "curve", 15);
			else if(e1.hp >= 2000)
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
	_getch();              // 按任意键继续
	closegraph();// 关闭绘图窗口
	return 0;
WIN:
	putimage(50, 400, &win);
	Sleep(3000);
	_getch();              // 按任意键继续
	closegraph();// 关闭绘图窗口
	return 0;
}