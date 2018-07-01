#include "lib.h"
#include "level.h"
#include "res.h"

void drawSprite(spritedex s, int x, int y, sf::RenderWindow & window, bool xflip = false);
void drawTile (int tilex, int tiley, int x, int y,  sf::RenderWindow & window);
void drawMap(Level & level, sf::RenderWindow & window);

