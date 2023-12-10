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

		//Level 1
		if (m_LM.getCurrentLevel() == 1)
		{
			if (counter == 0)
			{
				(*iter)->spawn(Vector2f(750, 550), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(750, 550));
			}
			if (counter == 1)
			{
				(*iter)->spawn(Vector2f(2500, 200), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2500, 200));
			}
			if (counter == 2)
			{
				(*iter)->spawn(Vector2f(5000, 150), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(5000, 150));
			}
			if (counter == 3)
			{
				(*iter)->spawn(Vector2f(5100, 500), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(5100, 500));
			}
			if (counter == 4)
			{
				(*iter)->spawn(Vector2f(2500, 400), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2500, 400));
			}
			if (counter == 5)
			{
				(*iter)->spawn(Vector2f(2400, 700), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2400, 700));
			}
			if (counter == 6)
			{
				(*iter)->spawn(Vector2f(4650, 800), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(4650, 800));
			}
			if (counter == 7)
			{
				(*iter)->spawn(Vector2f(5450, 1000), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(5450, 1000));
			}
			if (counter == 8)
			{	
				(*iter)->spawn(Vector2f(2950, 1050), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(5450, 1050));
			}
			if (counter == 9)
			{
				(*iter)->spawn(Vector2f(5450, 1000), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(5450, 1000));
			}
		}
		//Level 2
		else if (m_LM.getCurrentLevel() == 2)
		{
			if (counter == 0)
			{
				(*iter)->spawn(Vector2f(750, 550), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(750, 550));
			}
			if (counter == 1)
			{
				(*iter)->spawn(Vector2f(2500, 200), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2500, 200));
			}
			if (counter == 2)
			{
				(*iter)->spawn(Vector2f(2500, 150), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(5000, 150));
			}
			if (counter == 3)
			{
				(*iter)->spawn(Vector2f(800, 400), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(800, 400));
			}
			if (counter == 4)
			{
				(*iter)->spawn(Vector2f(2500, 400), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2500, 400));
			}
			if (counter == 5)
			{
				(*iter)->spawn(Vector2f(2400, 700), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2400, 700));
			}
			if (counter == 6)
			{
				(*iter)->spawn(Vector2f(2500, 800), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2500, 800));
			}
			if (counter == 7)
			{
				(*iter)->spawn(Vector2f(3000, 1000), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(3000, 1000));
			}
			if (counter == 8)
			{
				(*iter)->spawn(Vector2f(2950, 1000), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2950, 1000));
			}
			if (counter == 9)
			{
				(*iter)->spawn(Vector2f(3000, 1500), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(3000, 1500));
			}
		}
		//Level 3
		else if (m_LM.getCurrentLevel() == 3)
		{
			if (counter == 0)
			{
				(*iter)->spawn(Vector2f(2050, 200), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2050, 200));
			}
			if (counter == 1)
			{
				(*iter)->spawn(Vector2f(2050, 500), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2050, 500));
			}
			if (counter == 2)
			{
				(*iter)->spawn(Vector2f(2500, 300), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2500, 300));
			}
			if (counter == 3)
			{
				(*iter)->spawn(Vector2f(2050, 200), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2050, 200));
			}
			if (counter == 4)
			{
				(*iter)->spawn(Vector2f(2200, 850), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2200, 850));
			}
			if (counter == 5)
			{
				(*iter)->spawn(Vector2f(2150, 800), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2200, 800));
			}
			if (counter == 6)
			{
				(*iter)->spawn(Vector2f(2300, 900), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2300, 900));
			}
			if (counter == 7)
			{
				(*iter)->spawn(Vector2f(2050, 200), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2050, 200));
			}
			if (counter == 8)
			{
				(*iter)->spawn(Vector2f(2050, 200), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2050, 200));
			}
			if (counter == 9)
			{
				(*iter)->spawn(Vector2f(2050, 200), GRAVITY);
				(*iter)->SetPatrolPoint(Vector2f(2050, 200));
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