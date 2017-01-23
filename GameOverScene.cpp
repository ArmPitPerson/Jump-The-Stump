#include "GameOverScene.h"
#include "GlobalFunctions.h"
#include "JumpTheStump.h"

void AGameOver::LoadResources() {
	SBackground.setTexture(TBackground);
	SBackground.setColor(sf::Color(255, 255, 255, 100));

	GameOverText.setString("GAME OVER!");
	GameOverText.setCharacterSize(48);
	GameOverText.Center(0.f, -46.f);

	FinalScoreText.setString(ToString<int>(Score) + " POINTS");
	FinalScoreText.setCharacterSize(48);
	FinalScoreText.Center(0.f, 6.f);

	PlayAgainText.setString("Hit R to Replay or Q to Quit");
	PlayAgainText.setCharacterSize(20);
	PlayAgainText.Center(0.f, 90.f);

	SFXGameOver.play();
}

void AGameOver::HandleInput(const sf::Event& E) {
	if (E.type == sf::Event::Closed) GameWindow.close();
	if (E.type == sf::Event::KeyPressed && E.key.code == sf::Keyboard::Key::Q) Game.SwitchScene(&Game.MainMenu);
	if (E.type == sf::Event::KeyPressed && E.key.code == sf::Keyboard::Key::R) Game.SwitchScene(&Game.MainGame);
}

void AGameOver::Update(double DeltaTime) {

}

void AGameOver::Render() {
	GameWindow.clear();
	GameWindow.draw(SBackground);
	GameWindow.draw(GameOverText);
	GameWindow.draw(FinalScoreText);
	GameWindow.draw(PlayAgainText);
	GameWindow.display();
}
