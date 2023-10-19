#pragma once
#include "PlayableCharacter.h"

class Thomas : public PlayableCharacter
{
public:
	// A constructor specific to Thomas
	Thomas();

	
	int health = 10;

	// The overriden input handler for Thomas
	bool virtual handleInput();
	void setHealth(int h);
	int getHealth();

};
