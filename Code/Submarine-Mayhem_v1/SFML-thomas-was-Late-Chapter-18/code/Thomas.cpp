#include "Thomas.h"
#include "TextureHolder.h"
#include <iostream>

Thomas::Thomas()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/thomas.png"));

	m_JumpDuration = .45;
}

// A virtual function
bool Thomas::handleInput()
{
	/*
	* Removed jumping in favour of free vertical movement
	* 
	m_JustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::W))
	{

		// Start a jump if not already jumping
		// but only if standing on a block (not falling)
		if (!m_IsJumping && !m_IsFalling)
		{
			m_IsJumping = true;
			m_TimeThisJump = 0;
			m_JustJumped = true;
		}
	}
	else
	{
		m_IsJumping = false;
		m_IsFalling = true;

	}
	*/

	if (Keyboard::isKeyPressed(Keyboard::K))
	{

		std::cout << "player health: " << getHealth() << "\n";
	}

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		m_isClimbing = true;
	}
	else
	{
		m_isClimbing = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		m_IsFalling = true;
	}
	else
	{
		m_IsFalling = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_LeftPressed = true;
	}
	else
	{
		m_LeftPressed = false;
	}


	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		m_RightPressed = true;
	}
	else
	{
		m_RightPressed = false;
	}

	return m_JustJumped;
}

void Thomas::setHealth(int h)
{
	health = h;
}
void Thomas::setSpeed(int S)
{
	m_Speed += S;
}
int Thomas::getHealth()
{
	return health;
}
