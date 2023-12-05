#include "Engine.h"

void Engine::draw()
{
	list<Bob*>::const_iterator iter;
	// Rub out the last frame
	m_Window.clear(Color::White);
	
	// Update the shader parameters
	m_RippleShader.setUniform("uTime", m_GameTimeTotal.asSeconds());

		// Switch to background view
		m_Window.setView(m_BGMainView);
		// Draw the background
		m_Window.draw(m_BackgroundSprite);

		// Draw the background, complete with shader effect
		m_Window.draw(m_BackgroundSprite, &m_RippleShader);

		// Switch to m_MainView
		m_Window.setView(m_MainView);		

		// Draw the Level
		m_Window.draw(m_VALevel, &m_TextureTiles);

		// Draw thomas
		m_Window.draw(m_Thomas.getSprite());

		// Draw bobs
		for (iter = Enemy.begin(); iter != Enemy.end(); ++iter)
		{
			m_Window.draw((*iter)->getSprite());
		}

		//draw Pickup
		m_Window.draw(healthPickup.getSprite());
		m_Window.draw(MaxSpeed.getSprite());
		m_Window.draw(healthPickup2.getSprite());
		m_Window.draw(SpeedBoost.getSprite());

		//draw timebar
		m_Window.draw(timeBar);
		
		// Draw the particle system
		if (m_PS.running())
		{
			m_Window.draw(m_PS);
		}

		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isInFlight())
			{
				m_Window.draw(bullets[i].getShape());
			}
			/*
			else if (enemyBullets[i].isInFlight())
			{
				m_Window.draw(enemyBullets[i].getShape());
			}
			*/
		}
	
		//Draw the crosshair
		m_Window.draw(spriteCrosshair);
	
	// Draw the HUD
	// Switch to m_HudView
	m_Window.setView(m_HudView);
	m_Window.draw(m_Hud.getLevel());
	//ammo text
	//m_Window.draw(m_Hud.getAmmo());
	//m_Window.draw(m_Menu);
	//m_Window.draw(m_Hud.getTime());
	m_Window.draw(menu);
	if (!m_Playing)
	{
		m_Window.draw(m_Hud.getMessage());
	}

	if (oxygenGone)
	{
		m_Window.draw(messageText);
	}

	if (paused)
	{
		m_Window.draw(pause);
	}

	// Show everything we have just drawn
	m_Window.display();
}