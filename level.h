#pragma once

#include "lib.h"
#include "res.h"
#include "entity.h"



class Level
{
public:
	tiledex data[40][30];

	vec2 playerStart;
	std::string currentlevel;

	void load(std::string filename);
	void reload();

	tiledex tileAt( vec2 fx_pos );
	vec2 coordsAt(vec2 fx_pos);

	std::vector<Entity*> entities;
};
