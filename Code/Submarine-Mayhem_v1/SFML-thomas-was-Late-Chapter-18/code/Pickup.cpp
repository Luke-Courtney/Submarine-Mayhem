#include "Pickup.h"
#include "TextureHolder.h"

Pickup::Pickup()
{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/health_1.png"));

	// How much is pickup worth
	m_Value = HEALTH_START_VALUE;

	m_Sprite.setOrigin(25, 25);

	//m_SecondsToLive = START_SECONDS_TO_LIVE;
	//m_SecondsToWait = START_WAIT_TIME;
}

void Pickup::refreshSprite()
{
	if (m_Type == 1)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/health_1.png"));
		m_Sprite.setOrigin(25, 25);
	}
	if (m_Type == 2)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/SpeedBoost_1.png"));
		m_Sprite.setOrigin(25, 25);
	}
}

bool Pickup::isSpawned()
{
	return m_Spawned;
}

int Pickup::gotIt()
{
	//m_Spawned = false;
	//m_SecondsSinceDeSpawn = 0;
	return m_Value;
}

void Pickup::update(float elapsedTime)
{
	if (m_Spawned)
	{
		m_SecondsSinceSpawn += elapsedTime;
	}
	else
	{
		m_SecondsSinceDeSpawn += elapsedTime;
	}

	// Do we need to hide a pickup?
	if (m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned)
	{
		// Remove the pickup and put it somewhere else
		m_Spawned = false;
		m_SecondsSinceDeSpawn = 0;
	}

	// Do we need to spawn a pickup
	if (m_SecondsSinceDeSpawn > m_SecondsToWait && !m_Spawned)
	{

	}

}

bool Pickup::handleInput()
{
	return false;
}

void Pickup::upgrade()
{
	if (m_Type == 1)
	{
		m_Value += (HEALTH_START_VALUE * .5);
	}
	if(m_Type == 2)
	{
		m_Value += (AMMO_START_VALUE * .5);
	}

	// Make them more frequent and last longer
	m_SecondsToLive += (START_SECONDS_TO_LIVE / 10);
	m_SecondsToWait -= (START_WAIT_TIME / 10);
}
