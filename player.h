#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

#include "character.h"
#include "constants.h"
#include "hud.h"
#include "quest.h"

class HUD;
class Quest;

class Player : public Character
{
public:
	void load
	(
		std::string image,
		sf::Vector2f position,
		float maxVelocity,
		float accerleration,
		int maxhp,
		int maxmp,
		int damage,
		int armor
	);

	void login();

	void update
	(
		int index,
		Player(&player)[playerCount],
		Enemy(&enemy)[enemyCount],
		HUD &hud,
		Quest &quest,
		sf::RenderWindow &window,
		sf::Vector2u size,
		std::vector<std::vector<int>> cmap
	);

	void hasDefeated(Enemy &enemy);
	void hasLevels();

	void setMaxMP(int maxmp);
	void setMP(int mp);
	void setCurrency(int type, int amount);

	int getMaxMP();
	int getMP();
	int getMaxExp();
	int getLevels();
	int getCurrency(int type);

private:
	int maxmp;
	int mp;
	int maxexp;
	int levels;

	const int conversion = 100;
	int currency[3];
};

#endif