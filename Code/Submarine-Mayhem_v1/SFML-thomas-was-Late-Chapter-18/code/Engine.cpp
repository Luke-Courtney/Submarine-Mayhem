#include "Engine.h"
#include <iostream>


Engine::Engine()
{
	// Get the screen resolution and create an SFML window and View
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Thomas was late",
		Style::Fullscreen);

	// Initialize the full screen view
	m_MainView.setSize(resolution);
	m_HudView.reset(
		FloatRect(0, 0, resolution.x, resolution.y));

	// Inititialize the split-screen Views
	m_LeftView.setViewport(
		FloatRect(0.001f, 0.001f, 0.498f, 0.998f));

	m_RightView.setViewport(
		FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

	m_BGLeftView.setViewport(
		FloatRect(0.001f, 0.001f, 0.498f, 0.998f));

	m_BGRightView.setViewport(
		FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

	// Can this graphics card use shaders?
	if (!sf::Shader::isAvailable())
	{
		// Time to get a new PC
		m_Window.close();
	}
	else
	{
		// Load two shaders (1 vertex, 1 fragment)
		m_RippleShader.loadFromFile("shaders/vertShader.vert",
			"shaders/rippleShader.frag");
	}

	m_BackgroundTexture = TextureHolder::GetTexture(
		"graphics/background.png");

	// Associate the sprite with the texture
	m_BackgroundSprite.setTexture(m_BackgroundTexture);


	// Load the texture for the background vertex array
	m_TextureTiles = TextureHolder::GetTexture(
		"graphics/tiles_sheet.png");

	// Initialize the particle system
	m_PS.init(1000);


	//Set bob patrol point
	m_Bob.SetPatrolPoint(Vector2f(750, 450));

	healthPickup.m_Value = 10;
	SpeedBoost.m_Value = 500;

	healthPickup.m_Type = 1;
	SpeedBoost.m_Type = 2;
	healthPickup.refreshSprite();
	SpeedBoost.refreshSprite();

}// End Engine constructor

void Engine::run()
{
	// Timing 	
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt2;
		Time dt = clock.restart();
		// Update the total game time
		m_GameTimeTotal += dt;
		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		if (healthPickup.spawnNum != 3)
		{
			if ((m_Bob.getHealth() < 1))
			{
				healthPickup.spawnNum = 2;
			}
		}
		if (healthPickup.spawnNum==2)
		{
			healthPickup.spawn(Vector2f(m_Bob.getCenter().x, m_Bob.getCenter().y), GRAVITY);
			SpeedBoost.spawn(Vector2f(m_Bob.getCenter().x, m_Bob.getCenter().y+60), GRAVITY);
			
			m_Bob.die();
			healthPickup.spawnNum = 3;
		}

		//if (SpeedBoost.BoostTimeEnd == false)
		//{
		//	dt2 = clock.restart();
		//	SpeedBoost.boostTime -= dt2.asSeconds();

		//}
		//if (SpeedBoost.boostTime <= 0)
		//{
		//	SpeedBoost.BoostTimeEnd = true;
		//	m_Thomas.setSpeed(4);
		//}

		if (Keyboard::isKeyPressed(Keyboard::O))
		{

			std::cout << m_Thomas.m_Speed << "Time remining for Boost: " << SpeedBoost.boostTime << "\n";
		}

		input();
		update(dtAsSeconds);
		draw();
	}
}