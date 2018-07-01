#pragma once
#include "lib.h"

// utility functions
enum dir { dleft, dright, dup, ddown };

//convert fixed point to pixel
inline int unscale(int fxn)
{
	return fxn >> 16;
}

inline int scale(int pxn)
{
	return pxn << 16;
}

inline int fscale(float f)
{
	return (int) (f * ((float) (1 << 16)));
}

inline int fx_times(int a, int b)
{
	long p = a * b;
	return (int) (p >> 16);
}

inline int fx_div(int dividend, int divisor)
{

	long divisor_scaled = divisor >> 16;

	if (divisor_scaled == 0) return 0;

	return (int) (dividend / divisor_scaled);
}

inline vec2 interpolate (vec2 c, vec2 p, float alpha)
{
	vec2 n;
	n.x = p.x + ((c.x - p.x) * alpha);
	n.y = p.y + ((c.y - p.y) * alpha);
	return n;
}

inline bool rectangles_overlapping(sf::Rect<int> a, sf::Rect<int> b)
{
	if (a.left > (b.left + b.width)) return false;
	if ((a.left + a.width) < b.left) return false;
	if (a.top > (b.top + b.height)) return false;
	if ((a.top + a.height) < b.top) return false;

	return true;
};

inline sf::Rect<int> makeTileRect(vec2 pos)
{
	pos.x = unscale(pos.x);
	pos.y = unscale(pos.y);

	pos.x = pos.x >> 4;
	pos.y = pos.y >> 4;

	sf::Rect<int> r;

	r.left = pos.x << 4;
	r.top = pos.y << 4;
	r.width = 16;
	r.height = 16;

	return r;
}

inline vec2 Orbit(vec2 origin, int radius, float alpha)
{
	double rads = ((2 * 3.14159) * alpha);

	float normx = (float) sin(rads);
	float normy = (float) cos(rads);

	normx *= (float) radius;
	normy *= (float) radius;

	vec2 result(fscale(normx), fscale(-normy));

	result += origin;

	return result;
}
