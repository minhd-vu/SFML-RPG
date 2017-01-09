#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <iostream>
#include <fstream>

#include "player.h"
#include "enemy.h"
#include "weapon.h"
#include "item.h"

void Player::load(std::string image, sf::Vector2f position, float maxVelocity, float acceleration, int maxhp, int maxmp, int damage, int armor)
{
	Character::load(image, position, maxVelocity, acceleration, maxhp, damage, armor);

	this->maxmp = maxmp;
	mp = this->maxmp;

	maxexp = 100;
	exp = 0;
	levels = 0;

	currency[Item::bronze_coin] = 0;
	currency[Item::silver_coin] = 0;
	currency[Item::gold_coin] = 0;
}

void Player::login()
{
	std::string loginOrRegister = "";

	while (loginOrRegister.empty())
	{
		bool loggedIn = false;

		std::cout << "Login or Register?" << std::endl;
		std::cin >> loginOrRegister;

		while (!loggedIn)
		{
			if (loginOrRegister == "login" || loginOrRegister == "Login")
			{
				std::cout << std::endl << "Username: ";
				std::string username;
				std::cin >> username;

				std::cout << "Password: ";
				std::string password;
				std::cin >> password;

				std::ifstream file("accounts.txt");
				std::string line;

				bool incorrectUsernameOrPassword = true;
				
				if (file.is_open())
				{
					while (getline(file, line))
					{
						if (line == "Username: " + username)
						{
							getline(file, line);

							if (line == "Password: " + password)
							{
								incorrectUsernameOrPassword = false;
								loggedIn = true;

								break;
							}
						}
					}

					if (incorrectUsernameOrPassword)
					{
						std::cout << std::endl << "ERROR: Username and/or Password was Incorrect." << std::endl;
					}
				}

				file.close();
			}

			else if (loginOrRegister == "register" || loginOrRegister == "Register")
			{
				bool validUsername = false;
				std::string username;

				while (!validUsername)
				{
					std::cout << std::endl << "Username: ";
					std::cin >> username;

					std::string line;
					std::ifstream file("accounts.txt");

					if (file.is_open())
					{
						while (std::getline(file, line))
						{
							if (line == "Username: " + username)
							{
								std::cout << std::endl << "That Username is Already Taken." << std::endl;
								validUsername = false;
								break;
							}

							else
							{
								validUsername = true;
							}
						}
					}

					file.close();
				}

				bool valid_password = false;
				std::string password;

				while (!valid_password)
				{
					std::cout << "Password: ";
					std::cin >> password;

					std::cout << "Confirm Password: ";
					std::string confirm_password;
					std::cin >> confirm_password;

					if (password != confirm_password)
					{
						std::cout << "Passwords Do Not Match." << std::endl;
					}

					else
					{
						valid_password = true;
					}
				}

				std::cout << "Email: ";
				std::string email;
				std::cin >> email;

				std::ofstream file("accounts.txt", std::ios_base::app);

				file << '\n';
				file << "Username: " << username << std::endl;
				file << "Password: " << password << std::endl;
				file << "Email: " << email << std::endl;

				file.close();

				std::cout << std::endl << "Please Login With Your New Account." << std::endl;

				loginOrRegister = "login";
			}

			else
			{
				std::cout << std::endl << "Please Enter A Valid Input." << std::endl << std::endl;
				loginOrRegister.clear();

				break;
			}
		}
	}
}

void Player::update(int index, Player (& player)[playerCount], Enemy (& enemy)[enemyCount], HUD &hud, Quest &quest, sf::RenderWindow &window, sf::Vector2u size, std::vector<std::vector<int>> cmap)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moveUp();

		if (hasCollision(index, player) ||
			hasCollision(enemy) ||
			hasCollision(cmap) ||
			sprite.getPosition().y < 0)
		{
			sprite.move(0.0f, -velocityUp);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moveDown();

		if (hasCollision(index, player) ||
			hasCollision(enemy) ||
			hasCollision(cmap) ||
			sprite.getPosition().y + sprite.getGlobalBounds().height > size.y)
		{
			sprite.move(0.0f, -velocityDown);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveLeft();

		if (hasCollision(index, player) ||
			hasCollision(enemy) ||
			hasCollision(cmap) ||
			sprite.getPosition().x < 0)
		{
			sprite.move(-velocityLeft, 0.0f);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveRight();

		if (hasCollision(index, player) ||
			hasCollision(enemy) ||
			hasCollision(cmap) ||
			sprite.getPosition().x + sprite.getGlobalBounds().width > size.x)
		{
			sprite.move(-velocityRight, 0.0f);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		source.y = Down;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			source.y = Up;
		}
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::L) ||
		hud.hasActivated(HUD::level, window)) &&
		levels > 0)
	{
		hasLevels();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		quest.toggle();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		
	}
}

void Player::hasDefeated(Enemy &enemy)
{
	exp += enemy.getExp();

	if (exp >= maxexp)
	{
		++level;
		++levels;
		exp -= maxexp;
		maxexp = level * 100;
	}
}

void Player::hasLevels()
{
	std::string input;

	std::cout << "What would you like to increase?\nHealth\nMana\nDamage\nArmor" << std::endl;
	std::cin >> input;

	if (input == "health" || input == "Health")
	{
		++maxhp;
		hp = maxhp;
	}

	else if (input == "mana" || input == "Mana")
	{
		++maxmp;
		mp = maxmp;
	}

	else if (input == "damage" || input == "Damage")
	{
		++damage;
	}

	else if (input == "armor" || input == "armor")
	{
		++armor;
	}

	else
	{
		std::cout << "\nERROR: Please Enter A Valid Input." << std::endl;
	}

	--levels;
}

void Player::setMaxMP(int maxmp)
{
	this->maxmp = maxmp;

	setMP(this->maxmp);
}

void Player::setMP(int mp)
{
	this->mp = mp;

	if (this->mp > maxmp)
	{
		this->mp = maxmp;
	}
}

void Player::setCurrency(int type, int amount)
{
	currency[type] = amount;

	while (currency[type] >= conversion &&
		type != Item::Items::gold_coin)
	{
		currency[type] -= conversion;
		++currency[++type];
	}
}

int Player::getMaxMP()
{
	return maxmp;
}

int Player::getMP()
{
	return mp;
}

int Player::getMaxExp()
{
	return maxexp;
}

int Player::getLevels()
{
	return levels;
}

int Player::getCurrency(int type)
{
	return currency[type];
}
