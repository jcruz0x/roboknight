#include "things.h"
#include "res.h"
#include "gfx.h"
#include "level.h"
#include "tweak.h"
#include "player.h"


extern Level level;
extern Tweak tweak;
extern Player player;

extern sf::Clock animtick;


Fireball::Fireball(int mapx, int mapy, bool bottom)
{
	origin = vec2(scale(mapx * 16), scale(mapy * 16));

	currPos.x = origin.x;

	currPos.y = origin.y + (bottom? scale(32) : -scale(32));

	setPrevPos();

	rotTick = bottom? 45 : 0;
}

void Fireball::update()
{
	if (rotTick < 90)
		rotTick++;
	else
		rotTick = 0;

	float alpha = (float) rotTick / 90.f;

	vec2 newpos = Orbit(origin, 32, alpha);
	//newpos.x = scale(newpos.x);
	//newpos.y = scale(newpos.y);

	currPos = newpos;
}

void Fireball::draw(sf::RenderWindow & window, float deltafraction)
{
	int n = (animtick.getElapsedTime().asMilliseconds() / 8) % 2;

	if (n)
		basicDraw(window, deltafraction, fireball1);
	else
		basicDraw(window, deltafraction, fireball2);
}

// =============== MAIDEN =================================

Maiden::Maiden(int mapx, int mapy)
{
	currPos = vec2(scale(mapx * 16), scale(mapy * 16));
	setPrevPos();
	deathtick = 0;
	happytick = 0;
}

void Maiden::update()
{
	if (deathtick > 0)
		deathtick++;
	if (happytick > 0)
		happytick++;
}

void Maiden::draw(sf::RenderWindow & window, float deltafraction)
{
	vec2 v = getCoords(deltafraction);
	if (deathtick == 0 && happytick == 0)
		basicDraw(window, deltafraction, maiden1);
	if (happytick > 0)
	{
		int h = happytick;
		if (h > 36) h = 36;
		drawSprite(maidenhappy, v.x, v.y - h, window);
	}
	if (deathtick > 0)
	{	spritedex boomframe = boom1;
		spritedex gutsframe = maiden1;
		bool drawboom = true;
		bool drawguts = true;

		int d = deathtick;
		if (d > 5) boomframe = boom2;
		if (d > 10) boomframe = boom3;
		if (d > 15) boomframe = boom4;
		if (d > 20) boomframe = boom5;
		if (d > 25) drawboom = false;

		if (d > 8) gutsframe = mdeath1;
		if (d > 14) gutsframe = mdeath2;
		if (d > 20) gutsframe = mdeath3;
		if (d > 26) gutsframe = mdeath4;
		if (d > 31) gutsframe = mdeath5;
		if (d > 34) drawguts = false;


		if (drawguts)
		{
			if (gutsframe == maiden1) drawSprite(maiden1, v.x, v.y, window);
			else drawSprite(gutsframe, v.x - 22, v.y - 14, window);
		}
		if (drawboom) drawSprite(boomframe, v.x - 12, v.y + 2, window);
	}
}

void Maiden::message(int msg)
{
	if (msg & MAIDEN_KILL && happytick == 0 && deathtick == 0)
		deathtick = 1;

	if (msg & MAIDEN_SAVE && happytick == 0 && deathtick == 0)
	{
		res.sound[sMBoom].play();
		happytick = 1;
	}
}

// =================== BAT ======================================

Bat::Bat(int mapx, int mapy, bool bottom)
{
	origin = vec2(scale(mapx * 16), scale(mapy * 16));

	currPos.x = origin.x;

	currPos.y = origin.y + (bottom? scale(32) : -scale(32));

	setPrevPos();

	rotTick = bottom? 45 : 0;

	dead = false;
	dyingtick = 0;
}

void Bat::update()
{

	if (dead) return;

	if (dyingtick > 0)
	{
		dyingtick--;
		if (dyingtick == 0)
			dead = true;
		return;
	}

	if (rotTick < 90)
		rotTick++;
	else
		rotTick = 0;

	float alpha = (float) rotTick / 90.f;

	vec2 newpos = Orbit(origin, 32, alpha);
	//newpos.x = scale(newpos.x);
	//newpos.y = scale(newpos.y);

	currPos = newpos;
}

