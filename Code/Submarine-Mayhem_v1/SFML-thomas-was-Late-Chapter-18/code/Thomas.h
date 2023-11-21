#pragma once
#include "PlayableCharacter.h"

class Thomas : public PlayableCharacter
{
public:
	// A constructor specific to Thomas
	Thomas();

	
	int health = 10;
	bool alive;
	bool flipped = false;	//Non-flipped = Right
	// The overriden input handler for Thomas
	bool virtual handleInput();
	void setHealth(int h);
	void setMaxSpeed(int S);
	void setAcceleration(int S);
	int getHealth();
	bool isAlive();
	void damage(int damage);
	//void die();

};
