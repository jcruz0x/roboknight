#pragma once
#include "lib.h"
#include "res.h"
#include "utility.h"

extern Res res;

// Entity flags:
const int HAZARD = 1 << 0;
const int MAIDEN = 1 << 1;
const int SHOOTABLE = 1 << 2;
const int PICKUP = 1 << 3;
const int FIRE_ASPECT = 1 << 4;

// Entity Messages
const int MAIDEN_KILL = 1 << 0;
const int MAIDEN_SAVE = 1 << 1;
const int BULLET_KILL = 1 << 2;
const int PICKUP_EFFECT = 1 << 3;
const int PICKUP_KILL = 1 << 4;

class SenseResult
{
public:
	SenseResult() { };
	SenseResult(bool p, int x, int y, tiledex t): popped(p), mapx(x), mapy(y), tile(t) { };

	bool popped;
	int mapx;
	int mapy;
	tiledex tile;
};

class Entity
{
public:
	Entity() { };
	~Entity() { };

	vec2 currPos;
	vec2 prevPos;

	vec2 getCoords(float alpha);

	void setPrevPos();
	void moveTo(vec2 newpos);
	void moveToMapPos(vec2 newpos);

	SenseResult sensePop(vec2 sensor, dir d, int oldfoot, bool nopop = false); // check sensor to see if it moved into a wall, pop it back if it did

	virtual void update() { };
	virtual void draw(sf::RenderWindow & window, float deltafraction) { };
	virtual int getFlags() { return 0; };
	virtual intrect getHitbox(){ return makeHitbox(0, 0, 0, 0); };
	virtual intrect makeHitbox(int xo, int yo, int w, int h);
	void basicDraw(sf::RenderWindow & window, float deltafraction, spritedex s);
	bool colliding(intrect withBox);
	virtual void message(int msg) { };

	virtual bool isDead() { return false; };
};
