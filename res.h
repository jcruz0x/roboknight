#include "lib.h"
#pragma once


const int max_stages = 6;

enum sounds { sJump, sShoot, sBoom, sMBoom, sShieldHit, sPowerUp, sKill, sDie, maxSounds };

enum spritedex {	// test sprites
				herohead, herochest, herogun,
				legs1, legs2, legs3, legs4, legs5, legs6, legs7, legs8,
				legs1gold, legs2gold, legs3gold, legs4gold, legs5gold, legs6gold, legs7gold, legs8gold,
				death1, death2, death3, death4, fireball1, fireball2,
				maiden1, maidenhappy,
				mdeath1, mdeath2, mdeath3, mdeath4, mdeath5,
				boom1, boom2, boom3, boom4, boom5, boom6,
				bat1, bat2, bullet1, bullet2, redbullet1, redbullet2, misslebullet,
				goblin1, goblin2, goblin3,
				splat1, splat2, splat3, splat4,
				acorn, shieldball, fireshieldball, misslepickup, stars,
				spread, key, boots, bubble, firebubble,
				bigstarsprite, littlestarsprite, tail,


				//sprite max
				sprite_max
				};

enum tiledex { 	notile,
				grasstoptile, dirttile, stonetile, bgbluetile,
				spiketile,
				lava1, lava2, lava3,
				lavamix1, lavamix2, lavamix3, greenballtile,
				bluetile, pipeblock, vpipe, hpipe, magma,
				bluemagma, bridge, crystaltile, orangetile, keyblock,
				tiles_max };



const int solidtype = 1 << 0;
const int plattype = 1 << 1;
const int killtype = 1 << 2;
const int killtypehalf = 1 << 3;
const int firekilltype = 1 << 4;

class Res
{
public:
	Res();

	sf::Image img[sprite_max];
	sf::Texture tex[sprite_max];
	sf::Sprite sprite[sprite_max];

	sf::Image tileset;
	sf::Texture tiletex;
	sf::Sprite tilesprite;

	vec2 gfxmap[tiles_max];
	int typemap[tiles_max];


	sf::SoundBuffer soundB[maxSounds];
	sf::Sound sound[maxSounds];


	std::string levels[max_stages];

	void loadArt();
};





