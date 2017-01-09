#pragma once
#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <fstream>

class Player;

class Map
{
public:
	virtual void load(const std::string file);
	virtual void render(sf::RenderWindow & window);

protected:
	std::ifstream openfile;
	std::vector<std::vector<sf::Vector2i>> map;
	std::vector<sf::Vector2i> temp;
	sf::Sprite tiles;
	sf::Texture texture;
};

class HMap : Map
{
public:
	void load(const std::string file);
	void render(sf::RenderWindow & window);

private:
	sf::Sprite menu;
};

class CMap
{
public:
	void load(const std::string file);

	std::vector<std::vector<int>> getMap();

private:
	std::ifstream openfile;
	std::vector<std::vector<int>> map;
	std::vector<int> temp;
};

#endif