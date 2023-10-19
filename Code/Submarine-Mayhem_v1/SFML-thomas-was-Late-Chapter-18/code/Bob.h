#pragma once
#include "PlayableCharacter.h"

class Bob : public PlayableCharacter
{
public:
	// A constructor specific to Bob
	Bob();

	//Patrol function
	//Makes bob walk left and right for set distances
	void patrol();
	Vector2f patrolPoint;
	void SetPatrolPoint(Vector2f newPatrolPoint);

	//Should he be moving, and which way is he facing?
	bool moving = true;
	bool flipped = false;	//Non-flipped = Right

	//Health and damage
	int m_Health = 10;
	bool alive;

	void setHealth(int newHealth);
	int getHealth();
	void damage(int damage);
	void heal(int heal);
	void die();
	bool isAlive();

	// The overriden input handler for Bob
	bool virtual handleInput();

};

