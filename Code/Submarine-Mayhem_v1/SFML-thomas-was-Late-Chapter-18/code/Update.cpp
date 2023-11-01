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
		Time dt2;
		Clock clock;
		// Update Thomas
		m_Thomas.update(dtAsSeconds);

		// Update Bobs
		m_Bob0.update(dtAsSeconds);
		m_Bob1.update(dtAsSeconds);
		m_Bob2.update(dtAsSeconds);

		healthPickup.update(dtAsSeconds);
		SpeedBoost.update(dtAsSeconds);


		//Pickups from bob0
		if (healthPickup.spawnNum != 3)
		{
			if ((m_Bob0.getHealth() < 1))
			{
				healthPickup.spawnNum = 2;
			}
		}
		if (healthPickup.spawnNum == 2)
		{
			healthPickup.spawnNum = rand() % 2 + 4;
			if (healthPickup.spawnNum == 4)
			{
				healthPickup.spawn(Vector2f(m_Bob0.getCenter().x, m_Bob0.getCenter().y), GRAVITY);
			}
			if (healthPickup.spawnNum == 5)
			{
				SpeedBoost.spawn(Vector2f(m_Bob0.getCenter().x, m_Bob0.getCenter().y), GRAVITY);
			}

			m_Bob0.die();
			healthPickup.spawnNum = 3;
		}

		//Pickups from bob1
		if (healthPickup.spawnNum != 3)
		{
			if ((m_Bob1.getHealth() < 1))
			{
				healthPickup.spawnNum = 2;
			}
		}
		if (healthPickup.spawnNum == 2)
		{
			healthPickup.spawnNum = rand() % 2 + 4;
			if (healthPickup.spawnNum == 4)
			{
				healthPickup.spawn(Vector2f(m_Bob1.getCenter().x, m_Bob1.getCenter().y), GRAVITY);
			}
			if (healthPickup.spawnNum == 5)
			{
				SpeedBoost.spawn(Vector2f(m_Bob1.getCenter().x, m_Bob1.getCenter().y), GRAVITY);
			}

			m_Bob1.die();
			healthPickup.spawnNum = 3;
		}

		//Pickups from bob2
		if (healthPickup.spawnNum != 3)
		{
			if ((m_Bob2.getHealth() < 1))
			{
				healthPickup.spawnNum = 2;
			}
		}
		if (healthPickup.spawnNum == 2)
		{
			healthPickup.spawnNum = rand() % 2 + 4;
			if (healthPickup.spawnNum == 4)
			{
				healthPickup.spawn(Vector2f(m_Bob2.getCenter().x, m_Bob2.getCenter().y), GRAVITY);
			}
			if (healthPickup.spawnNum == 5)
			{
				SpeedBoost.spawn(Vector2f(m_Bob2.getCenter().x, m_Bob2.getCenter().y), GRAVITY);
			}

			m_Bob2.die();
			healthPickup.spawnNum = 3;
		}

		//if (SpeedBoost.BoostTimeEnd == false)
		//{
		//	dt2 = clock.restart();
		//	SpeedBoost.boostTime -= dt2.asSeconds();

		//}
		//if (SpeedBoost.boostTime <= 0)
		//{
		//	SpeedBoost.BoostTimeEnd = true;
		//	m_Thomas.setSpeed(4);
		//}

		// Detect collisions and see if characters have reached the goal tile
		// The second part of the if condition is only executed
		// when thomas is touching the home tile
		if (detectCollisions(m_Thomas) && detectCollisions(m_Bob0) || detectCollisions(m_Thomas) && detectCollisions(m_Bob1) || detectCollisions(m_Thomas) && detectCollisions(m_Bob2))
		{
			// New level required
			m_NewLevelRequired = true;

			// Play the reach goal sound
			m_SM.playReachGoal();

		}
		else
		{
			// Run bobs collision detection
			detectCollisions(m_Bob0);
			detectCollisions(m_Bob1);
			detectCollisions(m_Bob2);
		}

		// Count down the time the player has left
		m_TimeRemaining -= dtAsSeconds;

		// Have Thomas and Bob run out of time?
		if (m_TimeRemaining <= 0)
		{
			m_NewLevelRequired = true;
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
		m_RightView.setCenter(m_Bob0.getCenter());
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
			m_MainView.setCenter(m_Bob0.getCenter());
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

		// Update the time text
		ssTime << (int)m_TimeRemaining;
		m_Hud.setTime(ssTime.str());

		// Update the level text
		ssLevel << "Level:" << m_LM.getCurrentLevel();
		m_Hud.setLevel(ssLevel.str());

		m_FramesSinceLastHUDUpdate = 0;
	}

	// Update the particles
	if (m_PS.running())
	{
		m_PS.update(dtAsSeconds);
	}
}// End of update function