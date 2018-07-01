#pragma once
#include "lib.h"
#include "entity.h"

class Fireball : public Entity
{
public:
	Fireball(int mapx, int mapy, bool bottom = false);
	void update();
	void draw(sf::RenderWindow & window, float deltafraction);
	intrect getHitbox() { return makeHitbox(8, 8, 4, 4); };

	int rotTick;
	vec2 origin;

	int getFlags() { return HAZARD | SHOOTABLE | FIRE_ASPECT; };
};

class Maiden : public Entity
{
public:
	Maiden(int mapx, int mapy);
	void update();
	void draw(sf::RenderWindow & window, float deltafraction);
	int getFlags() { return MAIDEN; };
	intrect getHitbox() { return makeHitbox(0,0,16,32); };
	void message(int msg);

	int deathtick;
	int happytick;
};

class Bat : public Entity
{
public:
	Bat(int mapx, int mapy, bool bottom);
	void update();
	void draw(sf::RenderWindow & window, float deltafraction);
	intrect getHitbox() { return makeHitbox(8, 8, 4, 4); };

	int rotTick;
	vec2 origin;

	int dyingtick;
	bool dead;
	bool isDead() {return dead;};

	int getFlags() { return (dyingtick? 0 : HAZARD) | ((dead == false && dyingtick == 0)? SHOOTABLE : 0); };
	void message(int msg);
};

enum bulletype {regbullet, redbullet, bulletmissle};

class Bullet : public Entity
{
public:
	Bullet (vec2 pos, vec2 vel, bulletype btype = redbullet);
	void update();
	void draw(sf::RenderWindow & window, float deltafraction);
	intrect getHitbox() { return makeHitbox(2,2,14,14); };

	vec2 velocity;
	bulletype btype;

	int dyingtick;
	bool dead;
	bool isDead() { return dead; };
	void explode();
};

class Goblin : public Entity
{
public:
	Goblin(int mapx, int mapy);
	void update();
	void draw(sf::RenderWindow & window, float deltafraction);
	intrect getHitbox() { return makeHitbox(0, 0, 16, 16); };

	bool faceright;

	int dyingtick;
	bool dead;
	bool isDead() { return dead; };
	int getFlags() { return (dyingtick? 0 : HAZARD) | ((dead == false && dyingtick == 0)? SHOOTABLE : 0); };
	void message (int msg);
};

enum pickuptype {wjump, slowfall, shield, fireshield, keyptype, missleptype, spreadptype, invincible, ptype_max};

class Pickup : public Entity
{
public:
	Pickup(int mapx, int mapy);
	Pickup(int mapx, int mapy, pickuptype pt);
	void update();
	void draw(sf::RenderWindow & window, float deltafraction);
	intrect getHitbox() { return makeHitbox(0, 0, 16, 16); };

	pickuptype ptype;

	bool dead;
	bool isdead() { return dead; };
	int getFlags() { return PICKUP; }
	void message (int msg);
};
