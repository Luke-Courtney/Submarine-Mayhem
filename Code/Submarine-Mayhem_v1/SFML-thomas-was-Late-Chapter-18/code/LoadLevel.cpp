#include "Engine.h"

void Engine::loadLevel()
{
	list<Bob*>::const_iterator iter;
	counter=0;
	int type = 0;

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
		(*iter)->setType(type);
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
			if (counter == 3)
			{
				(*iter)->spawn(Vector2f(1222221, 173), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(1222221, 173));
			}
			if (counter == 4)
			{
				(*iter)->spawn(Vector2f(541, 573), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(541, 573));
			}
			if (counter == 5)
			{
				(*iter)->spawn(Vector2f(241, 1073), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(241, 1073));
			}
			if (counter == 6)
			{
				(*iter)->spawn(Vector2f(641, 2073), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(641, 2073));
			}
			if (counter == 7)
			{
				(*iter)->spawn(Vector2f(341, 3073), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(341, 3073));
			}
			if (counter == 8)
			{
				(*iter)->spawn(Vector2f(1041, 4073), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(1041, 4073));
			}
			if (counter == 9)
			{
				(*iter)->spawn(Vector2f(441, 5073), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(441, 5073));
			}
		}
		else if (m_LM.getCurrentLevel() == 2)
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
		counter++;
		type++;
		if(type >2)
		{ 
			type = 0;
		}
	}
	counter = 0;

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