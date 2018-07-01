#include "player.h"
#include "tweak.h"
#include "vpad.h"
#include "gfx.h"
#include "utility.h"
#include "entity.h"
#include "Gamestate.h"
#include "things.h"

extern Vpad vpad;
extern Tweak tweak;
extern Level level;
extern Gamestate gamestate;
extern sf::Clock animtick;

Player::Player()
{
	velocity.x = 0;
	velocity.y = 0;

	walktick = 0;
	faceright = false;
	onground = false;
	jumping = false;
	ledgeTick = 0;
	deathTick = 0;
	weapon = regbullet;

	haswjump = false;
	canwjump = false;

	hasslowfall = false;
	hasshield = false;
	hasfireshield = false;

	starstick = 0;
	flashtick = 0;

	makeStars(1.f);
}

void Player::reset(vec2 newpos)
{
	moveToMapPos(newpos);

	velocity.x = 0;
	velocity.y = 0;

	walktick = 0;
	faceright = false;
	onground = false;
	jumping = false;
	ledgeTick = 0;
	deathTick = 0;
	weapon = regbullet;

	haswjump = false;
	canwjump = false;

	hasslowfall = false;
	hasshield = false;
	hasfireshield = false;

	starstick = 0;
	flashtick = 0;

}

void Player::update()
{

	if (deathTick > 0)
	{
		deathUpdate();
		return;
	}

	if (flashtick > 0)
		flashtick--;

	if (starstick > 0)
		starstick--;

	if (vpad.pressed(shootkey))
	{
		res.sound[sShoot].play();
		vec2 b;
		b.x = faceright? currPos.x + scale(28) : currPos.x - scale(8);
		b.y = currPos.y + scale(16);
		vec2 v;
		v.x = faceright? scale(8) : scale(-8);
		v.y = 0;

		level.entities.push_back(new Bullet(b, v, weapon));

		if (weapon == redbullet)
		{
			vec2 va[4];
			va[0] = vec2(scale(-7), fscale(-0.5));
			va[1] = vec2(scale(-6), fscale(-1));
			va[2] = vec2(scale(-7), fscale(0.5));
			va[3] = vec2(scale(-6), fscale(2));

			for (uint i = 0; i < 4; i++)
				if (faceright) va[i].x *= -1;

			for (uint i = 0; i < 4; i++)
				level.entities.push_back(new Bullet(b, va[i], weapon));
		}
	}

	if (vpad.down(leftkey))
	{
		velocity.x -= velocity.x <= 0? tweak.accel : (onground? tweak.deccel : tweak.airdeccel);
		if (velocity.x < -tweak.maxSpeed)
			velocity.x = -tweak.maxSpeed;
	}

	if (vpad.down(rightkey))
	{
		velocity.x += velocity.x >= 0? tweak.accel : (onground? tweak.deccel : tweak.airdeccel);
		if (velocity.x > tweak.maxSpeed)
			velocity.x = tweak.maxSpeed;
	}

	if (vpad.pressed(jumpkey) && ledgeTick > 0)
	{
		velocity.y = -(tweak.jumpVel + fx_div(abs(velocity.x), tweak.jumpFract));
		jumping = true;
		res.sound[sJump].play();
	}

	if (vpad.pressed(jumpkey) && ledgeTick == 0 && canwjump == true && haswjump == true)
	{
		velocity.y = -(tweak.jumpVel + fx_div(abs(velocity.x), tweak.jumpFract));
		jumping = true;
		canwjump = false;
		res.sound[sJump].play();
	}

	if (vpad.down(jumpkey) == false && jumping == true)
	{
		velocity.y = -tweak.jumpShort;
		jumping = false;
	}

	int oldfoot = currPos.y + scale(32);

	velocity.y += tweak.gravity;
	if (velocity.y > tweak.terminalVel)
		velocity.y = tweak.terminalVel;
	if (velocity.y > tweak.slowfallspeed && hasslowfall && vpad.down(jumpkey))
		velocity.y = tweak.slowfallspeed;

	currPos.x += velocity.x;
	currPos.y += velocity.y;

	bool x_stop = false;
	bool y_stop = false;
	onground = false;
	if (ledgeTick > 0) ledgeTick--;

	SenseResult sense1;
	SenseResult sense2;

	if (velocity.x < 0)
	{
		sense1 = sensePop(vec2(0, 8), dleft, oldfoot);
		sense2 = sensePop(vec2(0, 24), dleft, oldfoot);
		if (sense1.popped || sense2.popped) x_stop = true;
		tileAction(sense1);
		tileAction(sense2);

	}
	if (velocity.x > 0)
	{
		sense1 = sensePop(vec2(16, 8), dright, oldfoot);
		sense2 = sensePop(vec2(16, 24), dright, oldfoot);
		if (sense1.popped || sense2.popped) x_stop = true;
		tileAction(sense1);
		tileAction(sense2);
	}
	if (velocity.y < 0)
	{
		sense1 = sensePop(vec2(2, 0), dup, oldfoot);
		sense2 = sensePop(vec2(14, 0), dup, oldfoot);
		if (sense1.popped || sense2.popped) { y_stop = true; jumping = false; }
		tileAction(sense1);
		tileAction(sense2);
	}
	if (velocity.y > 0)
	{
		jumping = false;

		sense1 = sensePop(vec2(2, 32), ddown, oldfoot);
		sense2 = sensePop(vec2(14, 32), ddown, oldfoot);
		if (sense1.popped || sense2.popped) { y_stop = true; onground = true; }
		tileAction(sense1);
		tileAction(sense2);
	}

	if (onground) ledgeTick = 6;

	if (x_stop == true) velocity.x = 0;
	if (y_stop == true) velocity.y = 0;

	if (vpad.down(leftkey) == false && vpad.down(rightkey) == false)
	{
		if (velocity.x < 0)
		{
			velocity.x += onground? tweak.friction : tweak.airfriction;
			if (velocity.x > 0) velocity.x = 0;
		}
		if (velocity.x > 0)
		{
			velocity.x -= onground? tweak.friction : tweak.airfriction;
			if (velocity.x < 0) velocity.x = 0;
		}
	}


	if (abs(velocity.x) > 0)
	{
		walktick += abs(unscale(velocity.x));
	}
	else
		walktick = 0;

	if (onground) canwjump = true;

	for (uint i = 0; i < level.entities.size(); i++)
	{
		Entity & ent = *level.entities[i];

		if (ent.colliding(getHitbox()))
		{
			if ( (ent.getFlags() & HAZARD) && ( ((ent.getFlags() & FIRE_ASPECT) == false) || (hasfireshield == false) )) die();
			if (ent.getFlags() & MAIDEN)
			{
				ent.message(MAIDEN_SAVE);
				for (uint i = 0; i < level.entities.size(); i++)
					level.entities[i]->message(MAIDEN_KILL);
				if (gamestate.wintick == 0)	gamestate.wintick = 70;
			}
			if (ent.getFlags() & PICKUP) ent.message(PICKUP_EFFECT);
		}
	}
}

