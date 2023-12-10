#include "Hud.h"

Hud::Hud()
{
	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	// Load the font
	m_Font.loadFromFile("fonts/Roboto-Light.ttf");

	
	// Position the text
	FloatRect textRect = m_StartText.getLocalBounds();

	m_StartText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	m_StartText.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);

	// Level
	m_LevelText.setFont(m_Font);
	m_LevelText.setCharacterSize(75);
	m_LevelText.setFillColor(Color::White);
	m_LevelText.setPosition(25, 0);
	m_LevelText.setString("1");

	//Ammo 
	m_AmmoText.setFont(m_Font);
	m_AmmoText.setCharacterSize(75);
	m_AmmoText.setFillColor(Color::White);
	m_AmmoText.setPosition(25, 900);
	m_AmmoText.setString("Ammo:");
}

Text Hud::getMessage()
{
	return m_StartText;
}

Text Hud::getLevel()
{
	return m_LevelText;
}

Text Hud::getAmmo()
{
	return m_AmmoText;
}

void Hud::setLevel(String text)
{
	m_LevelText.setString(text);
}

void Hud::setAmmo(String text)
{
	m_AmmoText.setString(text);
}