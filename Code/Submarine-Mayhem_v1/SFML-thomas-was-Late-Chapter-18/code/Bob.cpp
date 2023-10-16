#include "Bob.h"
#include "TextureHolder.h"

Bob::Bob()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/bob.png"));

	m_JumpDuration = .25;
}

bool Bob::handleInput()
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

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		m_LeftPressed = true;

	}
	else
	{
		m_LeftPressed = false;
	}


	if (Keyboard::isKeyPressed(Keyboard::Right))
	{

		m_RightPressed = true;

	}
	else
	{
		m_RightPressed = false;
	}

	return m_JustJumped;
}