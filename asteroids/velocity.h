#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity
{

private:
	float DX;
	float DY;

public:
	Velocity()
	{
		DX = 0;
		DY = 0;
	}

	Velocity(float DX2, float DY2)
	{
		DX = DX2;
		DY = DY2;
	}
	void addDx(float DX) { this->DX += DX; };
	void addDy(float DY) { this->DY += DY; };
	void setDx(float DX) { this->DX = DX; };
	void setDy(float DY) { this->DY = DY; };
	float getDx() const { return DX; };
	float getDy() const { return DY; };
};

#endif /* velocity_h */
