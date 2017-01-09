#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

#include "constants.h"

class Player;
class Enemy;
class Weapon;

class Character
{
public:
	enum Direction
	{
		Down,
		Left,
		Right,
		Up
	};

	void render(sf::RenderWindow & window);

	void setTexture(const sf::Texture & texture);
	void setPosition(float x, float y);
	void setSpeed(float maxVelocity, float acceleration);
	void setMaxHP(int maxhp);
	void setHP(int hp);
	void setLevel(int level);
	void setExp(int exp);
	void setDamage(int damage);
	void setArmor(int armor);

	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
	int getMaxHP();
	int getHP();
	int getLevel();
	int getExp();
	int getDamage();
	int getArmor();

protected:
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

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	bool hasCollision(Player (&player)[playerCount]);
	bool hasCollision(int index, Player (&player)[playerCount]);
	bool hasCollision(Enemy (&enemy)[enemyCount]);
	bool hasCollision(int index, Enemy (&enemy)[enemyCount]);
	bool hasCollision(std::vector<std::vector<int>> cmap);

	float frameCounter;
	float switchFrame;
	float frameSpeed;
	bool updateFrame;
	bool initialFrame;
	
	sf::Clock clock;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i source;

	float velocityUp;
	float velocityDown;
	float velocityLeft;
	float velocityRight;

	float maxVelocity;
	float acceleration;

	int maxhp;
	int hp;
	int level;
	int exp;
	int damage;
	int armor;
};

#endif