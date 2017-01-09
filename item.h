#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Player;

class Item
{
public:
	enum Items
	{
		bronze_coin,
		silver_coin,
		gold_coin,
		hp_potion_mini,
		hp_potion_medium,
		hp_potion_large,
		mp_potion_mini,
		mp_potion_medium,
		mp_potion_large,
		axe_weapon,
		dagger_weapon,
		staff_weapon,
		cloth_armor,
		leather_armor,
		bronze_armor,
		iron_armor,
		steel_armor,
		size
	};

	void load();

	void restart
	(
		sf::Vector2f location,
		sf::FloatRect dimensions,
		int type,
		int time,
		int amount
	);

	void update(Player &player);

	void render(sf::RenderWindow &window);

private:
	bool hasCollision(Player &player);

	sf::Clock clock;

	sf::Texture texture;
	sf::Sprite sprite;

	bool active;

	int type;
	int time;
	int amount;

	enum Size
	{
		mini,
		medium,
		large
	};

	const int hp[4] =
	{
		10,
		25,
		50
	};

	const int mp[4] = 
	{
		10,
		25,
		50
	};
};

#endif
