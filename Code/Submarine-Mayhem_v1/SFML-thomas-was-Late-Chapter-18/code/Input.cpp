#include "Engine.h"
void Engine::input()
{
	list<Bob*>::const_iterator iter;

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
			// Handle the player quitting
			if (Keyboard::isKeyPressed(Keyboard::P))
			{
				paused = true;
				m_Playing = false;
			}
			// Handle the player starting the game
			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				paused = false;
				m_Playing = true;
				menu.setPosition(-5000, -5000);//GET RID OF MENU
			}
			//handling restart menu
			if (restarted)
			{
				restarted = true;

				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::Return)//press enter to restart
					{

						m_Playing = true;//playing set to true
						restart.setPosition(-5000, -5000);//get rid of menu
						resetStats = true;//reset stats to true
						restarted = false;//restart set to false because we are in a playing state
					}

				}

			}
		}
	}	
			
	// Handle input specific to Thomas
	if (m_Thomas.handleInput())
	{
		// Play a jump sound
		m_SM.playJump();
	}

	 ///Handle input specific to Bobs
	for (iter = Enemy.begin(); iter != Enemy.end(); ++iter)
	{
		if ((*iter)->handleInput())
		{
			// Play a jump sound
			m_SM.playJump();
		}
	}
}