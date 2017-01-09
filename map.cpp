#include <sstream>
#include <fstream>

#include "map.h"

void Map::load(const std::string file)
{
	openfile.open(file);

	if (openfile.is_open() && !openfile.eof())
	{
		std::string str;

		std::getline(openfile, str);

		texture.loadFromFile(str);
		tiles.setTexture(texture);

		while (!openfile.eof())
		{
			std::getline(openfile, str);
			std::stringstream stream(str);
			std::string value;

			while (std::getline(stream, value, ' '))
			{
				if (value.length() > 0)
				{
					std::string x = value.substr(0, value.find(','));
					std::string y = value.substr(value.find(',') + 1);

					std::stringstream xconv(x);
					std::stringstream yconv(y);
					sf::Vector2i conv;

					if (!(xconv >> conv.x))
					{
						conv.x = 0;
					}

					if (!(yconv >> conv.y))
					{
						conv.y = 0;
					}

					temp.push_back(conv);
				}
			}

			map.push_back(temp);
			temp.clear();
		}
	}

	openfile.close();
}

void Map::render(sf::RenderWindow & window)
{
	for (int i = 0; i < map.size(); ++i)
	{
		for (int j = 0; j < map[i].size(); ++j)
		{
			if (map[i][j].x != -1 && map[i][j].y != -1)
			{
				tiles.setPosition(j * 32.0f, i * 32.0f);
				tiles.setTextureRect(sf::IntRect(map[i][j].x * 32, map[i][j].y * 32, 32, 32));
				window.draw(tiles);
			}
		}
	}
}

void HMap::load(const std::string file)
{
	texture.loadFromFile("Images/menu.png");
	menu.setTexture(texture);
}

void HMap::render(sf::RenderWindow & window)
{
	menu.setPosition(window.getView().getCenter().x - (window.getSize().x / 2.0f - menu.getGlobalBounds().width),
		window.getView().getCenter().y - (window.getSize().y / 2.0f - menu.getGlobalBounds().height));

	for (int i = 0; i < map.size(); ++i)
	{
		for (int j = 0; j < map[i].size(); ++j)
		{
			if (map[i][j].x != -1 && map[i][j].y != -1)
			{
				tiles.setPosition(menu.getPosition().x + j * 32.0f, menu.getPosition().y + i * 32.0f);
				tiles.setTextureRect(sf::IntRect(map[i][j].x * 32, map[i][j].y * 32, 32, 32));
				window.draw(tiles);
			}
		}
	}
}

void CMap::load(const std::string file)
{
	openfile.open(file);

	if (openfile.is_open() && !openfile.eof())
	{
		std::string str;

		std::getline(openfile, str);

		while (!openfile.eof())
		{
			std::getline(openfile, str);
			std::stringstream stream(str);
			std::string value;

			while (std::getline(stream, value, ' '))
			{
				if (value.length() > 0)
				{
					int i = atoi(value.c_str());
					temp.push_back(i);
				}
			}

			if (temp.size() > 0)
			{
				map.push_back(temp);
				temp.clear();
			}
		}
	}

	openfile.close();
}

std::vector<std::vector<int>> CMap::getMap()
{
	return map;
}
