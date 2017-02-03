#include "Obstacle.h"
#include "CollisionArea.h"

void AnObstacle::Update(double DeltaTime) {
	if (getPosition().x < -200) bAwaitingKill = true;

	XPos += Velocity.x * DeltaTime;
	YPos += Velocity.y * DeltaTime;
	setPosition(XPos, YPos);
}

FCollisionArea AnObstacle::GetCollisionArea() const {
	sf::Vector2f TopLeft{ getPosition().x - getOrigin().x, getPosition().y - getOrigin().y };
	return FCollisionArea(getSize(), TopLeft);
}