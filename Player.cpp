#include "Player.h"
#include "CollisionArea.h"

void APlayer::Slam() {
	if (!CanDoubleJump()) {
		AddVelocity(JumpStrength * 2);
		if (SFXSlam.getStatus() != sf::Sound::Status::Playing) {
			SFXSlam.play();
		}
	}
}

void APlayer::Jump() {
	if (CanJump()) {
		bIsGrounded = false;
		AddVelocity(-JumpStrength);
		if (SFXJump.getStatus() != sf::Sound::Status::Playing) {
			SFXJump.play();
		}
	}
	else if (CanDoubleJump()) {
		bHasDoubleJumped = true;
		AddVelocity(-JumpStrength);
		if (SFXDoubleJump.getStatus() != sf::Sound::Status::Playing) {
			SFXDoubleJump.play();
		}
	}
}

void APlayer::Update(double DeltaTime) {
	/// COOLDOWNS
	if (TimeToNextJump > 0) TimeToNextJump -= 1.0 * DeltaTime;
	if (TimeToNextDamage > 0) TimeToNextDamage -= 1.0 * DeltaTime;
		
	/// MOVEMENT
	AddVelocity(9.8 * DeltaTime);

	if (YPos + Velocity.y > 776.0) {
		if (abs(Velocity.y) < 2.0) Velocity.y = 0.0, YPos = 776.0;
		if (!CanJump() && SFXGroundImpact.getStatus() != sf::Sound::Status::Playing) SFXGroundImpact.play();
		bIsGrounded = true;
		bHasDoubleJumped = false;
		Velocity.y *= -0.1;
	}

	XPos += Velocity.x;
	YPos += Velocity.y;

	setPosition(XPos, YPos);

	/// ROTATION
	if (bRotatingLeft)  TargetAngle -= 5.0 * DeltaTime;
	if (bRotatingRight) TargetAngle += 5.0 * DeltaTime;

	if (TargetAngle > 3.14156 / 2) TargetAngle = 3.14156 / 2;
	if (TargetAngle < -3.14156 / 2) TargetAngle = -3.14156 / 2;

	/// Ensure the player is standing when on the ground
	if (776.0 - YPos <= 50) TargetAngle = 0.0, TurnRate = 16.0;
	else TurnRate = 4.0;

	if (RadianAngle < TargetAngle) {
		if (RadianAngle + TurnRate * DeltaTime < TargetAngle) RadianAngle += TurnRate * DeltaTime;
		else RadianAngle += TargetAngle - RadianAngle;
	}
	else if (RadianAngle > TargetAngle) {
		if (RadianAngle - TurnRate * DeltaTime > TargetAngle) RadianAngle -= TurnRate * DeltaTime;
		else RadianAngle += TargetAngle - RadianAngle;
	}

	setRotation(RadianAngle * 180 / 3.14156);
}

void APlayer::HandleInput(sf::Event InputEvent) {
	/// PRESSED KEYS ///
	if (InputEvent.type == sf::Event::KeyPressed) {
		if (InputEvent.key.code == sf::Keyboard::Key::W || InputEvent.key.code == sf::Keyboard::Key::Up) {
			Jump();
		}
		if (InputEvent.key.code == sf::Keyboard::Key::S || InputEvent.key.code == sf::Keyboard::Key::Down || InputEvent.key.code == sf::Keyboard::Key::Space) {
			Slam();
		}
		if (InputEvent.key.code == sf::Keyboard::Key::Q || InputEvent.key.code == sf::Keyboard::Key::Left) {
			bRotatingLeft = true;
		}
		if (InputEvent.key.code == sf::Keyboard::Key::E || InputEvent.key.code == sf::Keyboard::Key::Right) {
			bRotatingRight = true;
		}
	}
	/// RELEASED KEYS ///
	if (InputEvent.type == sf::Event::KeyReleased) {
		if (InputEvent.key.code == sf::Keyboard::Key::Q || InputEvent.key.code == sf::Keyboard::Key::Left) {
			bRotatingLeft = false;
		}
		if (InputEvent.key.code == sf::Keyboard::Key::E || InputEvent.key.code == sf::Keyboard::Key::Right) {
			bRotatingRight = false;
		}
	}
}

void APlayer::TakeDamage() {
	if (CanTakeDamage()) {
		--Lives;
		TimeToNextDamage = DamageDelay;
	}
}

sf::Vector2<double>& APlayer::AddVelocity(double X, double Y) {
	Velocity += sf::Vector2<double>(X, Y);
	return Velocity;
}

FCollisionArea APlayer::GetCollisionArea() const {
	sf::Vector2f TopLeft { getPosition().x - getOrigin().x, getPosition().y - getOrigin().y };
	return FCollisionArea(getSize(), TopLeft);
}
