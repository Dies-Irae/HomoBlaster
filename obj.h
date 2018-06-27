#pragma once
#include "stdafx.h"
#include <time.h>
#include <random>
#include <conio.h>
#include <graphics.h>
#define PI 3.14159

using namespace std;

class Bullet;
class Player;
class Enemy;

class Bullet
{
public:
	Bullet(double px, double py, int s, double s_a, int dmg, bool ran, IMAGE *b_img): posx(px),
		posy(py), speed(s), speed_angle(s_a), random(ran), damage(dmg), bul_img(b_img) {}
	void Update();
	void Display() { putimage(posx - 10, posy - 10, bul_img); }
	bool Out_of_bound() { return (posx < 0 || posx>500 || posy < 0 || posy>900); }
	double posx, posy;
	bool random;
	int damage;
	int speed;
	double speed_angle;
protected:
	IMAGE * bul_img;
};

class Enemy
{
public:
	Enemy(int h, int px, int py, IMAGE *img) : hp(h), posx(px), posy(py), ene_img(img) {}
	void Display() { putimage(posx - 60, posy - 60, ene_img); }
	int posx, posy;
	int hp;
protected:
	IMAGE * ene_img;
};
class Player
{
public:
	Player() {
		loadimage(&p1, _T("./res/Player.bmp"));
		loadimage(&p2, _T("./res/Player2.bmp"));
		loadimage(&p3, _T("./res/Player3.bmp"));
		loadimage(&pB1, _T("./res/player_bullet_1.bmp"));
	} //Initialize image of Player
	void Display();
	void Move();
	int posx = 250, posy = 450;
	int health = 3; //Health range: 1~3
	Bullet bullet_type = Bullet(0, 0, 5, -PI / 2, 100, false, &pB1);
private:
	IMAGE p1, p2, p3, pB1;
};


