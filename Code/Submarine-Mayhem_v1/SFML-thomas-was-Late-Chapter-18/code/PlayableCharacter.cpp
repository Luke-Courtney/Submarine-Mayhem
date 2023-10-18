#include "PlayableCharacter.h"
#include <iostream>
using namespace std;

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
		if (m_RightSpeed < m_Speed) {
			m_RightSpeed += rampUp;
		}

		m_Position.x += m_RightSpeed * elapsedTime;
		m_Sprite.setScale(Vector2f(1, 1));
	}
	else if(m_RightSpeed > 0)
	{
		m_Position.x += m_RightSpeed * elapsedTime;
		m_RightSpeed -= rampDown;

		if (m_RightSpeed < 0) {
			m_RightSpeed = 0;
		}
	}

	if (m_LeftPressed)
	{
		if (m_LeftSpeed > -m_Speed) {
			m_LeftSpeed -= rampUp;
		}

		m_Position.x += m_LeftSpeed * elapsedTime;
		m_Sprite.setScale(Vector2f(-1, 1));
	}
	else if(m_LeftSpeed < 0)
	{
		m_Position.x += m_LeftSpeed * elapsedTime;
		m_LeftSpeed += rampDown;

		if (m_LeftSpeed > 0) {
			m_LeftSpeed = 0;
		}
	}

	// Handle Climbing
	if (m_isClimbing)
	{
		// Update how long the jump has been going
		m_TimeThisJump += elapsedTime;

		if (m_UpSpeed > -m_Speed) {
			m_UpSpeed -= rampUp;
		}

		m_Position.y += m_UpSpeed * elapsedTime;
	}
	else if (m_UpSpeed < 0)
	{
		m_Position.y += m_UpSpeed * elapsedTime;
		m_UpSpeed += rampDown;

		if (m_UpSpeed > 0) {
			m_UpSpeed = 0;
		}
	}

	// Move down
	if (m_IsFalling)
	{
		if (m_DownSpeed < m_Speed) {
			m_DownSpeed += rampUp;
		}

		m_Position.y += m_DownSpeed * elapsedTime;
	}
	else if (m_DownSpeed > 0)
	{
		m_Position.y += m_DownSpeed * elapsedTime;
		m_DownSpeed -= rampDown;

		if (m_DownSpeed < 0) {
			m_DownSpeed = 0;
		}
	}

	// Update the rect for all body parts
	FloatRect r = getPosition();


	// Feet
	m_Feet.left = r.left + 25;
	m_Feet.top = r.top + r.height;
	m_Feet.width = r.width + 25;
	m_Feet.height = 1;

	// Head
	m_Head.left = r.left + 25;
	m_Head.top = r.top + (r.height * .3);
	m_Head.width = r.width + 25;
	m_Head.height = 1;

	// Right
	m_Right.left = r.left + r.width;
	m_Right.top = r.top + r.height * .3 + 15;
	m_Right.width = 5;
	m_Right.height = r.height * .3 - 25;

	// Left
	m_Left.left = r.left;
	m_Left.top = r.top + r.height * .35 - 150;
	m_Left.width = - 25;
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
	
	m_Position.x = position - m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::stopLeft(float position)
{
	m_Position.x = position + m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);

	m_Sprite.setRotation(90); //TEST TO DETECT stopLeft()
}

void PlayableCharacter::stopJump()
{
	// Stop a jump early 
	m_isClimbing = false;
	m_IsFalling = true;
}



