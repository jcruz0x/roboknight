#include "tweak.h"
#include "utility.h"

Tweak tweak;

Tweak::Tweak()
{
	maxSpeed = fscale(4.f);
	accel = fscale(0.2f);
	deccel = fscale(0.8f);
	airdeccel = deccel * 1.4;
	gravity = fscale(0.4f);
	jumpVel = fscale(7.f);
	jumpFract = fscale(4.f);
	jumpShort = fscale(2.f);
	terminalVel = fscale(8.f);
	friction = fscale(0.45f);
	airfriction = friction / 6;
	slowfallspeed = fscale(1.5f);
}
