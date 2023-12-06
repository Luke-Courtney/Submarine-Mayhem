#include "Engine.h"

void Engine::loadLevel()
{
	list<Bob*>::const_iterator iter;
	counter=0;

	m_Playing = false;

	// Delete the previously allocated memory
	for (int i = 0; i < m_LM.getLevelSize().y; ++i)
	{
		delete[] m_ArrayLevel[i];

	}
	delete[] m_ArrayLevel;

	// Load the next 2d array with the map for the level
	// And repopulate the vertex array as well
	m_ArrayLevel = m_LM.nextLevel(m_VALevel);

	// Prepare the sound emitters
	populateEmitters(m_FireEmitters, m_ArrayLevel);

	// Spawn Thomas and Bob
	m_Thomas.spawn(m_LM.getStartPosition(), GRAVITY);

	for (iter = Enemy.begin(); iter != Enemy.end(); ++iter)
	{
		(*iter)->setType(counter);
		if (m_LM.getCurrentLevel() == 1)
		{
			if (counter == 0)
			{
				(*iter)->spawn(Vector2f(750, 450), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(750, 450));
			}
			if (counter == 1)
			{
				(*iter)->spawn(Vector2f(3700, 650), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(3700, 650));
			}
			if (counter == 2)
			{
				(*iter)->spawn(Vector2f(1800, 900), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(1800, 900));
			}
		}
		else if (m_LM.getCurrentLevel() == 2)
		{
			if (counter == 0)
			{
				(*iter)->spawn(Vector2f(750, 450), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(750, 450));
				counter++;
			}
			if (counter == 1)
			{
				(*iter)->spawn(Vector2f(3700, 650), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(3700, 650));
				counter++;
			}
			if (counter == 2)
			{
				(*iter)->spawn(Vector2f(1800, 900), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(1800, 900));
				counter++;
			}
		}
		counter=0;
	}

	healthPickup.spawn(Vector2f(7900, 1500), GRAVITY);
	MaxSpeed.spawn(Vector2f(7900, 1600), GRAVITY);
	healthPickup2.spawn(Vector2f(7900, 1700), GRAVITY);
	SpeedBoost.spawn(Vector2f(7900, 1600), GRAVITY);
	BulletSpeed.spawn(Vector2f(7900, 1600), GRAVITY);
	BulletFireRate.spawn(Vector2f(7900, 1600), GRAVITY);
	BulletDMG.spawn(Vector2f(7900, 1600), GRAVITY);
	

	// Make sure this code isn't run again
	m_NewLevelRequired = false;
}