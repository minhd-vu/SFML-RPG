#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <windows.h>
#include <iostream>

#include "hud.h"
#include "map.h"
#include "player.h"
#include "enemy.h"
#include "item.h"
#include "weapon.h"
#include "constants.h"

class Engine
{
public:
	void load();
	void run();

private:
	void update();
	void render();

	void menu();
	void pause();
	void death();
	void help();
	void settings();
	void exit();

	enum State
	{
		Play,
		Menu,
		Pause,
		Death,
		Help,
		Settings,
		Exit
	};
	
	int state;

	sf::RenderWindow window;
	sf::Vector2u size;
	sf::View view;

	HUD hud;
	Quest quest;

	Map map[mapCount];
	CMap cmap;
	HMap hmap;

	sf::Texture playerTexture[playerCount];
	sf::Texture enemyTexture[enemyCount];

	Player player[playerCount];
	Enemy enemy[enemyCount];
	Item item[itemCount];
	Weapon weapon;
};

#endif