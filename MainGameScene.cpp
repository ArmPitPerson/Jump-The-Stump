#include "MainGameScene.h"
#include "GlobalFunctions.h"
#include "JumpTheStump.h"

void AMainGame::LoadResources() {
	SBackground.setTexture(TBackground);

	ThemeSong.setLoop(true);
	ThemeSong.play();

	LifeText.setFont(RegularFont);
	ScoreText.setFont(RegularFont);
	DeltaText.setFont(RegularFont);

	LifeText.setPosition({ 10.f, 10.f });
	ScoreText.setPosition({ 120.f, 10.f });
	DeltaText.setPosition({ 10.f, 878.f });

	LifeText.setCharacterSize(24);
	ScoreText.setCharacterSize(24);
	DeltaText.setCharacterSize(12);

	/// Reset Variables
	Obstacles.clear();
	ToKill.clear();
	Player.Reset();
	Score = 1;
	ScoreMultiplier = 1;
	GetNextLifeAt = 1000;
	ReduceSpawnTimeAt = 200;
	AddScoreMultiplierAt = 850;
	TimeToNextObstacle = 1.2;
	SpawnTime = 3.61;
}

void AMainGame::HandleInput(const sf::Event& E) {
	if (E.type == sf::Event::Closed) GameWindow.close();
	if (E.type == sf::Event::KeyPressed && E.key.code == sf::Keyboard::Key::Escape) GameWindow.close();
	if (E.type == sf::Event::KeyPressed && E.key.code == sf::Keyboard::Key::R) Game.SwitchScene(&Game.MainGame);
	Player.HandleInput(E);
}

void AMainGame::Update(double DeltaTime) {
	if (!Player.IsAlive()) Game.SwitchScene(&Game.GameOver);

	/// Update Difficulty
	if (Score >= ReduceSpawnTimeAt && SpawnTime - 0.25 > 0.6) SpawnTime -= 0.25, ReduceSpawnTimeAt *= 2;
	if (Score >= AddScoreMultiplierAt) ++ScoreMultiplier, AddScoreMultiplierAt *= 2;
	if (Score >= GetNextLifeAt) {
		GetNextLifeAt *= 2;
		if (SFXExtraLife.getStatus() != sf::Sound::Status::Playing) {
			Player.AddLife();
			SFXExtraLife.play();
		}
	}

	/// Spawning New Obstacles
	if (TimeToNextObstacle > 0) TimeToNextObstacle -= 1.0 * DeltaTime;
	else {
		Obstacles.push_back(AnObstacle(RandInt(5, 60), RandInt(5, 300), RandInt(100, 600)));
		TimeToNextObstacle = SpawnTime;
	}

	/// Updating Existing Game Objects
	Player.Update(DeltaTime);
	for (auto O = Obstacles.begin(); O != Obstacles.end(); ++O) {
		(*O).Update(DeltaTime);
		if (Player.GetCollisionArea().CollidesWith((*O).GetCollisionArea())) {
			(*O).setFillColor(sf::Color(203, 45, 76));
			Player.TakeDamage();
			Player.AddVelocity(-.5);
			(*O).bHitPlayer = true;

			if (SFXImpact.getStatus() != sf::Sound::Status::Playing) {
				SFXImpact.play();
			}
		}
		else (*O).setFillColor(sf::Color(211, 160, 170));
		if ((*O).IsAwaitingKill()) ToKill.push_back(O);
	}

	/// Kill marked obstacles
	for (const auto& I : ToKill) {
		if (!(*I).bHitPlayer) Score += 70 * ScoreMultiplier;
		Obstacles.erase(I);
	}
	ToKill.clear();

	/// Update Score
	if (ScoreClock.getElapsedTime().asSeconds() > 0.5) Score += 1, ScoreClock.restart();

	LifeText.setString("LIVES: " + ToString<double>(Player.GetLives()));
	ScoreText.setString("SCORE: " + ToString<int>(Score));
	DeltaText.setString("FPS: " + ToString<double>(1 / DeltaTime));
}

void AMainGame::Render() {
	GameWindow.clear();
	GameWindow.draw(SBackground);

	GameWindow.draw(Player);
	for (auto &O : Obstacles) {
		GameWindow.draw(O);
	}

	GameWindow.draw(LifeText);
	GameWindow.draw(ScoreText);
	GameWindow.draw(DeltaText);

	GameWindow.display();
}

void AMainGame::UnloadResources() {
	ThemeSong.stop();
}
