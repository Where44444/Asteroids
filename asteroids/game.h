/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include "flyingObject.h"
#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "bullet.h"
#include "ship.h"
#include "asteroid.h"
#include "largeAsteroid.h"
#include "mediumAsteroid.h"
#include "smallAsteroid.h"
#include <vector>
using namespace std;
class Game
{
public:
	float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;

	/*********************************************
	* Constructor
	* Initializes the game
	*********************************************/
	Game(Point tl, Point br);
	~Game();

	/*********************************************
	* Function: handleInput
	* Description: Takes actions according to whatever
	*  keys the user has pressed.
	*********************************************/
	void handleInput(const Interface & ui);

	/*********************************************
	* Function: advance
	* Description: Move everything forward one
	*  step in time.
	*********************************************/
	void advance();

	/*********************************************
	* Function: draw
	* Description: draws everything for the game.
	*********************************************/
	void draw(const Interface & ui);


private:
	// The coordinates of the screen
	int score;
	Ship ship;
	std::vector<Bullet> bullets;
	std::vector<Asteroid*> asteroids;
	Point topLeft;
	Point bottomRight;
	bool isOnScreen(const Point & point);
	void advanceBullets();
	void advanceAsteroids();
	void handleCollisions();
	void cleanUpZombies();
	void createAsteroid(Asteroid &ast);
	void meteorShower();

};


#endif /* GAME_H */
