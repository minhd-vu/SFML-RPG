#include "character.h"
#include "player.h"
#include "enemy.h"
#include "weapon.h"

void Character::render(sf::RenderWindow &window)
{
	frameCounter = (updateFrame) ? frameCounter + frameSpeed * clock.restart().asSeconds() : 0;

	if (frameCounter >= switchFrame)
	{
		frameCounter = 0;

		++source.x;

		if (source.x * (unsigned)32 >= texture.getSize().x)
		{
			source.x = 0;
		}
	}

	if (velocityUp < 0 || velocityDown > 0 || velocityLeft < 0 || velocityRight > 0 || initialFrame)
	{
		sprite.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));

		if (initialFrame)
		{
			initialFrame = false;
		}
	}

	window.draw(sprite);
}

void Character::setTexture(const sf::Texture & texture)
{
	this->texture = texture;
	sprite.setTexture(this->texture);
}

void Character::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void Character::setSpeed(float maxVelocity, float acceleration)
{
	this->maxVelocity = maxVelocity;
	this->acceleration = acceleration;
}

void Character::setMaxHP(int maxhp)
{
	this->maxhp = maxhp;

	setHP(this->maxhp);
}

void Character::setHP(int hp)
{
	this->hp = hp;

	if (this->hp > maxhp)
	{
		this->hp = maxhp;
	}
}

void Character::setLevel(int level)
{
	this->level = level;
}

void Character::setExp(int exp)
{
	this->exp = exp;
}

void Character::setDamage(int damage)
{
	this->damage = damage;
}

void Character::setArmor(int armor)
{
	this->armor = armor;
}

sf::Vector2f Character::getPosition()
{
	return sprite.getPosition();
}

sf::FloatRect Character::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

int Character::getMaxHP()
{
	return maxhp;
}

int Character::getHP()
{
	return hp;
}

int Character::getLevel()
{
	return level;
}

int Character::getExp()
{
	return exp;
}

int Character::getDamage()
{
	return damage;
}

int Character::getArmor()
{
	return armor;
}

void Character::load(std::string image, sf::Vector2f position, float maxVelocity, float acceleration, int maxhp, int damage, int armor)
{
	texture.loadFromFile("Images/" + image + ".png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
	sprite.setPosition(position);

	frameCounter = 0;
	switchFrame = 100;
	frameSpeed = 500;
	updateFrame = true;
	initialFrame = true;

	velocityUp = 0;
	velocityDown = 0;
	velocityLeft = 0;
	velocityRight = 0;

	this->maxVelocity = maxVelocity;
	this->acceleration = acceleration;

	this->maxhp = maxhp;
	hp = this->maxhp;
	level = 1;
	this->damage = damage;
	this->armor = armor;
}

void Character::moveUp()
{
	source.y = Up;
	
	if (velocityUp > -maxVelocity)
	{
		velocityUp -= acceleration;
	}
	
	sprite.move(0.0f, velocityUp);
}

void Character::moveDown()
{
	source.y = Down;
	
	if (velocityDown < maxVelocity)
	{
		velocityDown += acceleration;
	}
	
	sprite.move(0.0f, velocityDown);
}

void Character::moveLeft()
{
	source.y = Left;

	if (velocityLeft > -maxVelocity)
	{
		velocityLeft -= acceleration;
	}

	sprite.move(velocityLeft, 0.0f);
}

void Character::moveRight()
{
	source.y = Right;

	if (velocityRight < maxVelocity)
	{
		velocityRight += acceleration;
	}

	sprite.move(velocityRight, 0.0f);
}

bool Character::hasCollision(Player (&player)[playerCount])
{
	for (int i = 0; i < playerCount; ++i)
	{
		if (sprite.getGlobalBounds().intersects(player[i].getGlobalBounds()))
		{
			return true;
		}
	}

	return false;
}

bool Character::hasCollision(int index, Player (&player)[playerCount])
{
	for (int i = 0; i < playerCount; ++i)
	{
		if (sprite.getGlobalBounds().intersects(player[i].getGlobalBounds()) &&
			i != index)
		{
			return true;
		}
	}

	return false;
}

bool Character::hasCollision(Enemy (&enemy)[enemyCount])
{
	for (int i = 0; i < enemyCount; ++i)
	{
		if (sprite.getGlobalBounds().intersects(enemy[i].getGlobalBounds()))
		{
			return true;
		}
	}

	return false;
}

bool Character::hasCollision(int index, Enemy (&enemy)[enemyCount])
{
	for (int i = 0; i < enemyCount; ++i)
	{
		if (sprite.getGlobalBounds().intersects(enemy[i].getGlobalBounds()) &&
			i != index)
		{
			return true;
		}
	}

	return false;
}

bool Character::hasCollision(std::vector<std::vector<int>> cmap)
{
	for (int i = 0; i < cmap.size(); ++i)
	{
		for (int j = 0; j < cmap[i].size(); ++j)
		{
			if (cmap[i][j] > 0)
			{
				if (sprite.getGlobalBounds().intersects(sf::FloatRect(j * 32.0f, i  * 32.0f, 32.0f, 32.0f)))
				{
					return true;
				}
			}
		}
	}

	return false;
}
