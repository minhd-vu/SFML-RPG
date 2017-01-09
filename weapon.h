#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "constants.h"

class Player;
class Enemy;
class Item;

class Weapon
{
public:
	void load();

	void render(sf::RenderWindow & window);
	
	void update
	(
		Player (&player)[playerCount],
		Enemy (&enemy)[enemyCount],
		Item (&item)[itemCount],
		sf::RenderWindow &window,
		std::vector<std::vector<int>> cmap
	);

	bool hasCollision
	(
		Player (&player)[playerCount],
		Enemy (&enemy)[enemyCount],
		Item (&item)[itemCount]
	);

	bool hasCollision(std::vector<std::vector<int>> cmap);

	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();

private:
	sf::Clock clock;
	sf::Clock cooldown;

	float time;
	int size;

	float frameCounter;
	float switchFrame;
	float frameSpeed;
	bool updateFrame;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i mouse;
	int source;

	std::string weapon;
	float velocity;
	float constVelocity;
	float maxVelocity;
	float acceleration;
	float maxDistance;
	float angle;
	bool isMoving;
	bool initialCast;
	bool rotationDirection;
	sf::Vector2f initialPosition;
};

#endif