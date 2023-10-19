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
	//If bob moves far enough from of his patrol point, flip direction
	if (moving && !flipped && m_Position.x > patrolPoint.x + 150)
	{
		flipped = true;
	}

	if (moving && flipped && m_Position.x < patrolPoint.x - 150)
	{
		flipped = false;
	}
}

bool Bob::handleInput()
{
	patrol();

	if (moving && flipped)
	{
		m_LeftPressed = true;

	}
	else
	{
		m_LeftPressed = false;
	}


	if (moving && !flipped)
	{
		m_RightPressed = true;

	}
	else
	{
		m_RightPressed = false;
	}

	return m_JustJumped;
}