/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;


#define OFF_SCREEN_BORDER_AMOUNT 5

#define STATE_HOME 0
#define STATE_GAME 1
#define STATE_DEAD 2
#define LARGE 1
#define MEDIUM 2
#define SMALL 3

int state = STATE_HOME;
static int i = 2;
static int showerStart = 0;
/***************************************
* GAME CONSTRUCTOR
***************************************/
Game::Game(Point tl, Point br)
	: topLeft(tl), bottomRight(br)
{
	score = 0;
	for (int a = 0; a < 5; a++)
	{
		Point randomP(random(-200, 200), random(-200, 200));
		largeAsteroid * newAsteroid;
		newAsteroid = new largeAsteroid;
		newAsteroid->fire(randomP, random(0, 360));
		asteroids.push_back(newAsteroid);
	}
}

/****************************************
* GAME DESTRUCTOR
****************************************/
Game :: ~Game()
{


}

/***************************************
* GAME :: ADVANCE
* advance the game one unit of time
***************************************/
void Game::advance()
{
	if (state == STATE_GAME)
	{
		showerStart++;
		if (showerStart == 100)
			meteorShower();
		advanceBullets();
		advanceAsteroids();
		ship.advance();
		handleCollisions();
		cleanUpZombies();
		if (!isOnScreen(ship.getPoint()))
		{
			Point shipPoint = ship.getPoint();
			if (shipPoint.getX() < -200)
				ship.setShipX(200);
			else if (shipPoint.getX() > 200)
				ship.setShipX(-200);
			if (shipPoint.getY() < -200)
				ship.setShipY(200);
			else if (shipPoint.getY() > 200)
				ship.setShipY(-200);
		}
	}
}

/***************************************
* GAME :: METEORSHOWER
* Special Code that spawns a meteor shower
***************************************/
void Game::meteorShower()
{
	for (int a = 0; a < 5; a++)
	{
		Point randomP(-200, random(-200, 200));
		largeAsteroid * newAsteroid;
		newAsteroid = new largeAsteroid;
		newAsteroid->fire(randomP, 500);
		asteroids.push_back(newAsteroid);
	}
}

/***************************************
* GAME :: ADVANCE BULLETS
* Go through each bullet and advance it.
***************************************/
void Game::advanceBullets()
{
	// Move each of the bullets forward if it is alive
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			// this bullet is alive, so tell it to move forward
			bullets[i].advance();

		}
	}
}

/***************************************
* GAME :: ADVANCE ASTEROIDS
* Go through each asteroid and advance it.
***************************************/
void Game::advanceAsteroids()
{
	// Move each of the bullets forward if it is alive
	for (int i = 0; i < asteroids.size(); i++)
	{
		if (asteroids[i]->isAlive())
		{
			// this bullet is alive, so tell it to move forward
			asteroids[i]->advance();

		}
	}
}

/**************************************************************************
* GAME :: IS ON SCREEN
* Determines if a given point is on the screen.
**************************************************************************/
bool Game::isOnScreen(const Point & point)
{
	return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
* GAME :: HANDLE COLLISIONS
* Check for a collision between a bird and a bullet.
**************************************************************************/
void Game::handleCollisions()
{
	for (int j = 0; j < asteroids.size(); j++)
	{
		if (asteroids[j]->isAlive())
		{
			if ((asteroids[j]->getName() == LARGE &&
				getClosestDistance(ship, *asteroids[j]) < 16) ||
				(asteroids[j]->getName() == MEDIUM &&
					getClosestDistance(ship, *asteroids[j]) < 11) ||
					(asteroids[j]->getName() == SMALL &&
						getClosestDistance(ship, *asteroids[j]) < 9))
			{
				// the bullet is dead as well
				ship.kill();
				state = STATE_DEAD;
				asteroids[j]->kill();
			}
		}
	} // if bullet is alive
	// now check for a hit (if it is close enough to any live bullets)
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			// this bullet is alive, see if its too close

			// check if the bird is at this point (in case it was hit)

			for (int j = 0; j < asteroids.size(); j++)
			{
				if (asteroids[j]->isAlive())
				{
					if ((asteroids[j]->getName() == LARGE && 
						getClosestDistance(bullets[i], *asteroids[j]) < 16) || 
						(asteroids[j]->getName() == MEDIUM &&
						getClosestDistance(bullets[i], *asteroids[j]) < 11) ||
						(asteroids[j]->getName() == SMALL &&
						getClosestDistance(bullets[i], *asteroids[j]) < 9))
					{
						// the bullet is dead as well
						bullets[i].kill();
						asteroids[j]->kill();
						createAsteroid(*asteroids[j]);
						score += 100;
						
					}

				}
			} 

		} 
	}
}


