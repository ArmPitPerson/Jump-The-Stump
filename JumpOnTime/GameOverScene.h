#pragma once
#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "Scene.h"
#include "SFML/Audio.hpp"
#include "Player.h"
#include "Obstacle.h"
#include "CollisionArea.h"
#include "CenteredText.h"

class AGameOver : public AScene {
public:
	AGameOver(sf::RenderWindow& W, JumpTheStumpGame& G, int &GameScore) : AScene(W, G), Score(GameScore) {
		TBackground.loadFromFile("Textures/Background.png");
		RegularFont.loadFromFile("Fonts/Rubik-Regular.ttf");
		BoldFont.loadFromFile("Fonts/Rubik-Bold.ttf");
		GameOverSound.loadFromFile("Audio/GameOver.wav");
	}

	virtual void LoadResources() override;
	virtual void HandleInput(const sf::Event& E) override;
	virtual void Update(double DeltaTime) override;
	virtual void Render() override;

private:
	sf::Texture TBackground;
	sf::Sprite	SBackground;

	sf::Font RegularFont, BoldFont;
	CenteredText GameOverText{ BoldFont, 0.f, -50.f };
	CenteredText FinalScoreText{ BoldFont, 0.f, 50.f };
	CenteredText PlayAgainText{ RegularFont, 0.f, 50.f };
	
	sf::SoundBuffer GameOverSound;
	sf::Sound SFXGameOver{ GameOverSound };

	int& Score;
};

#endif