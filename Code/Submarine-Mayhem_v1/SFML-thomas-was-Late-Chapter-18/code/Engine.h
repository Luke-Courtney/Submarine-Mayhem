#pragma once
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <list>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "HUD.h"
#include "ParticleSystem.h"
#include "Pickup.h"
#include "Bullet.h"

using namespace sf;

class Engine
{
private:
	// The texture holder
	TextureHolder th;

	// create a particle system
	ParticleSystem m_PS;

	// Thomas and his friend, Bob
	Thomas m_Thomas;
	Bob* m_Bob0;
	Bob* m_Bob1;
	Bob* m_Bob2;
	int counter;
	list<Bob*> Enemy;


	Pickup healthPickup;
	Pickup MaxSpeed;
	Pickup healthPickup2;
	Pickup SpeedBoost;

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	Sprite spriteCrosshair;
	Texture textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");

	// 100 bullets should do
	Bullet bullets[999];
	//Bullet enemyBullets[999];
	int currentBullet = 0;
	int bulletsSpare = 100000;
	int bulletsInClip = 100000;
	int clipSize = 100000;
	float fireRate = 1;
	// When was the fire button last pressed?
	Time lastPressed;
	Bullet isInFlight;

	// A class to manage all the levels
	LevelManager m_LM;

	// Create a SoundManager
	SoundManager m_SM;

	// The Hud
	Hud m_Hud;
	int m_FramesSinceLastHUDUpdate = 0;
	int m_TargetFramesPerHUDUpdate = 500;

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	// The force pushing the characters down
	const int GRAVITY = 300;

	//Text display
	Font Font;
	Text messageText;

	// A regular RenderWindow
	RenderWindow m_Window;
	//Variable to control time
	Clock clock;
	//Total game time
	Time gameTimeTotal;
	//Make timebar a rectangle shape
	RectangleShape timeBar;
	//MENU
	Texture MENU;
	Sprite menu;
	//MENU
	Texture PAUSE;
	Sprite pause;
	//message
	FloatRect textRect = messageText.getLocalBounds();

	// The main Views
	View m_MainView;
	View m_LeftView;
	View m_RightView;

	// Three views for the background
	View m_BGMainView;
	View m_BGLeftView;
	View m_BGRightView;

	View m_HudView;

	// Declare a sprite and a Texture for the background
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	// Declare a shader for the background
	Shader m_RippleShader;
	//pause
	bool paused = false;
	// Is the game currently playing?
	bool m_Playing = false;

	// Is character 1 or 2 the current focus?
	bool m_Character1 = true;

	// Start in full screen mode
	bool m_SplitScreen = false;

	Time m_GameTimeTotal;
	bool oxygenGone = false;

	// Is it time for a new/first level?
	bool m_NewLevelRequired = true;

	// The vertex array for the level design
	VertexArray m_VALevel;

	// The 2d array with the map for the level
	// A pointer to a pointer
	int** m_ArrayLevel = NULL;

	// Texture for the background and the level tiles
	Texture m_TextureTiles;
	
	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();	

	// Load a new level
	void loadLevel();

	// Run will call all the private functions
	bool detectCollisions(PlayableCharacter& character);
	
	// Make a vector of the best places to emit sounds from
	void populateEmitters(vector <Vector2f>& vSoundEmitters,
		int** arrayLevel);

	// A vector of Vector2f for the fire emiiter locations
	vector <Vector2f> m_FireEmitters;

	

	//Oxygen bar
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	float timeRemaining = 20.0f;
	float timeBarWidthPerSecond;
	Time dt;
	//offset between player and timebar
	sf::Vector2f offset;
public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

};
