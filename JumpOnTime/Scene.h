#pragma once
#ifndef SCENE_H
#define SCENE_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

class JumpTheStumpGame;

class AScene {
public:
	AScene(sf::RenderWindow& W, JumpTheStumpGame& G) : GameWindow(W), Game(G) {}
	virtual ~AScene() {}

	virtual void LoadResources() {}
	virtual void HandleInput(const sf::Event& E) {}
	virtual void Update(double DeltaTime) {}
	virtual void Render() {}
	virtual void UnloadResources() {}

protected:
	sf::RenderWindow& GameWindow;
	JumpTheStumpGame& Game;
};
#endif