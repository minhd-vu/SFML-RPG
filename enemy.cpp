#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#include "enemy.h"
#include "player.h"
#include "item.h"
#include "weapon.h"

void Enemy::load(std::string image, sf::Vector2f position, float maxVelocity, float acceleration, int maxhp, int damage, int armor)
{
	Character::load(image, position, maxVelocity, acceleration, maxhp, damage, armor);

	font.loadFromFile("Fonts/Times/times.ttf");

	hpText.setFont(font);
	hpText.setCharacterSize(12);
	hpText.setStyle(sf::Text::Bold);

	deathTimer = 5000;
	alive = true;
	exp = level * 90;
}

void Enemy::update(int index, Player (&player)[playerCount], Enemy (&enemy)[enemyCount], sf::Vector2u window, std::vector<std::vector<int>> cmap)
{
	if (alive)
	{
		if (sprite.getPosition().y + 16.0f > player[0].getPosition().y + 16.0f)
		{
			moveUp();

			hasCollision(player);

			if (Character::hasCollision(player) ||
				Character::hasCollision(index, enemy) ||
				Character::hasCollision(cmap) ||
				sprite.getPosition().y < 0)
			{
				sprite.move(0.0f, -velocityUp);
			}
		}

		if (sprite.getPosition().y + 16.0f < player[0].getPosition().y + 16.0f)
		{
			moveDown();

			hasCollision(player);

			if (Character::hasCollision(player) ||
				Character::hasCollision(index, enemy) ||
				Character::hasCollision(cmap) ||
				sprite.getPosition().y + sprite.getGlobalBounds().height > window.y)
			{
				sprite.move(0.0f, -velocityDown);
			}
		}

		if (sprite.getPosition().x + 16.0f > player[0].getPosition().x + 16.0f)
		{
			moveLeft();

			hasCollision(player);

			if (Character::hasCollision(player) ||
				Character::hasCollision(index, enemy) ||
				Character::hasCollision(cmap) ||
				sprite.getPosition().x < 0)
			{
				sprite.move(-velocityLeft, 0.0f);
			}
		}

		if (sprite.getPosition().x + 16.0f < player[0].getPosition().x + 16.0f)
		{
			moveRight();

			hasCollision(player);

			if (Character::hasCollision(player) ||
				Character::hasCollision(index, enemy) ||
				Character::hasCollision(cmap) ||
				sprite.getPosition().x + sprite.getGlobalBounds().width > window.x)
			{
				sprite.move(-velocityRight, 0.0f);
			}
		}
	}

	else if (dClock.getElapsedTime().asMilliseconds() > 5000)
	{
		alive = true;

		sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));

		++level;
		++maxhp;
		++damage;
		++armor;

		exp = level * 10;

		hp = maxhp;

		for (int i = 0; i < 10; ++i)
		{
			sprite.setPosition((float)(rand() % 1921), (float)(rand() % 1081));

			if (!Character::hasCollision(player) &&
				!Character::hasCollision(index, enemy) &&
				!Character::hasCollision(cmap))
			{
				break;
			}
		}
	}

	hpText.setString(std::to_string(hp));

	if (hp > maxhp * 0.66f)
	{
		hpText.setColor(sf::Color::Green);
	}

	else if (hp <= maxhp * 0.66f || hp >= maxhp * 0.33f)
	{
		hpText.setColor(sf::Color::Yellow);
	}

	else if (hp < maxhp * 0.33f)
	{
		hpText.setColor(sf::Color::Red);
	}

	hpText.setPosition(sprite.getPosition().x + (sprite.getGlobalBounds().width - hpText.getGlobalBounds().width) / 2.0f,
		sprite.getPosition().y - hpText.getGlobalBounds().height - 2);
}

bool Enemy::isAlive()
{
	return alive;
}

void Enemy::hasDied(Item &item)
{
	alive = false;
	dClock.restart();

	srand(static_cast<unsigned int>(time(NULL)));

	switch (rand() % Item::Items::size)
	{
		case Item::Items::bronze_coin:
			item.restart
			(
				sprite.getPosition(),
				sprite.getGlobalBounds(),
				Item::Items::bronze_coin,
				5000,
				rand() % 100
			);
			break;
		case Item::Items::silver_coin:
			item.restart
			(
				sprite.getPosition(),
				sprite.getGlobalBounds(),
				Item::Items::silver_coin,
				5000,
				rand() % 100
			);
			break;
		case Item::Items::gold_coin:
			item.restart
			(
				sprite.getPosition(),
				sprite.getGlobalBounds(),
				Item::Items::gold_coin,
				5000,
				rand() % 100
			);
			break;
		case Item::Items::hp_potion_mini:
			item.restart
			(
				sprite.getPosition(),
				sprite.getGlobalBounds(),
				Item::Items::hp_potion_mini,
				5000,
				1
			);
			break;
		case Item::Items::hp_potion_medium:
			item.restart
			(
				sprite.getPosition(),
				sprite.getGlobalBounds(),
				Item::Items::hp_potion_medium,
				5000,
				1
			);
			break;
		case Item::Items::hp_potion_large:
			item.restart
			(
				sprite.getPosition(),
				sprite.getGlobalBounds(),
				Item::Items::hp_potion_large,
				5000,
				1
			);
			break;
		case Item::Items::mp_potion_mini:
			item.restart
			(
				sprite.getPosition(),
				sprite.getGlobalBounds(),
				Item::Items::mp_potion_mini,
				5000,
				1
			);
			break;
		case Item::Items::mp_potion_medium:
			item.restart
			(
				sprite.getPosition(),
				sprite.getGlobalBounds(),
				Item::Items::mp_potion_medium,
				5000,
				1
			);
			break;
		case Item::Items::mp_potion_large:
			item.restart
			(
				sprite.getPosition(),
				sprite.getGlobalBounds(),
				Item::Items::mp_potion_large,
				5000,
				1
			);
			break;
		case Item::Items::axe_weapon:
			break;
		case Item::Items::dagger_weapon:
			break;
		case Item::Items::staff_weapon:
			break;
		case Item::Items::cloth_armor:
			break;
		case Item::Items::leather_armor:
			break;
		case Item::Items::bronze_armor:
			break;
		case Item::Items::iron_armor:
			break;
		case Item::Items::steel_armor:
			break;
		default:
			break;
	}

	sprite.setPosition(-sprite.getGlobalBounds().width, -sprite.getGlobalBounds().height);
}

void Enemy::render(sf::RenderWindow & window)
{
	if (alive)
	{
		Character::render(window);
		window.draw(hpText);
	}
}

void Enemy::hasCollision(Player (&player)[playerCount])
{
	for (int i = 0; i < playerCount; ++i)
	{
		if (sprite.getGlobalBounds().intersects(player[i].getGlobalBounds()) &&
			asClock.getElapsedTime().asMilliseconds() > 500)
		{
			if (player[i].getArmor() < damage)
			{
				player[i].setHP(player[i].getHP() + player[i].getArmor() - damage);
			}

			asClock.restart();
		}
	}
}
