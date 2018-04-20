#ifndef flyingObject_h
#define flyingObject_h




#include "point.h"
#include "uiDraw.h"
#include "velocity.h"

class FlyingObject
{

protected:
	Velocity velocity;
	Point point;
	bool active;
	bool alive;
	float angle;

public:
	Velocity getVelocity() const { return velocity; }
	Point getPoint() const { return point; }
	FlyingObject()
	{
		alive = true;
	}
};

#endif /* flyingObject_h */
