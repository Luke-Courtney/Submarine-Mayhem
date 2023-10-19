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

	// How much is this pickup worth?
	int m_Value=10;

	// What type of pickup is this? 
	// 1 = health, 2 = ammo, 3 = CannonBall Gun, 4 = Pistol
	int m_Type=1;

	// Handle spawning and disappearing
	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDeSpawn;
	float m_SecondsToLive;
	float m_SecondsToWait;

	// Public prototypes go here
public:

	Pickup();

	// Let the pickup update itself each frame
	void update(float elapsedTime);

	bool virtual handleInput();

	// Is this pickup currently spawned?
	bool isSpawned();

	// Get the goodness from the pickup
	int gotIt();

	// Upgrade the value of each pickup
	void upgrade();

};



