#include "gfx.h"
#include "lib.h"
#include "level.h"

extern Res res;
extern sf::Clock animtick;


void drawSprite(spritedex s, int x, int y, sf::RenderWindow & window, bool xflip)
{
	int x_off = xflip? -res.tex[s].getSize().x : 0;
	res.sprite[s].setPosition(x - x_off, y);
	if (xflip) res.sprite[s].setScale(-1.f, 1.f);
	window.draw(res.sprite[s]);
	if (xflip) res.sprite[s].setScale(1.f, 1.f);
}

void drawTile(int tilex, int tiley, int x, int y, sf::RenderWindow & window)
{
	res.tilesprite.setTextureRect(sf::Rect<int>(tilex * 16, tiley * 16, 16, 16));
	res.tilesprite.setPosition(x * 16, y * 16);
	window.draw(res.tilesprite);
}

void drawMap(Level & level, sf::RenderWindow & window)
{
	for (int x = 0; x < 40; x++)
		for (int y = 0; y < 30; y++)
		{
			tiledex t = level.data[x][y];
			if (t != notile)
			{
				if (t == lava1 || t == lavamix1)
				{
					int a = (animtick.getElapsedTime().asMilliseconds() / 128) % 3;
					if (a == 1) t = (t == lava1? lava2 : lavamix2);
					if (a == 2) t = (t == lava1? lava3 : lavamix3);
				}
				vec2 v = res.gfxmap[t];

				drawTile(v.x, v.y, x, y, window);
			}
		}
}
