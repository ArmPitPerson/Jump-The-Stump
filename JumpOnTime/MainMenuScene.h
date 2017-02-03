#pragma once
#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Scene.h"
#include "SFML/Audio/Music.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Window/Event.hpp"

class AMainMenu : public AScene {
public:
	AMainMenu(sf::RenderWindow& W, JumpTheStumpGame& G) : AScene(W, G) {
		MenuMusic.openFromFile("Audio/Minuet-from-String-Quartet-Boccherini-Andy-Findon.wav");
		MenuBackgroundTexture.loadFromFile("Textures/MenuBackground.png");
		TapKeyTexture.loadFromFile("Textures/TapKey.png");
	}

	virtual void LoadResources() override;
	virtual void HandleInput(const sf::Event& E) override;
	virtual void Update(double DeltaTime) override;
	virtual void Render() override;
	virtual void UnloadResources() override;

private:
	sf::Music MenuMusic;
	sf::Texture MenuBackgroundTexture, TapKeyTexture;
	sf::Sprite MenuBackground, TapKey;

	sf::Uint8 TapAlpha = 255;
	bool bFadingOut = true;
};


#endif