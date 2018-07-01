#include "lib.h"
#include "res.h"
#include "gfx.h"
#include "level.h"
#include "constants.h"
#include "vpad.h"
#include "player.h"
#include "gamestate.h"


extern Res res;
extern Vpad vpad;
Player player;
Level level;
Gamestate gamestate;
sf::Clock animtick;

void updateTick();

clock_t t = clock();


int main()
{
	srand((int) t);
	res.loadArt();
	sf::Clock clock;
	sf::Time elapsed;
	float accumulator = 0.f;
	float deltafraction = 1;


	level.load(res.levels[0]);


	//sf::RenderWindow window (sf::VideoMode(640, 480), "Roboknight Must Choose.", sf::Style::Default);
	sf::RenderWindow window (sf::VideoMode(640, 480), "Roboknight Must Choose.", sf::Style::Fullscreen);

	window.setVerticalSyncEnabled(true);

	while (window.isOpen())
	{
		elapsed = clock.restart();
		accumulator += (float) (elapsed.asMilliseconds());
		while (accumulator > TICK_TIME)
		{
			updateTick();
			accumulator -= TICK_TIME;
		}

		if (accumulator > 0.f && accumulator <= TICK_TIME)
			deltafraction = accumulator / TICK_TIME;
		else
			deltafraction = 1.f;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
		}



		window.clear();
		//window.draw(res.sprite[ballsprite]);
		drawMap(level, window);


		for (uint i = 0; i < level.entities.size(); i++)
			level.entities[i]->draw(window, deltafraction);

		player.draw(window, deltafraction);

		window.display();
	}

	return 0;
}

void updateTick()
{

	std::vector<Entity*>::iterator it;
	it = level.entities.begin();
	while (it != level.entities.end())
	{
		Entity* ent = *it;
		if (ent->isDead())
		{
			delete *it;
			it = level.entities.erase(it);
		}
		else
		{
			it++;
		}
	}



	if (gamestate.wintick > 0)
	{
		gamestate.wintick--;
		if (gamestate.wintick == 1)
		{
			gamestate.wintick = 0;
			gamestate.stage++;
			if (gamestate.stage == max_stages) gamestate.stage = 0;
			level.load(res.levels[gamestate.stage]);
		}
	}

	vpad.update();
	player.setPrevPos();
	player.update();

	for (uint i = 0; i < level.entities.size(); i++)
		level.entities[i]->setPrevPos();

	for (uint i = 0; i < level.entities.size(); i++)
		level.entities[i]->update();

}


