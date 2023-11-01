#include "Engine.h"
void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			

			// Handle the player quitting
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				m_Window.close();

			}

			// Handle the player starting the game
			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				m_Playing = true;
				m_Menu.setPosition(-5000, -5000);//GET RID OF MENU
			}
		}
	}	

	// Handle input specific to Thomas
	if (m_Thomas.handleInput())
	{
		// Play a jump sound
		m_SM.playJump();
	}

	// Handle input specific to Bob
	if (m_Bob.handleInput())
	{
		// Play a jump sound
		m_SM.playJump();
	}
}