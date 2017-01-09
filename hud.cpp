#include <SFML/Window/Mouse.hpp>

#include <iostream>

#include "hud.h"
#include "player.h"

void HUD::load()
{
	texture.loadFromFile("Images/hud.png");

	for (int i = 0; i < hotbarsize.y; ++i)
	{
		for (int j = 0; j < hotbarsize.x; ++j)
		{
			hotbars[i][j].setTexture(texture);
		}
	}
	
	for (int i = 0; i < hotbarsize.y; ++i)
	{
		hotbars[i][0].setTextureRect(sf::IntRect(86, 80, 6, 16));
		hotbars[i][2].setTextureRect(sf::IntRect(92, 80, 8, 16));
		hotbars[i][23].setTextureRect(sf::IntRect(100, 80, 6, 16));
	}

	hotbars[0][1].setTextureRect(sf::IntRect(32, 32, 16, 16));
	hotbars[1][1].setTextureRect(sf::IntRect(64, 32, 16, 16));
	hotbars[2][1].setTextureRect(sf::IntRect(48, 32, 16, 16));

	for (int i = initialValue; i < hotbarsize.x - 1; ++i)
	{
		hotbars[0][i].setTextureRect(sf::IntRect(92, 40, 8, 16));
		hotbars[1][i].setTextureRect(sf::IntRect(92, 60, 8, 16));
		hotbars[2][i].setTextureRect(sf::IntRect(92, 20, 8, 16));
	}

	textures[level].loadFromFile("Images/levelupicon.png");
	icons[level].setTexture(textures[level]);
}

void HUD::update(Player &player, sf::View &view)
{
	for (int i = initialValue; i < hotbarsize.x - 1; ++i)
	{
		if (player.getExp() > getValue(player.getMaxExp(), i))
		{
			hotbars[0][i].setTextureRect(sf::IntRect(92, 40, 8, 16));
		}

		else
		{
			hotbars[0][i].setTextureRect(sf::IntRect(84, 0, 8, 16));
		}

		if (player.getMP() >= getValue(player.getMaxMP(), i))
		{
			hotbars[1][i].setTextureRect(sf::IntRect(92, 60, 8, 16));
		}

		else
		{
			hotbars[1][i].setTextureRect(sf::IntRect(84, 0, 8, 16));
		}
		
		if (player.getHP() >= getValue(player.getMaxHP(), i))
		{
			hotbars[2][i].setTextureRect(sf::IntRect(92, 20, 8, 16));
		}

		else
		{
			hotbars[2][i].setTextureRect(sf::IntRect(84, 0, 8, 16));
		}
	}

	for (int i = 0; i < hotbarsize.y; ++i)
	{
		hotbars[i][0].setPosition(view.getCenter().x - view.getSize().x / 2 + 2,
			(view.getCenter().y + view.getSize().y / 2) - (i * hotbars[i][0].getGlobalBounds().height) - hotbars[i][0].getGlobalBounds().height - 2.0f);
		hotbars[i][1].setPosition(view.getCenter().x - view.getSize().x / 2 + 8,
			(view.getCenter().y + view.getSize().y / 2) - (i * hotbars[i][0].getGlobalBounds().height) - hotbars[i][0].getGlobalBounds().height - 2.0f);

		for (int j = 2; j < hotbarsize.x; ++j)
		{
			hotbars[i][j].setPosition(hotbars[i][j - 1].getPosition().x + hotbars[i][j - 1].getGlobalBounds().width, hotbars[i][j - 1].getPosition().y);
		}
	}

	if (player.getLevels() > 0)
	{
		icon[level] = true;
		icons[level].setPosition(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
	}

	else
	{
		icon[level] = false;
	}
}

void HUD::render(sf::RenderWindow &window)
{
	for (int i = 0; i < hotbarsize.y; ++i)
	{
		for (int j = 0; j < hotbarsize.x; ++j)
		{
			window.draw(hotbars[i][j]);
		}
	}


	if (icon[level])
	{
		window.draw(icons[level]);
	}
}

bool HUD::hasActivated(int icon, sf::RenderWindow &window)
{
	if (icons[icon].getGlobalBounds().contains(sf::Mouse::getPosition(window).x + window.getView().getCenter().x - window.getSize().x / 2,
		sf::Mouse::getPosition(window).y + window.getView().getCenter().y - window.getSize().y / 2) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		return true;
	}

	return false;
}

int HUD::getValue(int value, int loop)
{
	return (loop * (value / (hotbarsize.x - initialValue - 1))) - (initialValue * (value / (hotbarsize.x - initialValue - 1)));
}
