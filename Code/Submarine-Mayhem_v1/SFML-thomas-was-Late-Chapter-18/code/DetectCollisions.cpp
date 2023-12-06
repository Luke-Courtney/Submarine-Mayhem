#include "Engine.h"
#include "Bob.h"
#include <iostream>

bool Engine::detectCollisions(PlayableCharacter& character)
{
	bool reachedGoal = false;
	// Make a rect for all his parts
	FloatRect detectionZone = character.getPosition();

	// Make a FloatRect to test each block
	FloatRect block;

	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	// Build a zone around thomas to detect collisions
	int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
	int startY = (int)(detectionZone.top / TILE_SIZE) - 1;
	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;

	// Thomas is quite tall so check a few tiles vertically
	int endY = (int)(detectionZone.top / TILE_SIZE) + 2;

	// Make sure we don't test positions lower than zero
	// Or higher than the end of the array
	if (startX < 0)startX = 0;
	if (startY < 0)startY = 0;
	if (endX >= m_LM.getLevelSize().x)
		endX = m_LM.getLevelSize().x;
	if (endY >= m_LM.getLevelSize().y)
		endY = m_LM.getLevelSize().y;

	// Has the character fallen out of the map?
	FloatRect level(0, 0, m_LM.getLevelSize().x * TILE_SIZE, m_LM.getLevelSize().y * TILE_SIZE);
	if (!character.getPosition().intersects(level))
	{
		//respawn the character
		//character.spawn(m_LM.getStartPosition(), GRAVITY);
	}

	//Has thomas fallen out of map?
	if (!m_Thomas.getPosition().intersects(level))
	{
		m_Thomas.spawn(m_LM.getStartPosition(), GRAVITY);
	}
	

	//Detect thomas collisions with enemy
	if (m_Thomas.getPosition().intersects(m_Bob0->getPosition()) || m_Thomas.getPosition().intersects(m_Bob1->getPosition()) || m_Thomas.getPosition().intersects(m_Bob2->getPosition()))
	{
		//Collision detected
		character.spawn(m_LM.getStartPosition(), GRAVITY);
		m_Thomas.health--; //thomas loses health when colliding with enemy
	}

	//Check if bullet collide enemy or player
	for (int i = 0; i < 100; i++)
	{
		if (bullets[i].isInFlight())
		{
			if (bullets[i].getPosition().intersects(m_Bob0->getPosition()) && m_Bob0->isAlive())
			{
				//stop the bullet
				bullets[i].stop();
				//enemy take damage
				m_Bob0->damage(1);
			}
			else if (bullets[i].getPosition().intersects(m_Bob1->getPosition()) && m_Bob1->isAlive())
			{
				bullets[i].stop();
				m_Bob1->damage(1);
			}
			else if (bullets[i].getPosition().intersects(m_Bob2->getPosition()) && m_Bob2->isAlive())
			{
				bullets[i].stop();
				m_Bob2->damage(1);
			}
			/*else if (bullets[i].getPosition().intersects(m_Thomas.getPosition()))
			{
				bullets[i].stop();
				character.spawn(m_LM.getStartPosition(), GRAVITY);
			}*/
		}

	}

	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			// Initialize the starting position of the current block
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;


			// Has character been burnt or drowned?
			if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
			{
				if (character.getPosition().intersects(block))
				{
					character.spawn(m_LM.getStartPosition(), GRAVITY);
					// Which sound should be played?
					if (m_ArrayLevel[y][x] == 2)// Fire, ouch!
					{
						// Play a sound
						m_SM.playFallInFire();

					}
					else // Water
					{
						// Play a sound
						m_SM.playFallInWater();
					}
				}
			}


			// Is character colliding with a regular block
			if (m_ArrayLevel[y][x] == 1)
			{

				if (character.getRight().intersects(block))
				{
					character.stopRight(block.left);
				}
				else if (character.getLeft().intersects(block))
				{
					character.stopLeft(block.left);
				}


				if (character.getFeet().intersects(block))
				{
					character.stopFalling(block.top);
				}
				else if (character.getHead().intersects(block))
				{
					character.stopClimbing(block.top);
				}
			}

			//collsion for player and Pickup
			if (m_Thomas.getPosition().intersects
			(healthPickup.getPosition()))
			{
				healthPickup.spawn(Vector2f(6900, 1500), GRAVITY);
				m_Thomas.setHealth(healthPickup.gotIt());
			}
			
			if (m_Thomas.getPosition().intersects
			(healthPickup2.getPosition()))
			{
				healthPickup2.spawn(Vector2f(6900, 1500), GRAVITY);
				m_Thomas.setHealth(healthPickup2.gotIt());
			}

			if (m_Thomas.getPosition().intersects
			(MaxSpeed.getPosition()))
			{
				MaxSpeed.spawn(Vector2f(6900, 1500), GRAVITY);
				m_Thomas.setMaxSpeed(MaxSpeed.gotIt());
			}
			if (m_Thomas.getPosition().intersects
			(SpeedBoost.getPosition()))
			{
				SpeedBoost.spawn(Vector2f(6900, 1500), GRAVITY);
				m_Thomas.setMaxSpeed(SpeedBoost.gotIt());
			}



			// More collision detection here once we have learned about particle effects
			// Has the characters' feet touched fire or water?
			// If so, start a particle effect
			// Make sure this is the first time we have detected this
			// by seeing if an effect is already running			
			if (!m_PS.running()) {
				if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
				{
					if (character.getFeet().intersects(block))
					{
						// position and start the particle system
						m_PS.emitParticles(character.getCenter());

					}
				}
			}

			// Has the character reached the goal?
			if (m_ArrayLevel[y][x] == 4)
			{
				// Character has reached the goal
				reachedGoal = true;
			}

		}

	}

	// All done, return, wheteher or not a new level might be required
	return reachedGoal;
}