#include "stdafx.h"
#include "obj.h"
#include <math.h>


using namespace std;

void Bullet::Update()
{
	static default_random_engine e(time(0));
	uniform_real_distribution<double> u(0, 3.14);
	if (random == 0)
	{
		posx += speed * cos(speed_angle);
		posy += speed * sin(speed_angle);
	}
	else
	{
		speed_angle = u(e);
		posx += speed * 2.5* cos(speed_angle);
		posy += speed * sin(speed_angle);
	}
}
