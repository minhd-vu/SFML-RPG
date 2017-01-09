#include "engine.h"

void Engine::load()
{
	SetConsoleTitle("Minh Dynasty");

	for (int i = 0; i < mapCount; ++i)
	{
		map[i].load("map" + std::to_string(i) + ".txt");
	}

	cmap.load("map3.txt");
	hmap.load("map4.txt");

	player[0].load("player", sf::Vector2f(256.0f, 256.0f), 2.0f, 2.0f, 100, 100, 100, 0);
	player[1].load("player", sf::Vector2f(512.0f, 512.0f), 2.0f, 2.0f, 100, 100, 1, 0);

	//player[0].login();

	enemy[0].load("enemy", sf::Vector2f(64.0f, 64.0f), 1.0f, 1.0f, 100, 1, 0);
	enemy[1].load("enemy", sf::Vector2f(128.0f, 128.0f), 1.0f, 1.0f, 100, 1, 0);

	item[0].load();
	item[1].load();

	weapon.load();

	state = Menu;

	window.create(sf::VideoMode(800, 600), "Minh Dynasty", sf::Style::Default);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	size = sf::Vector2u((int)cmap.getMap()[0].size() * 32,
		(int)cmap.getMap().size() * 32);
	view.setSize((sf::Vector2f)window.getSize());

	hud.load();
	quest.load();
}

void Engine::run()
{
	while (window.isOpen())
	{
		sf::Event Event;
		
		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		update();
		render();
	}
}

void Engine::update()
{
	if (window.hasFocus())
	{
		player[0].update(0, player, enemy, hud, quest, window, size, cmap.getMap());

		for (int i = 0; i < enemyCount; ++i)
		{
			enemy[i].update(i, player, enemy, size, cmap.getMap());
		}

		for (int i = 0; i < itemCount; ++i)
		{
			item[i].update(player[0]);
		}

		weapon.update(player, enemy, item, window, cmap.getMap());

		view.setCenter(player[0].getPosition().x + player[0].getGlobalBounds().width / 2.0f,
			player[0].getPosition().y + player[0].getGlobalBounds().width / 2.0f);

		hud.update(player[0], view);
		quest.update();
	}

	/*
	if (state == Play)
	{
		if (window.hasFocus())
		{
			update();
		}

		else
		{
			state = Pause;
		}
	}

	else if (state == Pause)
	{
		pause();
	}
	*/
}

void Engine::render()
{
	window.clear();
	window.setView(view);

	map[0].render(window);
	map[1].render(window);

	for (int i = 0; i < itemCount; ++i)
	{
		item[i].render(window);
	}

	for (int i = 0; i < playerCount; ++i)
	{
		player[i].render(window);
	}

	for (int i = 0; i < enemyCount; ++i)
	{
		enemy[i].render(window);
	}

	weapon.render(window);
	map[2].render(window);
	hud.render(window);
	quest.render(window);
	hmap.render(window);

	window.display();
}

void Engine::menu()
{

}

void Engine::pause()
{

}

void Engine::death()
{

}

void Engine::help()
{

}

void Engine::settings()
{

}

void Engine::exit()
{

}
