#include "ship.h"
#include <cassert>

void Ship::draw() const
{
	drawShip(point, angle, isthrust);
}
void Ship::moveLeft()
{
	angle += ROTATE_AMOUNT;
	if (angle > 360)
		angle = angle - 360;
	if (angle < 0)
		angle = angle + 360;
}
void Ship::moveRight()
{
	angle -= ROTATE_AMOUNT;
	if (angle > 360)
		angle = angle - 360;
	if (angle < 0)
		angle = angle + 360;
}
void Ship::thrust()
{
	int angleX;
	int angleY;

	if (angle >= 0 && angle <= 90)
	{
		angleX = angle;
		angleY = angle - 90;
	}
	else if (angle > 90 && angle <= 180)
	{
		angleX = 180 - angle;
		angleY = angle - 90;
	}
	else if (angle > 180 && angle <= 270)
	{
		angleX = 180 - angle;
		angleY = 270 - angle;
	}
	else
	{
		angleX = -360 + angle;
		angleY = 270 - angle;
	}
	
	this->isthrust = true;
	velocity.addDx(THRUST_AMOUNT*angleX/-90);
	velocity.addDy(THRUST_AMOUNT*angleY/-90);
}