void Bat::draw(sf::RenderWindow & window, float deltafraction)
{
	if (dyingtick > 0)
	{
		spritedex frame = splat1;

		if (dyingtick < 18) frame = splat2;
		if (dyingtick < 12)	frame = splat3;
		if (dyingtick < 6) frame = splat4;

		vec2 v = getCoords(deltafraction);

		drawSprite(frame, v.x - 8, v.y - 8, window);

		return;
	}

	if (dead) return;

	vec2 v = getCoords(deltafraction);
	int n = (animtick.getElapsedTime().asMilliseconds() / 8) % 2;

	if (n)
		drawSprite(bat1, v.x - 8, v.y, window);
	else
		drawSprite(bat2, v.x - 8, v.y, window);
}

void Bat::message(int msg)
{
	if (msg & BULLET_KILL)
	{
		res.sound[sKill].play();
		dyingtick = 24;
	}
}
// ============================ BULLET ===============================

Bullet::Bullet(vec2 pos, vec2 vel, bulletype btype)
{
	currPos = pos;
	setPrevPos();
	velocity = vel;
	dead = false;
	this->btype = btype;
	dyingtick = 0;
}

void Bullet::update()
{
	if (dead == true) return;
	if (dyingtick > 0)
	{
		dyingtick--;
		if (dyingtick == 1)
			dead = true;
		return;
	}
	currPos += velocity;

	vec2 c = level.coordsAt(currPos);
	if (c.x > 0 && c.x < 40 && c.y > 0 && c.y < 30)
	{
		tiledex t = level.data[c.x][c.y];
		if (res.typemap[t] & solidtype)
		{
			if (btype == (bulletmissle)) explode();
			dyingtick = 24;
			return;
		}
	}

	if ( currPos.x < scale(-8) ||
		 currPos.x > scale(640) ||
		 currPos.y < scale(-8) ||
		 currPos.y > scale(480) )
	{	dead = true; return;	}

	intrect r = getHitbox();

	for (uint i = 0; i < level.entities.size(); i++)
	{
		Entity & ent = *level.entities[i];

		if (ent.colliding(r) )
		{
			if (ent.getFlags() & SHOOTABLE)
			{
				ent.message(BULLET_KILL);
				if (btype == (bulletmissle)) explode();
				dyingtick = 24;
				return;
			}

		}

	}
}

void Bullet::draw(sf::RenderWindow & window, float deltafraction)
{
	if (dyingtick > 0)
	{
		if (btype != bulletmissle)
			return;

		spritedex frame = boom1;

		if (dyingtick < 20) frame = boom2;
		if (dyingtick < 16)	frame = boom3;
		if (dyingtick < 12) frame = boom4;
		if (dyingtick < 8)	frame = boom5;
		if (dyingtick < 4) frame = boom6;

		vec2 v = getCoords(deltafraction);

		drawSprite(frame, v.x - 8, v.y - 8, window);

		return;
	}
	spritedex frame1;
	spritedex frame2;

	if (btype == regbullet) { frame1 = bullet1; frame2 = bullet2; }
	if (btype == redbullet) { frame1 = redbullet1; frame2 = redbullet2; }
	if (btype == bulletmissle) { frame1 = misslebullet; frame2 = misslebullet; }

	vec2 offset(0,0);

	if (btype == bulletmissle) offset = vec2(-8, -5);

	bool flip = (velocity.x > 0);

	vec2 v = getCoords(deltafraction);
	int n = (animtick.getElapsedTime().asMilliseconds() / 8) % 2;

	if (n)
		drawSprite(frame1, v.x + offset.x, v.y + offset.y, window, flip);
	else
		drawSprite(frame2, v.x + offset.x, v.y + offset.y, window, flip);
}

void Bullet::explode()
{
	res.sound[sBoom].play();
	intrect killzone = intrect(currPos.x - scale(16), currPos.y - scale(16), 48, 48);

	for (uint i = 0; i < level.entities.size(); i++)
	{
		Entity & ent = *level.entities[i];
		if (ent.colliding(killzone))
			ent.message(BULLET_KILL);
	}
}

// ================= GOBLIN =============================

Goblin::Goblin(int mapx, int mapy)
{
	currPos = vec2(scale(mapx * 16), scale(mapy * 16));
	setPrevPos();

	dead = false;
	faceright = true;
	dyingtick = 0;
}

