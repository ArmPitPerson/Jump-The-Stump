#pragma once
#ifndef COLLISION_AREA_H
#define COLLISION_AREA_H

#include "SFML/System/Vector2.hpp"

struct FCollisionArea {
	FCollisionArea() : TopLeftCorner({ 0.f, 0.f }) {};
	FCollisionArea(sf::Vector2f VSize, sf::Vector2f TopLeft) : Size(VSize), TopLeftCorner(TopLeft) {}

	sf::Vector2f Size;
	sf::Vector2f TopLeftCorner;

	bool CollidesWith(FCollisionArea OtherArea);
};

#endif
