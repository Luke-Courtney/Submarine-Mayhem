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
	int m_Health = 5;
	int Damage = 1;
	bool alive;

	//Enemy type
	int m_type = 0; //0,1,2

	//Set type
	void setType(int newType);
	void setSpriteType();

	void setHealth(int newHealth);
	int getHealth();
	int Getdamage();
	void Setdamage(int D);
	void heal(int heal);
	void die();
	bool isAlive();

	// The overriden input handler for Bob
	bool virtual handleInput();

};

