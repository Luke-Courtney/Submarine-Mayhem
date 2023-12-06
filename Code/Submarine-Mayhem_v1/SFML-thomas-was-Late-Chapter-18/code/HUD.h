#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hud
{
private:
	Font m_Font;
	Text m_StartText;
	Text m_LevelText;
	Text m_AmmoText;

public:
	Hud();
	Text getMessage();
	Text getLevel();
	// Ammo
	Text getAmmo();

	void setLevel(String text);
	void setAmmo(String text);
};