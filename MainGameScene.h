#pragma once
#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include "SFML/Audio.hpp"
#include "Player.h"
#include "Obstacle.h"
#include "CollisionArea.h"
#include "CenteredText.h"

class AMainGame : public AScene {
public:
	AMainGame(sf::RenderWindow& W, JumpTheStumpGame& G) : AScene(W, G) {
		TBackground.loadFromFile("Textures/Background.png");
		ImpactSound.loadFromFile("Audio/Impact.wav");
		ExtraLifeSound.loadFromFile("Audio/ExtraLife.wav");
		ThemeSong.openFromFile("Audio/Telemann-Sonata-In-F-Minor-Barry-Joseph.wav");
		RegularFont.loadFromFile("Fonts/Rubik-Regular.ttf");
		BoldFont.loadFromFile("Fonts/Rubik-Bold.ttf");
	}

	virtual void LoadResources() override;
	virtual void HandleInput(const sf::Event& E) override;
	virtual void Update(double DeltaTime) override;
	virtual void Render() override;
	virtual void UnloadResources() override;

	int& GetScore() { return Score; }

private:
	sf::Texture TBackground;	
	sf::Sprite SBackground;
	APlayer Player = APlayer();
	std::vector<AnObstacle> Obstacles;
	std::vector<decltype(Obstacles.begin())> ToKill;

	sf::Font RegularFont, BoldFont;	
	sf::Text LifeText, ScoreText, DeltaText;

	sf::SoundBuffer ImpactSound, ExtraLifeSound;
	sf::Sound SFXImpact{ ImpactSound };
	sf::Sound SFXExtraLife{ ExtraLifeSound };
	sf::Music ThemeSong;

	int Score = 1;
	int ScoreMultiplier = 1;
	int GetNextLifeAt = 1000;
	int ReduceSpawnTimeAt = 200;
	int AddScoreMultiplierAt = 850;
	bool Running = true;
	double GroundLevel = 776.0;

	double TimeToNextObstacle = 1.2;
	double SpawnTime = 3.61;

	sf::Clock ScoreClock;
};


#endif