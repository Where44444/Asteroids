#ifndef mediumasteroid_h
#define mediumasteroid_h

#include "asteroid.h"

class mediumAsteroid : public Asteroid
{
private:
	int name;

public:
	mediumAsteroid()
	{
		name = 2;
	};
	virtual int getName() { return name; };
	virtual void draw()
	{
		drawMediumAsteroid(point, angle);
		angle = angle + MEDIUM_ROTATE;
	};
	void fireLM1(Point asteroidPoint, Velocity vel)
	{
		velocity = vel;
		velocity.addDy(1);
		point = asteroidPoint;
		point.addY(30);
	};
	void fireLM2(Point asteroidPoint, Velocity vel)
	{
		velocity = vel;
		velocity.addDy(-1);
		point = asteroidPoint;
		point.addY(-30);
	};

};

#endif