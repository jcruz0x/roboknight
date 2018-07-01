#include "entity.h"
#include "utility.h"
#include "Level.h"
#include "res.h"
#include "gfx.h"

extern Level level;

vec2 Entity::getCoords(float alpha)
{
	vec2 v = interpolate(currPos, prevPos, alpha);
	v.x = unscale(v.x);
	v.y = unscale(v.y);
	return v;
}

void Entity::setPrevPos()
{
	prevPos = currPos;
}

void Entity::moveTo(vec2 newpos)
{
	currPos = newpos;
	prevPos = newpos;
}

void Entity::moveToMapPos(vec2 newpos)
{
	newpos.x = scale(newpos.x);
	newpos.y = scale(newpos.y);
	newpos.x = newpos.x << 4;
	newpos.y = newpos.y << 4;
	currPos = newpos;
	prevPos = newpos;
}

SenseResult Entity::sensePop(vec2 sensor, dir d, int oldfoot, bool nopop)
{
	sensor.x = scale(sensor.x);
	sensor.y = scale(sensor.y);
	vec2 realsensor = currPos + sensor;

	tiledex t = level.tileAt(realsensor);

	intrect rect = makeTileRect(realsensor);
	intrect fxrect;

	fxrect.left = scale(rect.left);
	fxrect.top = scale(rect.top);
	fxrect.width = scale(rect.width);
	fxrect.height = scale(rect.height);

	intrect hitbox = getHitbox();

	bool popped = false;

	if (res.typemap[t] & solidtype || ((res.typemap[t] & plattype) && (oldfoot <= fxrect.top) && d == ddown))
	{
		popped = true;
		if (nopop == false)
		{
			if (d == dleft) currPos.x = (fxrect.left + fxrect.width);
			if (d == dright) currPos.x = (fxrect.left - hitbox.width);
			if (d == dup) currPos.y = (fxrect.top + fxrect.height);
			if (d == ddown) currPos.y = (fxrect.top - hitbox.height);
		}
	}

	vec2 atvec = level.coordsAt(realsensor);
	return SenseResult(popped, atvec.x, atvec.y, t);
}

intrect Entity::makeHitbox(int xo, int yo, int x, int y)
{
	intrect hitbox;
	hitbox.left = currPos.x + scale(xo);
	hitbox.top = currPos.y + scale(yo);
	hitbox.width = scale(x);
	hitbox.height = scale(y);

	return hitbox;
}

void Entity::basicDraw(sf::RenderWindow & window, float deltafraction, spritedex s)
{
	vec2 v = getCoords(deltafraction);
	drawSprite(s, v.x, v.y, window);
}

bool Entity::colliding(intrect withBox)
{
	return rectangles_overlapping(getHitbox(), withBox);
}
