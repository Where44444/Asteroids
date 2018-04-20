#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40


#include "flyingObject.h"

class Bullet : public FlyingObject
{

private:
	int life;

public:
	Bullet()
	{
		point.setX(200);
		point.setY(-200);
		velocity.setDx(0);
		velocity.setDy(0);
		life = 40;
		alive = true;
	}

	void kill()
	{
		this->alive = false;
	};
	bool isAlive() { return this->alive; };
	Point getPoint() const { return point; };

	void fire(Point riflePoint, float rifleAngle, Velocity shipVelocity)
	{
		int angleX;
		int angleY;

		if (rifleAngle >= 0 && rifleAngle<= 90)
		{
			angleX = rifleAngle;
			angleY = rifleAngle- 90;
		}
		else if (rifleAngle> 90 && rifleAngle<= 180)
		{
			angleX = 180 - rifleAngle;
			angleY = rifleAngle- 90;
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
		velocity.setDx(BULLET_SPEED * angleX / -90 + shipVelocity.getDx());
		velocity.setDy(BULLET_SPEED * angleY / -90 + shipVelocity.getDy());
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

	void draw()
	{ 
		drawCircle(point, 2); life--;
		if (life < 0)
			kill();
	};
};


#endif /* bullet_h */
