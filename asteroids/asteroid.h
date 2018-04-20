#ifndef asteroid_h
#define asteroid_h

#define LARGE_SPEED 1
#define MEDIUM_SPEED 1
#define SMALL_SPEED 1
#define LARGE_ROTATE 2
#define MEDIUM_ROTATE 5
#define SMALL_ROTATE 10
#define LARGE 1
#define MEDIUM 2
#define SMALL 3

#include "flyingObject.h"

class Asteroid : public FlyingObject
{

private:
	int life;
	int type;
	int name;

public:
	Asteroid()
	{
		point.setX(200);
		point.setY(-200);
		velocity.setDx(0);
		velocity.setDy(0);
		angle = random(0, 360);
		alive = true;
		name = 0;
	}

	void kill()
	{
		this->alive = false;
	};
	bool isAlive() { return this->alive; };
	Point getPoint() const { return point; };
	virtual int getName() { return name; };

	virtual void fire(Point riflePoint, float rifleAngle)
	{
		float angleX;
		float angleY;
		if (rifleAngle >= 0 && rifleAngle <= 90)
		{
			angleX = rifleAngle;
			angleY = rifleAngle - 90;
		}
		else if (rifleAngle> 90 && rifleAngle <= 180)
		{
			angleX = 180 - rifleAngle;
			angleY = rifleAngle - 90;
		}
		else if (rifleAngle > 180 && rifleAngle <= 270)
		{
			angleX = 180 - rifleAngle;
			angleY = 270 - rifleAngle;
		}
		else
		{
			angleX = -360 + rifleAngle;
			angleY = 270 - rifleAngle;
		}
		velocity.setDx(ceil(LARGE_SPEED * angleX / -90));
		velocity.setDy(ceil(LARGE_SPEED * angleY / -90));
		if (rifleAngle == 500)
		{
			velocity.setDx(10);
			velocity.setDy(random(-1, 1));
		}
		set(riflePoint);
	}



	void set(Point riflePoint)
	{
		point.setX(riflePoint.getX());
		point.setY(riflePoint.getY());
	}
	void setBulletX(int x) { point.setX(x); };
	void setBulletY(int y) { point.setY(y); };

	void advance()
	{
		point.addY(velocity.getDy());
		point.addX(velocity.getDx());
	};

	virtual void draw()
	{
		drawLargeAsteroid(point, angle);
		angle = angle + LARGE_ROTATE;
		std::cout << "Drawing Generic ";
	};
};


#endif
