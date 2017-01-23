#include "CollisionArea.h"

bool FCollisionArea::CollidesWith(FCollisionArea OtherArea) {
	if (TopLeftCorner.x < OtherArea.TopLeftCorner.x + OtherArea.Size.x &&
		TopLeftCorner.x + Size.x > OtherArea.TopLeftCorner.x &&
		TopLeftCorner.y < OtherArea.TopLeftCorner.y + OtherArea.Size.y &&
		TopLeftCorner.y + Size.y > OtherArea.TopLeftCorner.y) {
		return true;
	}
	return false;
}