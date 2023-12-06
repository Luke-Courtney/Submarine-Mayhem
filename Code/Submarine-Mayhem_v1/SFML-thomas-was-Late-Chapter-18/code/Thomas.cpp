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
	
	//Removed jumping in favour of free vertical movement


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
		//flipped = true;
	}
	else
	{
		m_LeftPressed = false;
	}


	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		m_RightPressed = true;
		//flipped = false;
	}
	else
	{
		m_RightPressed = false;
	}

	return m_JustJumped;
}

void Thomas::setHealth(int h)
{
	health += h;
}
void Thomas::setMaxSpeed(int S)
{
	m_Speed += S;
}
void Thomas::setAcceleration(int A)
{
	rampUp += A;
}
int Thomas::getHealth()
{
	return health;
}
bool Thomas::isAlive()
{
	return alive;
}

//Deal damage
void Thomas::damage(int damage)
{
	health = health - damage;
	if (health < 1)
	{
		//die();
	}
}