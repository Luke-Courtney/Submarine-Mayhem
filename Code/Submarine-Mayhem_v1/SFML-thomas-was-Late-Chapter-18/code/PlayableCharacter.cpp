#include "PlayableCharacter.h"

void PlayableCharacter::spawn(Vector2f startPosition, float gravity)
{
	// Place the player at the starting point
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	// Initialize the gravity
	m_Gravity = gravity;

	// Move the sprite in to position
	m_Sprite.setPosition(m_Position);

	//Set origin to center
	FloatRect spriteSize = m_Sprite.getGlobalBounds();
	m_Sprite.setOrigin(spriteSize.height, spriteSize.width);

}

void PlayableCharacter::update(float elapsedTime)
{

	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
		m_Sprite.setScale(Vector2f(1, 1));
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
		m_Sprite.setScale(Vector2f(-1, 1));
	}


	// Handle Climbing
	if (m_isClimbing)
	{
		// Update how long the jump has been going
		m_TimeThisJump += elapsedTime;

		m_Position.y -= m_Speed * elapsedTime;

	}

	// Move down
	if (m_IsFalling)
	{
		m_Position.y += m_Speed * elapsedTime;
	}

	// Update the rect for all body parts
	FloatRect r = getPosition();


	// Feet
	m_Feet.left = r.left +3;
	m_Feet.top = r.top + r.height;
	m_Feet.width = r.width - 6;
	m_Feet.height = 1;

	// Head
	m_Head.left = r.left;
	m_Head.top = r.top + (r.height * .3);
	m_Head.width = r.width;
	m_Head.height = 1;

	// Right
	m_Right.left = r.left + r.width + 6;
	m_Right.top = r.top + r.height * .35 + 15;
	m_Right.width = 1;
	m_Right.height = r.height * .3 - 25;

	// Left
	m_Left.left = r.left + 6;
	m_Left.top = r.top + r.height * .35 - 15;
	m_Left.width = 1;
	m_Left.height = r.height * .3 - 25;

	// Move the sprite into position
	m_Sprite.setPosition(m_Position);
}

FloatRect PlayableCharacter::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f PlayableCharacter::getCenter()
{
	return Vector2f(
		m_Position.x + (m_Sprite.getGlobalBounds().width / 2) + 25,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
		);
}

FloatRect PlayableCharacter::getFeet()
{
	return m_Feet;
}

FloatRect PlayableCharacter::getHead()
{
	return m_Head;
}

FloatRect PlayableCharacter::getLeft()
{
	return m_Left;
}

FloatRect PlayableCharacter::getRight()
{
	return m_Right;
}

Sprite PlayableCharacter::getSprite()
{
	return m_Sprite;
}


void PlayableCharacter::stopClimbing(float position)
{
	m_Position.y = position + getPosition().height + 90;
	m_Sprite.setPosition(m_Position);
	m_isClimbing = false;
}

void PlayableCharacter::stopFalling(float position)
{
	m_Position.y = position - getPosition().height + 175;
	m_Sprite.setPosition(m_Position);
	m_IsFalling = false;
}

void PlayableCharacter::stopRight(float position)
{
	
	m_Position.x = position - m_Sprite.getGlobalBounds().width - 20;
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::stopLeft(float position)
{
	m_Position.x = position + m_Sprite.getGlobalBounds().width + 20;
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::stopJump()
{
	// Stop a jump early 
	m_isClimbing = false;
	m_IsFalling = true;
}



