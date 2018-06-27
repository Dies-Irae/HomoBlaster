#include "stdafx.h"
#include "func.h"
#include "obj.h"

extern vector<Bullet> activated_Bullet;

void Emitter(Bullet b_type, string trace, int num)
{
	if (trace == "line")
	{
		Bullet b1(b_type);
		activated_Bullet.push_back(b1);
	}
	else if (trace == "curve")
	{
		Bullet b1=b_type;
		static int init_angle = 0;
		b1.speed_angle = init_angle % 3 / 3.0;
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
		b1.speed_angle = init_angle;
		tmp = tmp + 1 % 6;
		init_angle = abs(0.3 - tmp / 10.0);
		double step = PI / (double)num;
		for (int i = 0; i != num; i++)
		{
			b1.speed_angle += step;
			activated_Bullet.push_back(b1);
		}

	}
}

