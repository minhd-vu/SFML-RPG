#define _USE_MATH_DEFINES

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <cmath>

#include "weapon.h"
#include "player.h"
#include "enemy.h"

void Weapon::load()
{
	frameCounter = 0;
	switchFrame = 100;
	frameSpeed = 500;
	updateFrame = true;
	source = 0;

	isMoving = false;
	initialCast = true;

	texture.loadFromFile("Images/items.png");
	sprite.setTexture(texture);

	while (weapon.empty())
	{
		std::string input;

		std::cout << "\nPlease Choose A Class: Warrior, Rogue, Mage." << std::endl;
		std::cin >> input;

		if (input == "Warrior" || input == "warrior")
		{
			sprite.setTextureRect(sf::IntRect(68, 342, 32, 32));

			weapon = "axe";
			constVelocity = 6.0f;
			velocity = 6.0f;
			maxVelocity = 3.0f;
			acceleration = 0.1f;
			maxDistance = 256.0f;
			time = 1.0f;
			size = 32;
			break;
		}

		else if (input == "Rogue" || input == "rogue")
		{
			sprite.setTextureRect(sf::IntRect(42, 212, 18, 18));

			weapon = "dagger";
			constVelocity = 9.0f;
			velocity = 9.0f;
			maxVelocity = 6.0f;
			acceleration = 0.1f;
			maxDistance = 256.0f;
			time = 1.0f;
			size = 18;
			break;
		}

		else if (input == "Mage" || input == "mage")
		{
			texture.loadFromFile("Images/fireball.png");
			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

			weapon = "fireball";
			constVelocity = 3.0f;
			velocity = 3.0f;
			maxVelocity = 9.0f;
			acceleration = 0.1f;
			maxDistance = 256.0f;
			time = 1.0f;
			size = 32;
			break;
		}

		else
		{
			std::cout << "\nPlease Enter A Valid Input." << std::endl;
		}
	}

	sprite.setPosition(-sprite.getGlobalBounds().width, -sprite.getGlobalBounds().height);
}

void Weapon::render(sf::RenderWindow & window)
{
	if (weapon == "fireball")
	{
		frameCounter = (updateFrame) ? frameCounter + frameSpeed * clock.restart().asSeconds() : 0;

		if (frameCounter >= switchFrame)
		{
			frameCounter = 0;
			++source;

			if (source * (unsigned)32 >= texture.getSize().x)
			{
				source = 0;
			}
		}

		sprite.setTextureRect(sf::IntRect(source * size, 0, size, size));
	}

	if (velocity > 0 && isMoving)
	{
		window.draw(sprite);
	}
}

void Weapon::update(Player (&player)[playerCount], Enemy (&enemy)[enemyCount], Item(&item)[itemCount], sf::RenderWindow &window, std::vector<std::vector<int>> cmap)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !isMoving && (cooldown.getElapsedTime().asSeconds() > time || initialCast))
	{
		mouse = sf::Mouse::getPosition(window) + (sf::Vector2i)window.getView().getCenter() - ((sf::Vector2i)window.getSize() / 2);

		angle = (atan2(player[0].getPosition().y - mouse.y, player[0].getPosition().x - mouse.x)) * 180.0f / (float)M_PI;

		sprite.setRotation(0.0f);
		sprite.setPosition(player[0].getPosition().x + player[0].getGlobalBounds().width / 2.0f, player[0].getPosition().y + player[0].getGlobalBounds().height / 2.0f);
		sprite.setOrigin(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f);
		sprite.setRotation(angle);

		initialPosition = sprite.getPosition();

		if (player[0].getPosition().x - mouse.x > 0)
		{
			rotationDirection = true;
		}

		else
		{
			rotationDirection = false;
		}

		isMoving = true;

		if (initialCast)
		{
			initialCast = false;
		}
	}

	else if (isMoving)
	{
		if (weapon == "axe" || weapon == "dagger")
		{
			if (velocity > maxVelocity)
			{
				velocity -= acceleration;
			}

			if (rotationDirection)
			{
				sprite.rotate(-9.0f);
			}

			else
			{
				sprite.rotate(9.0f);
			}
		}

		else if (weapon == "fireball")
		{
			if (velocity < maxVelocity)
			{
				velocity += acceleration;
			}
		}

		sprite.move(-1 * (float)cos(M_PI * angle / 180.0f) * velocity, -1 * (float)sin(M_PI * angle / 180.0f) * velocity);

		sf::Vector2f asip(sprite.getPosition().x - initialPosition.x, sprite.getPosition().y - initialPosition.y);

		if (sqrt(asip.x * asip.x + asip.y * asip.y) > maxDistance ||
			hasCollision(player, enemy, item) ||
			hasCollision(cmap))
		{
			sprite.setPosition(-sprite.getGlobalBounds().width, -sprite.getGlobalBounds().height);
			
			velocity = constVelocity;
			isMoving = false;

			cooldown.restart().asSeconds();
		}
	}
}

bool Weapon::hasCollision(Player (&player)[playerCount], Enemy (&enemy)[enemyCount], Item(&item)[itemCount])
{
	for (int i = 0; i < enemyCount; ++i)
	{
		if (sprite.getGlobalBounds().contains(enemy[i].getPosition().x + 16.0f, enemy[i].getPosition().y + 16.0f))
		{
			if (enemy[i].isAlive() && enemy[i].getArmor() < player[0].getDamage())
			{
				enemy[i].setHP(enemy[i].getHP() + enemy[i].getArmor() - player[0].getDamage());

				if (enemy[i].getHP() <= 0)
				{
					player[0].hasDefeated(enemy[i]);
					enemy[i].hasDied(item[i]);
				}
			}

			return true;
		}
	}

	return false;
}

bool Weapon::hasCollision(std::vector<std::vector<int>> cmap)
{
	for (int i = 0; i < cmap.size(); ++i)
	{
		for (int j = 0; j < cmap[i].size(); ++j)
		{
			if (cmap[i][j] > 0)
			{
				if (sprite.getGlobalBounds().contains(sf::Vector2f(j * 32.0f + 16.0f, i * 32.0f + 16.0f)))
				{
					return true;
				}
			}
		}
	}

	return false;
}

sf::Vector2f Weapon::getPosition()
{
	return sprite.getPosition();
}

sf::FloatRect Weapon::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}
