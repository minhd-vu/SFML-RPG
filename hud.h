#pragma once
#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "constants.h"

class Player;

class HUD
{
public:
	enum Icon
	{
		level,
		quest,
		size
	};

	void load();

	void update
	(
		Player &player,
		sf::View &view
	);

	void render(sf::RenderWindow &window);

	bool hasActivated(int icon, sf::RenderWindow &window);

private:
	int getValue(int value, int loop);

	sf::Texture texture;
	sf::Sprite hotbars[3][24];
	const int initialValue = 3;
	const sf::Vector2i hotbarsize = sf::Vector2i(24, 3);

	sf::Texture textures[size];
	sf::Sprite icons[size];
	sf::Vector2f locations[size];
	bool icon[size];
};

#endif