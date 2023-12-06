#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	
	
		// Measure time
		dt = clock.restart();
		



		

	

	if (m_NewLevelRequired)
	{
		 
			// Load a level
			loadLevel();
		
		
	}

	if (m_Playing)
	{
		list<Bob*>::const_iterator iter;
		// Update Thomas
		m_Thomas.update(dtAsSeconds);

		// Update Bobs
		m_Bob0->update(dtAsSeconds);
		m_Bob1->update(dtAsSeconds);
		m_Bob2->update(dtAsSeconds);

		//Update Pickups
		healthPickup.update(dtAsSeconds);
		MaxSpeed.update(dtAsSeconds);
		SpeedBoost.update(dtAsSeconds);
		healthPickup2.update(dtAsSeconds);

#		//Pickups for Bob0
		for (iter = Enemy.begin(); iter != Enemy.end(); ++iter)
		{
			if ((*iter)->getHealth() < 1 && (*iter)->isAlive())
			{
				healthPickup.spawnNum = rand() % 7;
				if (healthPickup.spawnNum >=0 && healthPickup.spawnNum <= 1)
				{
					healthPickup.spawn(Vector2f((*iter)->getCenter().x, (*iter)->getCenter().y), GRAVITY);
				}
				if (healthPickup.spawnNum >= 2 && healthPickup.spawnNum <= 3)
				{
					MaxSpeed.spawn(Vector2f((*iter)->getCenter().x, (*iter)->getCenter().y), GRAVITY);
				}
				if (healthPickup.spawnNum >= 4 && healthPickup.spawnNum <= 5)
				{
					SpeedBoost.spawn(Vector2f((*iter)->getCenter().x, (*iter)->getCenter().y), GRAVITY);
				}
				if (healthPickup.spawnNum == 6)
				{
					healthPickup2.spawn(Vector2f((*iter)->getCenter().x, (*iter)->getCenter().y), GRAVITY);
				}
				(*iter)->die();
			}
		}

		// Detect collisions and see if characters have reached the goal tile
		// The second part of the if condition is only executed
		// when thomas is touching the home tile
		if (detectCollisions(m_Thomas) && detectCollisions(*m_Bob0) || detectCollisions(m_Thomas) && detectCollisions(*m_Bob1) || detectCollisions(m_Thomas) && detectCollisions(*m_Bob2))
		{
			// New level required
			
			m_NewLevelRequired = true;

			// Play the reach goal sound
			m_SM.playReachGoal();

		}
		else
		{
			// Run bobs collision detection
			detectCollisions(*m_Bob0);
			detectCollisions(*m_Bob1);
			detectCollisions(*m_Bob2);
		}

		// Where is the mouse pointer
		mouseScreenPosition = Mouse::getPosition();

		// Convert mouse position to world coordinates of mainView
		mouseWorldPosition = m_Window.mapPixelToCoords(Mouse::getPosition(), m_MainView);
		
		// Fire a bullet
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{

			if (m_GameTimeTotal.asMilliseconds()
				- lastPressed.asMilliseconds()
					> 1000 / fireRate && bulletsInClip > 0)
			{

				// Pass the centre of the player and the centre of the crosshair
				// to the shoot function
				bullets[currentBullet].shoot(
					(m_Thomas.getCenter().x + 50), m_Thomas.getCenter().y,
					mouseWorldPosition.x, mouseWorldPosition.y);

				currentBullet++;
				if (currentBullet > 99)
				{
					currentBullet = 0;
				}
				lastPressed = m_GameTimeTotal;
				//shoot.play();
				bulletsInClip--;
			}

		}// End fire a bullet

		float Bob0shoot = (m_Bob0->getCenter().x, m_Bob0->getCenter().y);
		float Bob1shoot = (m_Bob1->getCenter().x, m_Bob1->getCenter().y);
		float Bob2shoot = (m_Bob2->getCenter().x, m_Bob2->getCenter().y);

		//Enemies shoot thomas
		float distance = abs((m_Bob0->getCenter().x - m_Thomas.getCenter().x) + (m_Bob0->getCenter().y - m_Thomas.getCenter().y));
		float distance1 = abs((m_Bob1->getCenter().x - m_Thomas.getCenter().x) + (m_Bob1->getCenter().y - m_Thomas.getCenter().y));
		float distance2 = abs((m_Bob2->getCenter().x - m_Thomas.getCenter().x) + (m_Bob2->getCenter().y - m_Thomas.getCenter().y));

		if (distance < 10)
		{
			//Shoot function takes in start pos and target pos
			bullets[currentBullet].shoot(m_Bob0->getCenter().x, m_Bob0->getCenter().y, m_Thomas.getCenter().x, m_Thomas.getCenter().y);
		}
		else if (distance1 < 10)
		{
			bullets[currentBullet].shoot(m_Bob1->getCenter().x, m_Bob1->getCenter().y, m_Thomas.getCenter().x, m_Thomas.getCenter().y);
		}
		else if (distance2 < 10)
		{
			bullets[currentBullet].shoot(m_Bob2->getCenter().x, m_Bob2->getCenter().y, m_Thomas.getCenter().x, m_Thomas.getCenter().y);
		}
		
		// Update any bullets that are in - flight
		for (int i = 0; i < 100; i++)
		{// && enemyBullets[i].isInFlight()
			if (bullets[i].isInFlight())
			{
				bullets[i].update(dtAsSeconds);
				//enemyBullets[i].update(dtAsSeconds);
			}
		}
		
		// Reloading
		if (Keyboard::isKeyPressed(Keyboard::R))
		{
			if (bulletsSpare >= clipSize)
			{
				// Plenty of bullets. Reload.
				bulletsInClip = clipSize;
				bulletsSpare -= clipSize;
			}
			else if (bulletsSpare > 0)
			{
				// Only few bullets left
				bulletsInClip = bulletsSpare;
				bulletsSpare = 0;
			}
			
		}

		if (Keyboard::isKeyPressed(Keyboard::J))
		{
			plusHealth();

		}

		if (Keyboard::isKeyPressed(Keyboard::I))
		{
			minusHealth();
		}
		/*
		/Have any enemies been shot?
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isInFlight() && m_Bob0.isAlive() || bullets[i].isInFlight() && m_Bob1.isAlive() ||
				bullets[i].isInFlight() && m_Bob2.isAlive())
			{
				if (bullets[i].getPosition().intersects(m_Bob0.getPosition()) || bullets[i].getPosition().intersects(m_Bob1.getPosition()) ||
					bullets[i].getPosition().intersects(m_Bob2.getPosition()))
				{
					// Stop the bullet
					bullets[i].stop();

					// Register the hit and see if it was a kill
					//if (m_Bob0.damage() || m_Bob1.damage() || m_Bob2.damage()) {
						// Not just a hit but a kill too
						//die();
					//}
				}
			}
		}
		*/

		// size up the time bar
		timeBar.setSize(Vector2f(timeBarWidthPerSecond *
			timeRemaining, timeBarHeight));

		timeBar.setPosition(m_Thomas.getCenter() + offset);

		// Subtract from the amount of time remaining

		if (timeRemaining > 0)
		{

			timeRemaining = timeRemaining - (dt.asSeconds()/20);
		}

		//if oxygen runs out display a message
		if (timeRemaining < 1)
		{

			oxygenGone = true;
		}

		

	}// End if playing

	
	 /*
	 // Check if a fire sound needs to be played
	vector<Vector2f>::iterator it;

	// Iterate through the vector of Vector2f objects
	for (it = m_FireEmitters.begin(); it != m_FireEmitters.end(); it++)
	{
		// Where is this emitter?
		// Store the location in pos
		float posX = (*it).x;
		float posY = (*it).y;

		// is the emiter near the player?
		// Make a 500 pixel rectangle around the emitter
		FloatRect localRect(posX - 250, posY - 250, 500, 500);

		// Is the player inside localRect?
		if (m_Thomas.getPosition().intersects(localRect))
		{
			// Play the sound and pass in the location as well
			m_SM.playFire(Vector2f(posX, posY), m_Thomas.getCenter());
		}
	}
	*/

	m_MainView.setCenter(m_Thomas.getCenter());
		
	// Time to update the HUD?
	// Increment the number of frames since the last HUD calculation
	m_FramesSinceLastHUDUpdate++;

	// Update the HUD every m_TargetFramesPerHUDUpdate frames
	if (m_FramesSinceLastHUDUpdate > m_TargetFramesPerHUDUpdate) 
	{
		// Update game HUD text
		stringstream ssTime;
		stringstream ssLevel;
		stringstream ssAmmo;

		// Update the level text
		ssLevel << "Level:" << m_LM.getCurrentLevel();
		m_Hud.setLevel(ssLevel.str());

		// Update the ammo text
		ssAmmo << "Ammo:" << m_LM.getCurrentLevel();
		ssAmmo << bulletsInClip << "/" << bulletsSpare;
		m_Hud.setAmmo(ssAmmo.str());

		m_FramesSinceLastHUDUpdate = 0;
	}

	// Update the particles
	if (m_PS.running())
	{
		m_PS.update(dtAsSeconds);
	}
}// End of update function