void Player::deathUpdate()
{
		deathTick--;

		if (deathTick == 0) level.reload(); //moveToMapPos(level.playerStart);
}

void Player::draw(sf::RenderWindow & window, float deltafraction)
{

	if (flashtick)
		if ((animtick.getElapsedTime().asMilliseconds() / 8) % 2) return;

	if (deathTick > 0)
	{
		deathDraw(window, deltafraction);
		return;
	}
	// part offsetts:
	vec2 chestoff(-1, 11);
	vec2 headoff(0, 0);
	vec2 legoff(-4, 21);
	vec2 gunoff(-4, 17);

	bool w = haswjump;
	spritedex leg;
	int legpick = (walktick / 12) % 8;
	switch(legpick)
	{
	case 0: leg = !w? legs1 : legs1gold; break;
	case 1: leg = !w? legs2 : legs2gold; break;
	case 2: leg = !w? legs3 : legs3gold; break;
	case 3: leg = !w? legs4 : legs4gold; break;
	case 4: leg = !w? legs5 : legs5gold; break;
	case 5: leg = !w? legs6 : legs6gold; break;
	case 6: leg = !w? legs7 : legs7gold; break;
	case 7: leg = !w? legs8 : legs8gold; break;


	}

	if (velocity.x < 0) faceright = false;
	if (velocity.x > 0) faceright = true;

	if (faceright == true)
	{
		chestoff.x = 3;
		legoff.x = 2;
		gunoff.x = 3;
		headoff.x = 4;
	}

	vec2 v = getCoords(deltafraction);

	if (hasslowfall)
	{
		vec2 tail_off(10, 12);
		if (faceright) tail_off = vec2(-4, 12);
		vec2 tv = v + tail_off;
		drawSprite(tail, tv.x, tv.y, window, faceright);
	}

	drawSprite(leg, v.x + legoff.x, v.y + legoff.y, window, faceright);
	drawSprite(herochest, v.x + chestoff.x, v.y + chestoff.y, window, faceright);
	drawSprite(herohead, v.x + headoff.x, v.y + headoff.y, window, faceright);
	drawSprite(herogun, v.x + gunoff.x, v.y + gunoff.y, window, faceright);

	if (hasfireshield) drawSprite(firebubble, v.x - 19, v.y -10, window);
	if (!hasfireshield && hasshield) drawSprite(bubble, v.x - 19, v.y -10, window);

	if (starstick > 0)
	{
		if ((animtick.getElapsedTime().asMilliseconds() / 4) % 2 == 1)
			makeStars(deltafraction);


		vec2 stardif = oldStarPos - v;

		for (int i = 0; i < numStars; i++)
		{
			vec2 newStarPos = starpos[i] + stardif;
			drawSprite((bigstar[i]? bigstarsprite : littlestarsprite), newStarPos.x, newStarPos.y, window);
		}
	}

}

