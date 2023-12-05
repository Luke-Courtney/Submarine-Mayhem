#include "Engine.h"
#include <iostream>

Engine::Engine()
{
	list<Bob*>::const_iterator iter;
	counter = 0;
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
	// Set up a menu
	MENU.loadFromFile("graphics/menu.png");
	menu.setTexture(MENU);
	// Set up a pause screen
	PAUSE.loadFromFile("graphics/pause.png");
	pause.setTexture(PAUSE);
	// Time bar
	//timeRemaining = 20;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((resolution.x / 2) - timeBarStartWidth / 2, resolution.y);//position
	timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;


	//Game over text ran out of oxygen
	// Load the font
	Font.loadFromFile("fonts/Roboto-Light.ttf");
	messageText.setFont(Font);
	messageText.setCharacterSize(100);
	messageText.setFillColor(Color::Red);
	// Change the message shown to the player
	messageText.setString("Ran Out Of Oxygen!");
	messageText.setPosition((resolution.x/2)-500,(resolution.y/2));
	
	

	//set offset value between player and timebar
	offset.x = 0;
	offset.y = 400;
	
		
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

	//create enemy
	m_Bob0 = new Bob();
	m_Bob1 = new Bob();
	m_Bob2 = new Bob();

	//put enemy on list
	Enemy.push_back(m_Bob0);
	Enemy.push_back(m_Bob1);
	Enemy.push_back(m_Bob2);

	//Set bob patrol point
	for (iter = Enemy.begin(); iter != Enemy.end(); ++iter)
	{
		(*iter)->setType(counter);
		if (counter == 0)
		{
			(*iter)->SetPatrolPoint(Vector2f(750, 450));
		}
		if (counter == 1)
		{
			(*iter)->SetPatrolPoint(Vector2f(3700, 650));
		}
		if (counter == 2)
		{
			(*iter)->SetPatrolPoint(Vector2f(1800, 900));
		}
		counter++;
	}

	// how much does it increase whatever it increases
	healthPickup.m_Value = 10;
	healthPickup2.m_Value = 25;
	MaxSpeed.m_Value = 500;
	SpeedBoost.m_Value = 0.2f;

	//selecting the sprite to be used
	healthPickup.m_Type = 1;
	MaxSpeed.m_Type = 2;
	healthPickup2.m_Type = 3;
	SpeedBoost.m_Type = 4;

	healthPickup.refreshSprite();
	healthPickup2.refreshSprite();
	MaxSpeed.refreshSprite();
	SpeedBoost.refreshSprite();

	srand(time(0));

	// Hide the mouse pointer and replace it with crosshair
	m_Window.setMouseCursorVisible(true);
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 50);

}// End Engine constructor

void Engine::run()
{
	// Timing 	
	Clock clock;

	while (m_Window.isOpen())
	{
		list<Bob*>::const_iterator iter;

		Time dt = clock.restart();
		// Update the total game time
		m_GameTimeTotal += dt;
		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			//Deals 1 damage and outputs new health
			for (iter = Enemy.begin(); iter != Enemy.end(); ++iter)
			{
				(*iter)->damage(1);
				std::cout << "Dealt 1 damage. Health: " << (*iter)->getHealth() << "\n";
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::K))
		{
				std::cout << "Thomas Health: " << m_Thomas.getHealth() << "\n";
		}

		input();
		update(dtAsSeconds);
		draw();
	}
}