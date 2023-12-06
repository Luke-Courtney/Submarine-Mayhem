#include "Pickup.h"
#include "TextureHolder.h"

Pickup::Pickup()
{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/health_1.png"));

	// How much is pickup worth
	m_Value = HEALTH_START_VALUE;

	m_Sprite.setOrigin(25, 25);
}

void Pickup::refreshSprite()
{
	if (m_Type == 1)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/health_1.png"));
		m_Sprite.setOrigin(25, 25);
	}
	else if (m_Type == 2)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/MaxSpeed_1.png"));
		m_Sprite.setOrigin(25, 25);
	}
	else if (m_Type == 3)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/health_2.png"));
		m_Sprite.setOrigin(25, 25);
	}
	else if (m_Type == 4)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/SpeedBoost_1.png"));
		m_Sprite.setOrigin(25, 25);
	}
	else if (m_Type == 5)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/BulletFireRate_1.png"));
		m_Sprite.setOrigin(25, 25);
	}
	else if (m_Type == 6)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/BulletSpeed_1.png"));
		m_Sprite.setOrigin(25, 25);
	}
	else if (m_Type == 7)
	{
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/BulletDMG.png"));
		m_Sprite.setOrigin(25, 25);
	}
}

bool Pickup::isSpawned()
{
	return m_Spawned;
}

int Pickup::gotIt()
{
	return m_Value;
}

void Pickup::update(float elapsedTime)
{

}

bool Pickup::handleInput()
{
	return false;
}
