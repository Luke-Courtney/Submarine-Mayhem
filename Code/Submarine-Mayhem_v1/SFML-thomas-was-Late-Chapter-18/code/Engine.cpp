#include "Engine.h"

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


	//Set bob patrol point
	m_Bob.SetPatrolPoint(Vector2f(750, 450));

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