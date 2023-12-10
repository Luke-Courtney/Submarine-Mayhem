#pragma once
#include <SFML/Graphics.hpp>
#include"PlayableCharacter.h"

class Pickup : public PlayableCharacter
{
private:
	//Start value for health pickups
	const int HEALTH_START_VALUE = 50;
	const int AMMO_START_VALUE = 12;
	const int START_WAIT_TIME = 5;
	const int START_SECONDS_TO_LIVE = 15;

	// Handle spawning and disappearing
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDeSpawn;
	float m_SecondsToLive;
	float m_SecondsToWait;

	// Public prototypes go here
public:

	Pickup();

	void refreshSprite();

	//time the speed bost will last
	int boostTime = 5;
	bool BoostTimeEnd = true;

	// How much is this pickup worth?
	float m_Value = 0;

	int spawnNum = 1;

	// What type of pickup is this? 
	int m_Type = 0;

	bool m_Spawned;

	// Let the pickup update itself each frame
	void update(float elapsedTime);

	bool virtual handleInput();

	// Is this pickup currently spawned?
	bool isSpawned();

	// Get the goodness from the pickup
	int gotIt();
};



