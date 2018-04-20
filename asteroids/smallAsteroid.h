#ifndef smallasteroid_h
#define smallasteroid_h

#include "asteroid.h"

class smallAsteroid : public Asteroid
{
private:
	int name;

public:
	smallAsteroid() { name = 3; };
	virtual int getName() { return name; };
	virtual void draw()
	{
		drawSmallAsteroid(point, angle);
		angle = angle + SMALL_ROTATE;
	};

	void fireLS(Point asteroidPoint, Velocity vel)
	{
		velocity = vel;
		velocity.addDx(2);
		point = asteroidPoint;
		point.addX(30);
	};
	void fireMS1(Point asteroidPoint, Velocity vel)
	{
		velocity = vel;
		velocity.addDx(3);
		point = asteroidPoint;
		point.addX(15);
	};
	void fireMS2(Point asteroidPoint, Velocity vel)
	{
		velocity = vel;
		velocity.addDx(-3);
		point = asteroidPoint;
		point.addX(-15);
	};
};

#endif