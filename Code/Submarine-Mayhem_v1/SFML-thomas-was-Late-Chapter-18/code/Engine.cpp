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
	m_Bob3 = new Bob();
	m_Bob4 = new Bob();
	m_Bob5 = new Bob();
	m_Bob6 = new Bob();
	m_Bob7 = new Bob();
	m_Bob8 = new Bob();
	m_Bob9 = new Bob();

	//put enemy on list
	Enemy.push_back(m_Bob0);
	Enemy.push_back(m_Bob1);
	Enemy.push_back(m_Bob2);
	Enemy.push_back(m_Bob3);
	Enemy.push_back(m_Bob4);
	Enemy.push_back(m_Bob5);
	Enemy.push_back(m_Bob6);
	Enemy.push_back(m_Bob7);
	Enemy.push_back(m_Bob8);
	Enemy.push_back(m_Bob9);

	// how much does it increase whatever it increases
	healthPickup.m_Value = 10;
	healthPickup2.m_Value = 25;
	MaxSpeed.m_Value = 500;
	SpeedBoost.m_Value = 0.2f;
	BulletFireRate.m_Value = 2;
	BulletSpeed.m_Value = 50;
	BulletDMG.m_Value = 2;

	//selecting the sprite to be used
	healthPickup.m_Type = 1;
	MaxSpeed.m_Type = 2;
	healthPickup2.m_Type = 3;
	SpeedBoost.m_Type = 4;
	BulletFireRate.m_Type = 5;
	BulletSpeed.m_Type = 6;
	BulletDMG.m_Type = 7;

	healthPickup.refreshSprite();
	healthPickup2.refreshSprite();
	MaxSpeed.refreshSprite();
	SpeedBoost.refreshSprite();
	BulletFireRate.refreshSprite();
	BulletSpeed.refreshSprite();
	BulletDMG.refreshSprite();

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
				(*iter)->Getdamage();
				std::cout << "Dealt 1 damage. Health: " << (*iter)->getHealth() << "\n";
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::K))
		{
				std::cout << "Thomas Health: " << m_Thomas.getHealth() << "\n";
		}

		if (Keyboard::isKeyPressed(Keyboard::U))
		{
			BulletSpeed.spawn(Vector2f(m_Thomas.getCenter().x + 10, m_Thomas.getCenter().y), GRAVITY);
		}

		input();
		update(dtAsSeconds);
		draw();
	}
}
int Engine::plusHealth()
{
	timeRemaining = timeRemaining + 1;
	return timeRemaining;
}
int Engine::minusHealth()
{
	timeRemaining = timeRemaining - 0.5;
	return timeRemaining;
}