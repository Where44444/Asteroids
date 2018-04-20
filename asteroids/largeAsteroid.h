#ifndef largeasteroid_h
#define largeasteroid_h

#include "asteroid.h"

class largeAsteroid : public Asteroid
{
private:
	int name;

public:
	largeAsteroid() { name = 1; };
	virtual int getName() { return name; };

	virtual void draw()
	{
		drawLargeAsteroid(point, angle);
		angle = angle + LARGE_ROTATE;
	};

};

#endif