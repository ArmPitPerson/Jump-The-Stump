#pragma once
#ifndef JTS_H
#define JTS_H

#include "GameOverScene.h"
#include "MainGameScene.h"
#include "MainMenuScene.h"

class JumpTheStumpGame {
public:
	JumpTheStumpGame() : GameWindow({ 1600, 900 }, "Jump the Stump", sf::Style::None) {
		GameWindow.setFramerateLimit(144);
		SwitchScene(&MainMenu);
		Icon.loadFromFile("Textures/Icon.png");
		GameWindow.setIcon(256, 256, Icon.getPixelsPtr());
	}

	void SwitchScene(AScene* NewScene) {
		if (ActiveScene) ActiveScene->UnloadResources();
		ActiveScene = NewScene;
		if (ActiveScene) ActiveScene->LoadResources();
	}

	AMainMenu MainMenu{ GameWindow, *this };
	AMainGame MainGame{ GameWindow, *this };
	AGameOver GameOver{ GameWindow, *this, MainGame.GetScore() };

	int GameLoop() {
		while (GameWindow.isOpen()) {
			double DeltaTime = DeltaClock.restart().asSeconds();

			if (ActiveScene) {
				sf::Event CurrentEvent;
				while (GameWindow.pollEvent(CurrentEvent)) {
					if (CurrentEvent.type == sf::Event::Closed) GameWindow.close();
					ActiveScene->HandleInput(CurrentEvent);
				}
				ActiveScene->Update(DeltaTime);
				ActiveScene->Render();
			}
		}
		return 0;
	}

private:
	sf::Clock DeltaClock;
	sf::RenderWindow GameWindow;
	sf::Image Icon;
	AScene* ActiveScene = nullptr;
};

#endif
