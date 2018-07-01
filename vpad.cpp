#include "vpad.h"
#include "lib.h"

Vpad vpad;

Vpad::Vpad()
{
	for (int i = 0; i < max_keys; i++)
	{
		isDown[i] = false;
		wasDown[i] = false;
	}
}

void Vpad::update()
{
	for (int i = 0; i < max_keys; i++)
	{
		wasDown[i] = isDown[i];
		isDown[i] = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) isDown[leftkey] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) isDown[rightkey] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) isDown[downkey] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) isDown[upkey] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) isDown[jumpkey] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) isDown[shootkey] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) isDown[jumpkey] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) isDown[shootkey] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) isDown[shootkey] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) isDown[jumpkey] = true;

}
