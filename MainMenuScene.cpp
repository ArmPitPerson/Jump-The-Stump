#include "MainMenuScene.h"
#include "MainGameScene.h"
#include "JumpTheStump.h"

void AMainMenu::LoadResources() {
	MenuMusic.setLoop(true);
	MenuMusic.play();	
	MenuBackground.setTexture(MenuBackgroundTexture);
	TapKey.setTexture(TapKeyTexture);
}

void AMainMenu::HandleInput(const sf::Event& E) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) GameWindow.close();
	else if (E.type == sf::Event::KeyPressed) Game.SwitchScene(&Game.MainGame);
}

void AMainMenu::Update(double DeltaTime) {
	if (TapAlpha == 1) bFadingOut = false;
	if (TapAlpha == 255) bFadingOut = true;
	if (bFadingOut) --TapAlpha;
	else ++TapAlpha;
	TapKey.setColor({ 255, 255, 255, TapAlpha });
}

void AMainMenu::Render() {
	GameWindow.clear();

	GameWindow.draw(MenuBackground);
	GameWindow.draw(TapKey);

	GameWindow.display();
}

void AMainMenu::UnloadResources() {
	MenuMusic.stop();
}
