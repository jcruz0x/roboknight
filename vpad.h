#pragma once

enum vkey { leftkey, rightkey, upkey, downkey, jumpkey, shootkey, max_keys };

class Vpad
{
public:
	Vpad();

	void update();

	bool isDown[max_keys];
	bool wasDown[max_keys];

	bool down(vkey k) { return isDown[k]; };
	bool pressed(vkey k) { return (isDown[k] == true && wasDown[k] == false); };
};
