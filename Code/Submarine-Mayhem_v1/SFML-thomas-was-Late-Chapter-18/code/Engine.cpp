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
	//Set up a menu
	m_MenuTexture = TextureHolder::GetTexture("graphics/menu.png");
	m_Menu.setTexture(m_MenuTexture);
	m_Menu.setPosition(0, 0);
	// Time bar
	//timeRemaining = 20;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 1080);
	timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
	
	
	//set offset value between player and timebar
	offset.x = 0;
	offset.y = 450;
	

		

		
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
	m_Bob0.SetPatrolPoint(Vector2f(750, 450));
	m_Bob1.SetPatrolPoint(Vector2f(3700, 650));
	m_Bob2.SetPatrolPoint(Vector2f(1800, 900));


	healthPickup.m_Value = 10;
	healthPickup2.m_Value = 25;
	MaxSpeed.m_Value = 500;

	healthPickup.m_Type = 1;
	MaxSpeed.m_Type = 2;
	healthPickup2.m_Type = 3;
	healthPickup.refreshSprite();
	healthPickup2.refreshSprite();
	MaxSpeed.refreshSprite();

	srand(time(0));

}// End Engine constructor

void Engine::run()
{
	// Timing 	
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();
		// Update the total game time
		m_GameTimeTotal += dt;
		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);
		draw();
	}
}