#pragma once
#ifndef QUEST_H
#define QUEST_H

#include <iostream>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Quest
{
public:
	void load();

	void toggle();
	void update();

	void render(sf::RenderWindow &window);

private:
	int time;
	bool active;

	sf::Clock clock;

	sf::Font font;

	int quests;
	sf::Text quest;

	int stages;
	sf::Text stage;

	sf::Texture texture;
	sf::Sprite menu;
};

#endif