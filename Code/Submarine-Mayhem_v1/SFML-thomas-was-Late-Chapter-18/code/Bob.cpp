#include "Bob.h"
#include "TextureHolder.h"
#include "Bullet.h"
#include "Engine.h"
#include <iostream>

/*
References to Bobs in:
- Engine.h
- Engine.cpp
- Draw.cpp
- LoadLevel.cpp
- Update.cpp
- DetectCollisions.cpp
*/

Bob::Bob()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/bob0.png"));

	alive = true;

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

//vvvv Health and damage functions vvvv

//Teleports far from anything
void Bob::die()
{
	m_Position = Vector2f(100, 100);
	patrolPoint = Vector2f(100, 100);
	alive = false;
}

void Bob::setType(int newType)
{
	m_type = newType;
	setSpriteType();

}

void Bob::setSpriteType()
{
	switch (m_type)
	{
		case 0:
			m_Sprite = Sprite(TextureHolder::GetTexture(
				"graphics/bob0.png"));
			m_Speed += 50;
			break;

		case 1:
			m_Sprite = Sprite(TextureHolder::GetTexture(
				"graphics/bob1.png"));
			break;

		case 2:
			m_Sprite = Sprite(TextureHolder::GetTexture(
				"graphics/bob2.png"));
			m_Speed -= 50;
			break;
	}
}

//Set health value
void Bob::setHealth(int newHealth)
{
	m_Health = newHealth;
	if (m_Health < 1)
	{

	}
}

//Get health value
int Bob::getHealth()
{
	return m_Health;
}

//Deal damage
void Bob::damage(int damage)
{
	m_Health = m_Health - damage;
}

//Heal health
void Bob::heal(int heal)
{
	m_Health = m_Health + heal;
}

bool Bob::isAlive()
{
	return alive;
}

//vvvv Input handling vvvv

bool Bob::handleInput()
{
	patrol();

	if (moving && flipped && alive)
	{
		m_LeftPressed = true;

	}
	else
	{
		m_LeftPressed = false;
	}


	if (moving && !flipped && alive)
	{
		m_RightPressed = true;

	}
	else
	{
		m_RightPressed = false;
	}


	//vvv TEST KEYS vvv
	//Num1 - Damage Enemy
	//if (Keyboard::isKeyPressed(Keyboard::Num1))
	//{
	//	//Deals 1 damage and outputs new health
	//	damage(1);
	//	std::cout << "Dealt 1 damage. Health: " << getHealth() << "\n";
	//}

	//Num2 - Heal Enemy
	if (Keyboard::isKeyPressed(Keyboard::Num2))
	{
		//Heals 1 health and outputs new health
		heal(1);
		std::cout << "Healed 1 health. Health: " << getHealth() << "\n";
	}

	//Num3 - isAlive()
	if (Keyboard::isKeyPressed(Keyboard::Num3))
	{
		std::cout << "Is bob alive?: " << isAlive() << "\n";
	}

	//Num4 - Set health to 1
	if (Keyboard::isKeyPressed(Keyboard::Num4))
	{
		setHealth(1);
		std::cout << "Set health to 1. New health: " << getHealth() << "\n";
	}

	//Num5 - Set health to 0
	if (Keyboard::isKeyPressed(Keyboard::Num5))
	{
		setHealth(0);
		std::cout << "Set health to 0. New health: " << getHealth() << "\n";
	}

	return m_JustJumped;

}
