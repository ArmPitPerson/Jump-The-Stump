#pragma once
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "SFML/Graphics.hpp"

struct FCollisionArea;

class AnObstacle : public sf::RectangleShape {
public:
	AnObstacle() : sf::RectangleShape({ 40.f, 80.f }) { setOrigin({ 20.f, 80.f }); setPosition({ 1700.f, 776.f }); setFillColor({ 146, 26, 26 }); }
	AnObstacle(float Width, float Height, double Speed = 250.0) : sf::RectangleShape({ Width, Height }) { setOrigin({ Width / 2.f, Height }); setPosition({ 1700.f, 776.f }); setVelocity(-Speed); setFillColor({ 146, 26, 26 }); }

	void Update(double DeltaTime);

	// Add Velocity in X and Y
	sf::Vector2<double>& AddVelocity(double X, double Y) { Velocity += sf::Vector2<double>(X, Y); return Velocity; }
	
	// Add Velocity in X only. Useful for this moving obstacle
	sf::Vector2<double>& AddVelocity(double X) { return AddVelocity(X, 0.0); }

	// Set Velocity in X only. Useful for this moving obstacle
	sf::Vector2<double>& setVelocity(double X) { Velocity.x = X; return Velocity; }

	const bool IsAwaitingKill() const { return bAwaitingKill; }

	FCollisionArea GetCollisionArea() const;

	bool bHitPlayer = false;

private:
	bool bAwaitingKill = false;

	double XPos = 1700.0;
	double YPos = 776.0;

	sf::Vector2<double> Velocity{ 0.0, 0.0 };
};

#endif