#pragma once

#include "lib.h"
#include "entity.h"
#include "things.h"


class Player : public Entity
{
public:
	Player();
	vec2 velocity;

	int walktick;
	bool faceright;
	bool onground;
	bool jumping;
	int ledgeTick;
	int deathTick;

	bulletype weapon;

	bool haswjump;
	bool canwjump;

	bool hasslowfall;
	bool hasshield;
	bool hasfireshield;

	int starstick;
	int flashtick;

	vec2 starpos[10];
	bool bigstar[10];
	int numStars;
	vec2 oldStarPos;

	void reset(vec2 newpos);
	void update();
	void deathUpdate();
	void deathDraw(sf::RenderWindow & window, float deltafraction);
	void draw(sf::RenderWindow & window, float deltafraction);
	void die();
	void tileAction(SenseResult sen);
	intrect getHitbox() { return makeHitbox(0, 0, 16, 32); };

	void makeStars(float deltafraction);
};


