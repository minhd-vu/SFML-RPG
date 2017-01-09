#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>

#include "character.h"
#include "constants.h"
#include "item.h"

class Item;

class Enemy : public Character
{
public:
	void load
	(
		std::string image,
		sf::Vector2f position,
		float maxVelocity,
		float acceleration, 
		int maxhp,
		int damage,
		int armor
	);
	
	void update
	(
		int index,
		Player (&player)[playerCount],
		Enemy (&enemy)[enemyCount],
		sf::Vector2u window,
		std::vector<std::vector<int>> cmap
	);

	bool isAlive();
	void hasDied(Item &item);

	void render(sf::RenderWindow &window);

private:
	bool alive;

	sf::Clock asClock;
	sf::Clock dClock;

	int deathTimer;

	sf::Font font;
	sf::Text hpText;

	void hasCollision(Player (&player)[playerCount]);
};

#endif
