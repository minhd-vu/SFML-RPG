#include "quest.h"

void Quest::load()
{
	time = 500;
	active = false;

	font.loadFromFile("Fonts/Times/times.ttf");

	quests = 0;
	quest.setFont(font);
	quest.setCharacterSize(32.0f);
	quest.setColor(sf::Color::White);
	quest.setStyle(sf::Text::Style::Regular);
	quest.setString("Hello");

	stages = 0;
	stage.setFont(font);
	stage.setCharacterSize(16.0f);
	stage.setColor(sf::Color::White);
	stage.setStyle(sf::Text::Style::Regular);
	stage.setString("Stage");

	texture.loadFromFile("Images/menu.png");
	menu.setTexture(texture);
	menu.setColor(sf::Color::Black);
}

void Quest::toggle()
{
	if (clock.getElapsedTime().asMilliseconds() > time)
	{
		active = !active;
		clock.restart();
	}
}

void Quest::update()
{
	if (active)
	{
		switch (quests)
		{
			case 0:
				switch (stages)
				{
					case 0:
						break;
					case 1:
						break;
					case 2:
						break;
					default:
						break;
				}
				break;
			case 1:
				break;
			case 2:
				break;
			default:
				break;
		}
	}
}

void Quest::render(sf::RenderWindow &window)
{
	if (active)
	{
		window.draw(menu);
	}
}
