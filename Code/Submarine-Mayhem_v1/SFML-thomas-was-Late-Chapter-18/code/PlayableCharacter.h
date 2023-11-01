#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter
{
protected:
	// Of course we will need a sprite
	Sprite m_Sprite;

	// How long does a jump last
	float m_JumpDuration;

	// Is character currently moving up or down
	bool m_isClimbing;
	bool m_IsFalling;

	// Which directions is the character currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;

	// How long has this jump lasted so far
	float m_TimeThisJump;

	// Has the player just initialted a jump
	bool m_JustJumped = false;

	// Where is the player
	Vector2f m_Position;


	// How fast is the character
	float m_Speed = 400; //Max speed

	// Private variables and functions come next
private:
	// What is the gravity
	float m_Gravity;


	float m_RightSpeed = 0;
	float m_LeftSpeed = -0;
	float m_UpSpeed = -0;
	float m_DownSpeed = 0;

	//How fast the player speeds up and slows down
	//Smaller number means slower change in speed
	float rampUp = 0.25f;	//Acceleration
	float rampDown = 0.5f;	//Decceleration

	// Where are the characters various body parts?
	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;

	// And a texture
	Texture m_Texture;

	// All our public functions will come next
public:

	void spawn(Vector2f startPosition, float gravity);

	// This is a pure virtual function
	bool virtual handleInput() = 0;
	// This class is now abstract and cannot be instanciated

	// Where is the player
	FloatRect getPosition();

	// A rectangle representing the position of different parts of the sprite
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// Make the character stand firm
	void stopClimbing(float position);
	void stopFalling(float position);
	void stopRight(float position);
	void stopLeft(float position);
	void stopJump();

	// Where is the center of the character
	Vector2f getCenter();

	// We will call this function once every frame
	void update(float elapsedTime);
};
