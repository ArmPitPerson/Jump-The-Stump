#pragma once
#ifndef CENTERTEXT_H
#define CENTERTEXT_H

#include "SFML/Graphics/Text.hpp"

class CenteredText : public sf::Text {
public:
	CenteredText() : sf::Text() { Center(0.f, 0.f); }
	CenteredText(const sf::Font& FontToUse, float XOffset, float YOffset) : sf::Text() { setFont(FontToUse); Center(XOffset, YOffset); }

	void Center(float XOffset, float YOffset) {
		auto Bounds = getLocalBounds();
		setOrigin(Bounds.left + Bounds.width / 2, Bounds.top + Bounds.height / 2);
		setPosition(1600 / 2 + XOffset, 900 / 2 + YOffset);
	}
};
#endif // CENTERTEXT_H