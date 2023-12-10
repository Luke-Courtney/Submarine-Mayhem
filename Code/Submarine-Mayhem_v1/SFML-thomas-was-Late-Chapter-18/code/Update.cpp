#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
		// Measure time
		dt = clock.restart();
		
	

	if (m_NewLevelRequired)
	{
		// Load a level
		loadLevel();

		//Start playing music on level load
		m_SM.playMusic();
	}

	if (m_Playing)
	{

		list<Bob*>::const_iterator iter;
		// Update Thomas
		m_Thomas.update(dtAsSeconds);

		// Update Bobs
		for (iter = Enemy.begin(); iter != Enemy.end(); ++iter)
		{
			(*iter)->update(dtAsSeconds);
		}

		//Update Pickups
		healthPickup.update(dtAsSeconds);
		MaxSpeed.update(dtAsSeconds);
		SpeedBoost.update(dtAsSeconds);
		BulletFireRate.update(dtAsSeconds);
		BulletSpeed.update(dtAsSeconds);
		BulletDMG.update(dtAsSeconds);

#		//Pickups for Bob0
		for (iter = Enemy.begin(); iter != Enemy.end(); ++iter)
		{
			if ((*iter)->getHealth() < 1 && (*iter)->isAlive())
			{
				healthPickup.spawnNum = rand() % 13;
				if (healthPickup.spawnNum >= 0 && healthPickup.spawnNum <= 1)
				{
					healthPickup.spawn(Vector2f((*iter)->getCenter().x, (*iter)->getCenter().y), GRAVITY);
				}
				else if (healthPickup.spawnNum >= 2 && healthPickup.spawnNum <= 3)
				{
					MaxSpeed.spawn(Vector2f((*iter)->getCenter().x, (*iter)->getCenter().y), GRAVITY);
				}
				else if (healthPickup.spawnNum >= 4 && healthPickup.spawnNum <= 5)
				{
					SpeedBoost.spawn(Vector2f((*iter)->getCenter().x, (*iter)->getCenter().y), GRAVITY);
				}
				else if (healthPickup.spawnNum >= 6 && healthPickup.spawnNum <= 7)
				{
					BulletFireRate.spawn(Vector2f((*iter)->getCenter().x, (*iter)->getCenter().y), GRAVITY);
				}
				else if (healthPickup.spawnNum >= 8 && healthPickup.spawnNum <= 9)
				{
					BulletSpeed.spawn(Vector2f((*iter)->getCenter().x, (*iter)->getCenter().y), GRAVITY);
				}
				else if (healthPickup.spawnNum >= 10 && healthPickup.spawnNum <= 11)
				{
					BulletDMG.spawn(Vector2f((*iter)->getCenter().x, (*iter)->getCenter().y), GRAVITY);
				}
				else if (healthPickup.spawnNum == 12)
				{
					healthPickup2.spawn(Vector2f((*iter)->getCenter().x, (*iter)->getCenter().y), GRAVITY);
				}
				(*iter)->die();
			}
		}

		// Detect collisions and see if characters have reached the goal tile
		// The second part of the if condition is only executed
		// when thomas is touching the home tile
		if (detectCollisions(m_Thomas))
		{
			// New level required

			m_NewLevelRequired = true;

			// Play the reach goal sound
			m_SM.playReachGoal();

		}
		else
		{
			// Run bobs collision detection
			for (iter = Enemy.begin(); iter != Enemy.end(); ++iter)
			{
				detectCollisions(*(*iter));
			}
		}

		// Where is the mouse pointer
		mouseScreenPosition = Mouse::getPosition();

		// Convert mouse position to world coordinates of mainView
		mouseWorldPosition = m_Window.mapPixelToCoords(Mouse::getPosition(), m_MainView);
		
		// Set the crosshair to the mouse world location
		spriteCrosshair.setPosition(mouseWorldPosition);

		// Fire a bullet
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{

			if (m_GameTimeTotal.asMilliseconds()
				- lastPressed.asMilliseconds()
			> 1000 / fireRate && bulletsInClip > 0)
			{
				// Pass the centre of the player and the centre of the crosshair
				// to the shoot function
				if (m_Thomas.isFlipped == true)
				{
					bullets[currentBullet].shoot(
						(m_Thomas.getCenter().x - 120), m_Thomas.getCenter().y,
						mouseWorldPosition.x, mouseWorldPosition.y);
					cout << m_Thomas.flipped;
				}
				else
				{
					bullets[currentBullet].shoot(
						(m_Thomas.getCenter().x + 30), m_Thomas.getCenter().y,
						mouseWorldPosition.x, mouseWorldPosition.y);
				}
				
				currentBullet++;
				if (currentBullet > 500)
				{
					currentBullet = 0;
				}
				lastPressed = m_GameTimeTotal;
				m_SM.playShootSound();
				bulletsInClip--;
			}

		}// End fire a bullet

		//Enemies shoot thomas
		for (iter = Enemy.begin(); iter != Enemy.end(); ++iter)
		{
			float distance = abs((*iter)->getCenter().x - m_Thomas.getCenter().x + (*iter)->getCenter().y - m_Thomas.getCenter().y);

			if (distance < 10)
			{
				if (m_GameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / EfireRate && EbulletsInClip > 0)
				{
					//Shoot function takes in start pos and target pos
					Ebullets[EcurrentBullet].shoot((*iter)->getCenter().x, (*iter)->getCenter().y, m_Thomas.getCenter().x, m_Thomas.getCenter().y);
					EcurrentBullet++;
					if (EcurrentBullet > 500)
					{
						EcurrentBullet = 0;
					}
					lastPressed = m_GameTimeTotal;
					m_SM.playShootSound();
					EbulletsInClip--;
				}
			}
		}
		
		// Update any bullets that are in flight
		for (int i = 0; i < 500; i++)
		{// && enemyBullets[i].isInFlight()
			if (bullets[i].isInFlight())
			{
				bullets[i].update(dtAsSeconds);
			}
		}
		for (int i = 0; i < 500; i++)
		{// && enemyBullets[i].isInFlight()
			if (Ebullets[i].isInFlight())
			{
				Ebullets[i].update(dtAsSeconds);
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
		//ssAmmo << "Ammo:" << m_LM.getCurrentLevel();
		//ssAmmo << bulletsInClip << "/" << bulletsSpare;
		//m_Hud.setAmmo(ssAmmo.str());

		m_FramesSinceLastHUDUpdate = 0;
	}

	// Update the particles
	if (m_PS.running())
	{
		m_PS.update(dtAsSeconds);
	}
}// End of update function