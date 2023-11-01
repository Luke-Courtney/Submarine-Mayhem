#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	if (m_NewLevelRequired)
	{
		// These calls to spawn will be moved to a new
		// LoadLevel function soon
		// Spawn Thomas and Bob
		//m_Thomas.spawn(Vector2f(0,0), GRAVITY);
		//m_Bob.spawn(Vector2f(100, 0), GRAVITY);

		// Make sure spawn is called only once
		//m_TimeRemaining = 10;
		//m_NewLevelRequired = false;

		// Load a level
		loadLevel();
		
	}

	if (m_Playing)
	{
		// Update Thomas
		m_Thomas.update(dtAsSeconds);

		// Update Bob
		m_Bob.update(dtAsSeconds);

		// Detect collisions and see if characters have reached the goal tile
		// The second part of the if condition is only executed
		// when thomas is touching the home tile
		if (detectCollisions(m_Thomas) && detectCollisions(m_Bob))
		{
			// New level required
			m_NewLevelRequired = true;

			// Play the reach goal sound
			m_SM.playReachGoal();

		}
		else
		{
			// Run bobs collision detection
			detectCollisions(m_Bob);
		}

		// Count down the time the player has left
		m_TimeRemaining -= dtAsSeconds;

		// Have Thomas and Bob run out of time?
		if (m_TimeRemaining <= 0)
		{
			m_NewLevelRequired = true;
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
					m_Thomas.getCenter().x, m_Thomas.getCenter().y,
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
		
		// Update any bullets that are in - flight
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isInFlight())
			{
				bullets[i].update(dtAsSeconds);
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
	}// End if playing

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
		
	// Set the appropriate view around the appropriate character
	if (m_SplitScreen)
	{
		m_LeftView.setCenter(m_Thomas.getCenter());
		m_RightView.setCenter(m_Bob.getCenter());
	}
	else
	{
		// Centre full screen around appropriate character
		if (m_Character1)
		{
			m_MainView.setCenter(m_Thomas.getCenter());
		}
		else
		{
			m_MainView.setCenter(m_Bob.getCenter());
		}
	}

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

		// Update the time text
		ssTime << (int)m_TimeRemaining;
		m_Hud.setTime(ssTime.str());

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