void Goblin::update()
{
	if (dead) return;

	if (dyingtick > 0)
	{
		dyingtick--;
		if (dyingtick == 0)
			dead = true;
		return;
	}


	vec2 dropcheck;

	dropcheck.y = 16;
	dropcheck.x = (faceright? 17 : -1);

	int oldfoot = currPos.y + scale(16);
	SenseResult sr = sensePop(dropcheck, (faceright? dright : dleft), oldfoot, true); // no popping just checking
	SenseResult sr2 = sensePop(dropcheck, ddown, oldfoot, true); // no popping just checking

	if (sr.popped == false && sr2.popped == false) faceright = !faceright;

	currPos += vec2(fscale(faceright? 1.5f : -1.5f), tweak.gravity);

	if (faceright)
	{
		sr = sensePop(vec2(16, 8), dright, oldfoot);
		if (sr.popped) faceright = !faceright;
	}
	else
	{
		sr = sensePop(vec2(0, 8), dleft, oldfoot);
		if (sr.popped) faceright = !faceright;
	}

	sr = sensePop(vec2(8, 16), ddown, oldfoot);
}

void Goblin::draw(sf::RenderWindow & window, float deltafraction)
{
	if (dyingtick > 0)
	{
		spritedex frame = splat1;

		if (dyingtick < 18) frame = splat2;
		if (dyingtick < 12)	frame = splat3;
		if (dyingtick < 6) frame = splat4;

		vec2 v = getCoords(deltafraction);

		drawSprite(frame, v.x - 8, v.y - 8, window);

		return;
	}

	if (dead) return;

	spritedex frame;
	int n = (animtick.getElapsedTime().asMilliseconds() / 64) % 4;

	if (n == 0) frame = goblin1;
	if (n == 1) frame = goblin2;
	if (n == 2) frame = goblin1;
	if (n == 3) frame = goblin3;

	vec2 v = getCoords(deltafraction);

	drawSprite(frame, v.x, v.y, window, faceright);
}

void Goblin::message(int msg)
{
	if (msg & BULLET_KILL)
	{
		res.sound[sKill].play();
		dyingtick = 24;
	}
}

// ========================= PICKUP ================================

Pickup::Pickup(int mapx, int mapy)
{
	currPos = vec2(scale(mapx * 16), scale(mapy * 16));
	setPrevPos();

	dead = false;

	ptype = (pickuptype) (rand() % ptype_max);
}

Pickup::Pickup(int mapx, int mapy, pickuptype pt)
{
	currPos = vec2(scale(mapx * 16), scale(mapy * 16));
	setPrevPos();

	dead = false;

	ptype = pt;
}

void Pickup::update()
{
	// stand there and look pretty
}

void Pickup::draw(sf::RenderWindow & window, float deltafraction)
{
	if (dead) return;
	spritedex frame;

	if (ptype == wjump) frame = boots;
	if (ptype == slowfall) frame = acorn;
	if (ptype == shield) frame = shieldball;
	if (ptype == fireshield) frame = fireshieldball;
	if (ptype == keyptype) frame = key;
	if (ptype == missleptype) frame = misslepickup;
	if (ptype == spreadptype) frame = spread;
	if (ptype == invincible) frame = stars;

	vec2 v = getCoords(deltafraction);

	drawSprite(frame, v.x - 1, v.y - 1, window);
}

void Pickup::message(int msg)
{
	if ((msg & PICKUP_KILL) && dead == false)
	{
		dead = true;
		return;
	}
	if (msg & PICKUP_EFFECT && dead == false)
	{
		res.sound[sPowerUp].play();
		if (ptype == wjump) player.haswjump = true;
		if (ptype == slowfall) player.hasslowfall = true;
		if (ptype == shield) player.hasshield = true;
		if (ptype == fireshield) player.hasfireshield = true;
		if (ptype == keyptype)
		{
			for (int x = 0; x < 40; x++)
				for (int y = 0; y < 40; y++)
					if (level.data[x][y] == keyblock)
						level.data[x][y] = bluetile;
		}
		if (ptype == missleptype) player.weapon = bulletmissle;
		if (ptype == spreadptype) player.weapon = redbullet;
		if (ptype == invincible) player.starstick = 300;

		dead = true;

		for (uint i = 0; i < level.entities.size(); i++)
			level.entities[i]->message(PICKUP_KILL);


		return;
	}
}
