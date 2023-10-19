#include "Bob.h"
#include "TextureHolder.h"
#include <iostream>

Bob::Bob()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/bob.png"));

	m_JumpDuration = .25;
}

void Bob::SetPatrolPoint(Vector2f newPatrolPoint)
{
	patrolPoint = newPatrolPoint;
}

void Bob::patrol()
{
	float asd = m_Position.x;
	std::cout << "Moving = " << moving << "\n";
	std::cout << "Flipped = " << flipped << "\n";
	std::cout << "m_Position.x = " << m_Position.x << "\n";
	std::cout << "patrolPoint.x = " << patrolPoint.x << "\n";
	//If bob moves far enough from of his patrol point, flip direction
	if (moving && !flipped && m_Position.x > patrolPoint.x + 150)
	{
		flipped = true;
		//m_Sprite.setScale(-1, 0);
	}

	if (moving && flipped && m_Position.x < patrolPoint.x - 150)
	{
		std::cout << "Should unflip";
		flipped = false;
		//m_Sprite.setScale(1, 0);
	}
}

bool Bob::handleInput()
{
	patrol();

	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		m_isClimbing = true;
	}
	else
	{
		m_isClimbing = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		m_IsFalling = true;
	}
	else
	{
		m_IsFalling = false;
	}

	if (moving && flipped)
	{
		m_LeftPressed = true;
		std::cout << "Moving Left\n";

	}
	else
	{
		m_LeftPressed = false;
	}


	if (moving && !flipped)
	{
		m_RightPressed = true;

		std::cout << "Moving Right\n";

	}
	else
	{
		m_RightPressed = false;
	}

	return m_JustJumped;
}