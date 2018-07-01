#include "level.h"
#include "player.h"
#include "things.h"
#include "entity.h"

extern Player player;

void Level::load(std::string filename)
{
	for(uint i = 0; i < entities.size(); i++)
		delete entities[i];

	entities.clear();

	sf::Image src;
	currentlevel = filename;
	src.loadFromFile(filename);

	int w = src.getSize().x;
	int h = src.getSize().y;

	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++)
		{
			sf::Color p = src.getPixel(x, y);

			if (p == sf::Color::Black) { data[x][y] = notile; };
			if (p == sf::Color(38, 127, 0)) { data[x][y] = grasstoptile; };
			if (p == sf::Color(127, 51, 0)) { data[x][y] = dirttile; };
			if (p == sf::Color(128, 128, 128)) { data[x][y] = stonetile; };
			if (p == sf::Color::White) { data[x][y] = bgbluetile; playerStart = vec2(x, y); };
			if (p == sf::Color(0, 19, 127)) { data[x][y] = bgbluetile; };
			if (p == sf::Color(255, 106, 0)) {data[x][y] = lava1; };
			if (p == sf::Color(191, 76, 0)) {data[x][y] = lavamix1; };
			if (p == sf::Color(0, 148, 255)) {data[x][y] = spiketile; };
			if (p == sf::Color(255, 0, 0)) { data[x][y] = greenballtile; entities.push_back(new Fireball(x, y)); };
			if (p == sf::Color(200, 0, 0)) { data[x][y] = greenballtile; entities.push_back(new Fireball(x, y, true)); };
			if (p == sf::Color(255, 0, 110)) { data[x][y] = bgbluetile; entities.push_back(new Maiden(x, y)); };
			if (p == sf::Color(127, 0, 55)) { data[x][y] = bgbluetile; entities.push_back(new Bat(x, y, false)); };
			if (p == sf::Color(95, 0, 55)) { data[x][y] = bgbluetile; entities.push_back(new Bat(x, y, true)); };
			if (p == sf::Color(0, 255, 33)) { data[x][y] = bgbluetile; entities.push_back(new Goblin(x, y)); };
			if (p == sf::Color(0, 38, 255)) { data[x][y] = bluetile; };
			if (p == sf::Color(255, 70, 0)) { data[x][y] = magma; };
			if (p == sf::Color(125, 0, 125)) { data[x][y] = bluemagma; };
			if (p == sf::Color(255, 216, 0)) { data[x][y] = bridge; };
			if (p == sf::Color(0, 50, 0)) { data[x][y] = pipeblock; };
			if (p == sf::Color(0, 60, 0)) { data[x][y] = vpipe; };
			if (p == sf::Color(0, 70, 0)) { data[x][y] = hpipe; };
			if (p == sf::Color(0, 0, 50)) { data[x][y] = crystaltile; };
			if (p == sf::Color(63, 25, 0)) { data[x][y] = orangetile; };
			if (p == sf::Color(63, 25, 0)) { data[x][y] = orangetile; };
			if (p == sf::Color(127, 0, 0)) { data[x][y] = keyblock; };
			if (p == sf::Color(255, 233, 127)) { data[x][y] = bgbluetile; entities.push_back(new Pickup(x, y)); };

		}
	}

	player.reset(playerStart);

	for (uint i = 0; i < entities.size(); i++)
		entities[i]->setPrevPos();
}

tiledex Level::tileAt(vec2 fx_pos)
{
	vec2 pos;
	pos.x = unscale(fx_pos.x);
	pos.y = unscale(fx_pos.y);

	pos.x = pos.x >> 4;
	pos.y = pos.y >> 4;

	if (pos.x < 0 || pos.x >= 40 || pos.y < 0 || pos.y >= 40)
		return notile;

	return data[pos.x][pos.y];
}

vec2 Level::coordsAt(vec2 fx_pos)
{
	vec2 pos;
	pos.x = unscale(fx_pos.x);
	pos.y = unscale(fx_pos.y);

	pos.x = pos.x >> 4;
	pos.y = pos.y >> 4;

	return pos;
}

void Level::reload()
{
	load(currentlevel);
}
