#include "Engine.h"

void Engine::loadLevel()
{
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

	// How long is this new time limit
	m_TimeRemaining = m_LM.getTimeLimit();

	// Spawn Thomas and Bob
	m_Thomas.spawn(m_LM.getStartPosition(), GRAVITY);

	m_Bob0.setType(0);
	m_Bob0.spawn(Vector2f(750, 450), GRAVITY);

	m_Bob1.setType(1);
	m_Bob1.spawn(Vector2f(3700, 650), GRAVITY);

	m_Bob2.setType(2);
	m_Bob2.spawn(Vector2f(1800, 900), GRAVITY);

	healthPickup.spawn(Vector2f(6900, 1500), GRAVITY);
	MaxSpeed.spawn(Vector2f(6900, 1600), GRAVITY);
	healthPickup2.spawn(Vector2f(6900, 1700), GRAVITY);
	SpeedBoost.spawn(Vector2f(6900, 1600), GRAVITY);
	

	// Make sure this code isn't run again
	m_NewLevelRequired = false;
}