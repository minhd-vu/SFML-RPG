#include "item.h"
#include "player.h"

void Item::load()
{
	texture.loadFromFile("Images/items_new.png");
	sprite.setTexture(texture);
	active = false;
}

void Item::restart(sf::Vector2f location, sf::FloatRect dimensions, int type, int time, int amount)
{
	active = true;

	this->type = type;
	this->time = time;
	this->amount = amount;

	switch (this->type)
	{
		case bronze_coin:
			sprite.setTextureRect(sf::IntRect(417, 519, 16, 16));
			break;
		case silver_coin:
			sprite.setTextureRect(sf::IntRect(383, 519, 16, 16));
			break;
		case gold_coin:
			sprite.setTextureRect(sf::IntRect(347, 519, 16, 16));
			break;
		case hp_potion_mini:
			sprite.setTextureRect(sf::IntRect(250, 71, 11, 29));
			break;
		case hp_potion_medium:
			sprite.setTextureRect(sf::IntRect(249, 105, 13, 28));
			break;
		case hp_potion_large:
			sprite.setTextureRect(sf::IntRect(6, 71, 21, 29));
			break;
		case mp_potion_mini:
			sprite.setTextureRect(sf::IntRect(352, 71, 11, 29));
			break;
		case mp_potion_medium:
			sprite.setTextureRect(sf::IntRect(351, 105, 13, 28));
			break;
		case mp_potion_large:
			sprite.setTextureRect(sf::IntRect(109, 71, 21, 29));
			break;
		case axe_weapon:
			break;
		case dagger_weapon:
			break;
		case staff_weapon:
			break;
		case cloth_armor:
			break;
		case leather_armor:
			break;
		case bronze_armor:
			break;
		case iron_armor:
			break;
		case steel_armor:
			break;
		default:
			break;
	}

	sprite.setPosition(location.x + (dimensions.width - sprite.getGlobalBounds().width) / 2.0f,
		location.y + (dimensions.height - sprite.getGlobalBounds().height) / 2.0f);

	clock.restart();
}

void Item::update(Player & player)
{
	if (clock.getElapsedTime().asMilliseconds() < time &&
		hasCollision(player) && active)
	{
		switch (type)
		{
			case bronze_coin:
				player.setCurrency(bronze_coin, player.getCurrency(bronze_coin) + amount);
				break;
			case silver_coin:
				player.setCurrency(silver_coin, player.getCurrency(silver_coin) + amount);
				break;
			case gold_coin:
				player.setCurrency(gold_coin, player.getCurrency(gold_coin) + amount);
				break;
			case hp_potion_mini:
				player.setHP(player.getHP() + hp[mini] * amount);
				break;
			case hp_potion_medium:
				player.setHP(player.getHP() + hp[medium] * amount);
				break;
			case hp_potion_large:
				player.setHP(player.getHP() + hp[large] * amount);
				break;
			case mp_potion_mini:
				player.setMP(player.getMP() + mp[mini] * amount);
				break;
			case mp_potion_medium:
				player.setMP(player.getMP() + mp[medium] * amount);
				break;
			case mp_potion_large:
				player.setMP(player.getMP() + mp[large] * amount);
				break;
			case axe_weapon:
				break;
			case dagger_weapon:
				break;
			case staff_weapon:
				break;
			case cloth_armor:
				break;
			case leather_armor:
				break;
			case bronze_armor:
				break;
			case iron_armor:
				break;
			case steel_armor:
				break;
			default:
				break;
		}

		active = false;
	}

	else if (clock.getElapsedTime().asMilliseconds() > time)
	{
		active = false;
	}
}

void Item::render(sf::RenderWindow & window)
{
	if (active)
	{
		window.draw(sprite);
	}
}

bool Item::hasCollision(Player & player)
{
	return sprite.getGlobalBounds().intersects(player.getGlobalBounds()) ||
		player.getGlobalBounds().intersects(sprite.getGlobalBounds());
}
