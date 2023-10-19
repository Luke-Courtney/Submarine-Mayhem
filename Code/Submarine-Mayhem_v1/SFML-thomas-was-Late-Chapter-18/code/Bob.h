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

	// The overriden input handler for Bob
	bool virtual handleInput();

};

