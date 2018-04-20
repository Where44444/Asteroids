#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5
#include "flyingObject.h"

class Ship : public FlyingObject
{

private:
	bool isthrust;

public:
	Ship() { angle = 0; isthrust = false; point.setX(0); point.setY(0); }

	void kill() { this->alive = false;};
	bool isAlive() { return this->alive; };
	/****************
	* Basic Getters
	****************/
	float getAngle() const { return angle; }
	Point getPoint() const { return point; }

	/*****************
	* Drawing
	*****************/
	void draw() const;

	/*****************
	* Movement
	*****************/
	void moveLeft();
	void moveRight();
	void thrust();
	void setThrust(bool thrust) { this->isthrust = thrust; };
	void advance()
	{
		point.addY(velocity.getDy());
		point.addX(velocity.getDx());
	};
	void setShipX(int x) { point.setX(x); };
	void setShipY(int y) { point.setY(y); };

};

// Put your Ship class here


#endif /* ship_h */