/***************************************
* GAME :: CREATE ASTEROID
* Allocates memory and creates an asteroid
***************************************/
void Game::createAsteroid(Asteroid &ast)
{
	switch (ast.getName())
	{
	case(LARGE):
		for (int a = 0; a < 2; a++)
		{
			mediumAsteroid * newAsteroid;
			newAsteroid = new mediumAsteroid;
			if (a == 0)
				newAsteroid->fireLM1(ast.getPoint(), ast.getVelocity());	
			else
				newAsteroid->fireLM2(ast.getPoint(), ast.getVelocity());

			asteroids.push_back(newAsteroid);
		}
		smallAsteroid * newAsteroid;
		newAsteroid = new smallAsteroid;
		newAsteroid->fireLS(ast.getPoint(), ast.getVelocity());
		asteroids.push_back(newAsteroid);
		break;

	case(MEDIUM):
		for (int a = 0; a < 2; a++)
		{
			smallAsteroid * newAsteroid;
			newAsteroid = new smallAsteroid;
			if (a == 0)
				newAsteroid->fireMS1(ast.getPoint(), ast.getVelocity());
			else
				newAsteroid->fireMS2(ast.getPoint(), ast.getVelocity());
			asteroids.push_back(newAsteroid);
		}
		break;


	}
}

/***************************************
* GAME :: HANDLE INPUT
* accept input from the user
***************************************/
void Game::handleInput(const Interface & ui)
{

	switch (state)
	{
		case(STATE_HOME):
			if (ui.isSpace())
				state = STATE_GAME;
			break;

		case(STATE_GAME):
		{
			if (ui.isLeft())
			{
				ship.moveLeft();
			}

			if (ui.isRight())
			{
				ship.moveRight();
			}
			if (ui.isUp())
			{
				ship.thrust();
			}
			else ship.setThrust(false);

			if (ui.isSpace())
			{
				Bullet newBullet;
				newBullet.fire(ship.getPoint(), ship.getAngle(), ship.getVelocity());

				bullets.push_back(newBullet);
			}
		}
	}
}

/*********************************************
* GAME :: DRAW
* Draw everything on the screen
*********************************************/
void Game::draw(const Interface & ui)
{

	Point gameText(-80, 150);
	Point gameText2(-50, 1);
	Point shipPoint = ship.getPoint();
	switch (state)
	{
	case(STATE_HOME):
		drawText(gameText, "Welcome to Asteroids");
		drawText(gameText2, "Press SpaceBar");
		break;

	case(STATE_DEAD):
		drawText(gameText, "Loser");
		if (i < 100)
		{
			drawCircle(shipPoint, i);
			i = i + 10;
		}
		break;

	case(STATE_GAME):
		// Put the score on the screen
		//testAst.draw();
		Point scoreLocation;
		Point info;
		scoreLocation.setX(topLeft.getX() + 5);
		scoreLocation.setY(topLeft.getY() - 5);
		info.setX(topLeft.getX() + 5);
		info.setY(topLeft.getY() - 40);
		drawNumber(scoreLocation, score);
		if (showerStart > 50 && showerStart < 500)
			drawText(info, "DETECTED METEOR SHOWER");
		if (ship.isAlive())
			ship.draw();
		for (int i = 0; i < bullets.size(); i++)
		{
		//	if (bullets[i].isAlive())
		//	{
				bullets[i].draw();
			//}
			if (!isOnScreen(bullets[i].getPoint()))
			{
				Point bulletPoint = bullets[i].getPoint();
				if (bulletPoint.getX() < -200)
					bullets[i].setBulletX(200);
				else if (bulletPoint.getX() > 200)
					bullets[i].setBulletX(-200);
				if (bulletPoint.getY() < -200)
					bullets[i].setBulletY(200);
				else if (bulletPoint.getY() > 200)
					bullets[i].setBulletY(-200);
			}
		}
		for (int k = 0; k < asteroids.size(); k++)
		{
				asteroids[k]->draw();
			if (!isOnScreen(asteroids[k]->getPoint()))
			{
				Point asteroidPoint = asteroids[k]->getPoint();
				if (asteroidPoint.getX() < -215)
					asteroids[k]->setBulletX(215);
				else if (asteroidPoint.getX() > 215)
					asteroids[k]->setBulletX(-215);
				if (asteroidPoint.getY() < -215)
					asteroids[k]->setBulletY(215);
				else if (asteroidPoint.getY() > 215)
					asteroids[k]->setBulletY(-215);
			}
		}

	}
}


/**************************************************************************
* GAME :: CLEAN UP ZOMBIES
* Remove any dead objects (take bullets out of the list, deallocate bird)
**************************************************************************/
void Game::cleanUpZombies()
{


	// Look for dead bullets

	vector<Bullet>::iterator bulletIt = bullets.begin();
	while (bulletIt != bullets.end())
	{
		Bullet bullet = *bulletIt;
		// Asteroids Hint:
		// If we had a list of pointers, we would need this line instead:
		//Bullet* pBullet = *bulletIt;

		if (!bullet.isAlive())
		{
			// If we had a list of pointers, we would need to delete the memory here...


			// remove from list and advance
			bulletIt = bullets.erase(bulletIt);
		}
		else
		{
			++bulletIt; // advance
		}
	}

	vector<Asteroid*>::iterator asteroidIt = asteroids.begin();
	while (asteroidIt != asteroids.end())
	{
		Asteroid * asteroid = *asteroidIt;
		// Asteroids Hint:
		// If we had a list of pointers, we would need this line instead:
		//Bullet* pBullet = *bulletIt;

		if (!asteroid->isAlive())
		{
			// If we had a list of pointers, we would need to delete the memory here...


			// remove from list and advance
			asteroidIt = asteroids.erase(asteroidIt);
		}
		else
		{
			++asteroidIt; // advance
		}
	}

}

// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}