void Player::makeStars(float deltafraction)
{
	numStars = (rand() % 10);
	vec2 c = getCoords(deltafraction);
	oldStarPos = getCoords(deltafraction);
	for (int i = 0; i < numStars; i++)
	{
		starpos[i].x = c.x + (rand() % 24) - 4;
		starpos[i].y = c.y + (rand() % 40) - 4;
		bigstar[i] = ((rand() % 2) == 1);
	}
}

void Player::deathDraw(sf::RenderWindow & window, float deltafraction)
{
	spritedex deathframe;
	if (deathTick > 32) deathframe = death1;
	else if (deathTick > 24) deathframe = death2;
	else if (deathTick > 16) deathframe = death3;
	else if (deathTick > 8) deathframe = death4;
	else return;

	vec2 offset(-17, -9);
	vec2 v = getCoords(deltafraction);
	drawSprite(deathframe, v.x + offset.x, v.y + offset.y, window, false);
}

void Player::die()
{
	if (flashtick > 0)
		return;

	if (starstick > 0)
		return;

	if (hasshield || hasfireshield)
	{
		res.sound[sShieldHit].play();
		hasshield = false;
		hasfireshield = false;
		flashtick = 60;
		return;
	}

	res.sound[sDie].play();

	gamestate.wintick = 0;

	deathTick = 40;
	velocity = vec2(0,0);
	jumping = false;
	ledgeTick = false;
	walktick = false;
}

void Player::tileAction(SenseResult sen)
{	int f = res.typemap[sen.tile];
	if ( (f & killtype) && ( ((f & firekilltype) == false) || (hasfireshield == false) ) ) die();
	if ( (f & killtypehalf) && ( ((f & firekilltype) == false) || (hasfireshield == false) ) )
	{
		int top = scale(sen.mapy * 16);
		int half = top + scale(8);
		if ((currPos.y + scale(32)) >= half) die();
	}
}
