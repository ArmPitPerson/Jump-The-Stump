#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Audio/Sound.hpp"

struct FCollisionArea;

class APlayer : public sf::RectangleShape {
public:
	APlayer() : sf::RectangleShape(sf::Vector2f(40.f, 120.f)) {
		setOrigin(20.f, 120.f);
		setPosition({ 400.f, 776.f });
		JumpSound.loadFromFile("Audio/Jump.wav");
		DoubleJumpSound.loadFromFile("Audio/DoubleJump.wav");
		GroundImpact.loadFromFile("Audio/GroundImpact.wav");
		SlamSound.loadFromFile("Audio/Slam.wav");
		setFillColor(sf::Color(170, 201, 195));
	}
	APlayer(float Width, float Height) : sf::RectangleShape(sf::Vector2f(Width, Height)) {
		setOrigin(Width / 2.f, Height);
		setPosition({ 400.f, 776.f });
		JumpSound.loadFromFile("Audio/Jump.wav");
		DoubleJumpSound.loadFromFile("Audio/DoubleJump.wav");
		GroundImpact.loadFromFile("Audio/GroundImpact.wav");
		SlamSound.loadFromFile("Audio/Slam.wav");
		setFillColor(sf::Color(170, 201, 195));
	}

	void Reset() { Lives = 3; setPosition(400.f, 776.f); }
	void Slam();
	void Jump();
	void Update(double DeltaTime);
	void HandleInput(sf::Event InputEvent);

	void TakeDamage();
	void AddLife() { ++Lives; }

	// Add Velocity in X and Y
	sf::Vector2<double>& AddVelocity(double X, double Y);

	// Add Velocity in Y only. Useful for Gravity / Jumping
	sf::Vector2<double>& AddVelocity(double Y) { return AddVelocity(0.0, Y); }

	const bool IsAlive() const { return Lives > 0; }
	const bool CanJump() const { return bIsGrounded && TimeToNextJump == 0; }
	const bool CanDoubleJump() const { return !bIsGrounded && !bHasDoubleJumped && TimeToNextJump == 0; }
	const bool CanTakeDamage() const { return TimeToNextDamage <= 0; }

	const int GetLives() const { return Lives; }
	const double GetJumpStrength() const { return JumpStrength; }
	const sf::Vector2<double> GetVelocity() const { return Velocity; }
	FCollisionArea GetCollisionArea() const;

private:
	bool bRotatingLeft = false;
	bool bRotatingRight = false;
	bool bIsGrounded = true;
	bool bHasDoubleJumped = false;

	int Lives = 3;

	double TurnRate = 4.0;
	double TargetAngle = 0.0;
	double RadianAngle = 0.0;

	double XPos = 400.0;
	double YPos = 776.0;

	double DamageDelay = 1.0;
	double TimeToNextDamage = 0.0;

	double JumpDelay = 0.1;
	double TimeToNextJump = 0.0;
	double JumpStrength = 5.0;

	sf::Vector2<double> Velocity{ 0.0, 0.0 };

	sf::SoundBuffer JumpSound, DoubleJumpSound, GroundImpact, SlamSound;
	sf::Sound SFXJump{ JumpSound };
	sf::Sound SFXDoubleJump{ DoubleJumpSound };
	sf::Sound SFXGroundImpact{ GroundImpact };
	sf::Sound SFXSlam{ SlamSound };
};

#endif
