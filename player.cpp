#include "stdafx.h"
#include "obj.h"
#include "func.h"


void Player::Display()
{
	if (health == 3)
		putimage(posx - 35, posy - 35, &p1);
	else if (health == 2)
		putimage(posx - 35, posy - 35, &p2);
	else
		putimage(posx - 35, posy - 35, &p3);
}
void Player::Move()
{
	static int cnt = 0;
	if (GetKeyState(38) < 0 && posy >= 35)
	{
		if (GetKeyState(VK_SHIFT) < 0)
			posy -= 2;
		else
			posy -= 4;
	}
	if (GetKeyState(40) < 0 && posy <= 865)
	{
		if (GetKeyState(VK_SHIFT) < 0)
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
		Emitter(bullet_type, "line", 1);
		bullet_type.posx = posx + 7, bullet_type.posy = posy - 50; //bullets are produced in front of plane
		PlaySound(TEXT("./res/shoot1.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	cnt = (cnt + 1) % 15;

}
