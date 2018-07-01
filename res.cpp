#include "res.h"

Res res; // global artbox_object

Res::Res()
{
	gfxmap[grasstoptile] = vec2(0, 0);
	gfxmap[dirttile] = vec2(1, 0);
	gfxmap[stonetile] = vec2(2, 0);
	gfxmap[bgbluetile] = vec2(3, 0);
	gfxmap[spiketile] = vec2(4, 0);
	gfxmap[greenballtile] = vec2(5, 0);

	gfxmap[bluetile] = vec2(6, 0);
	gfxmap[vpipe] = vec2(7, 0);
	gfxmap[pipeblock] = vec2(6, 1);
	gfxmap[hpipe] = vec2(7, 1);

	gfxmap[magma] = vec2(0, 2);
	gfxmap[bluemagma] = vec2(1, 2);
	gfxmap[bridge] = vec2(2, 2);
	gfxmap[crystaltile] = vec2(3, 2);
	gfxmap[orangetile] = vec2(4, 2);
	gfxmap[keyblock] = vec2(5, 2);


	gfxmap[lava1] = vec2(0,1);
	gfxmap[lava2] = vec2(1,1);
	gfxmap[lava3] = vec2(2,1);
	gfxmap[lavamix1] = vec2(3,1);
	gfxmap[lavamix2] = vec2(4,1);
	gfxmap[lavamix3] = vec2(5,1);


	typemap[grasstoptile] = plattype;
	typemap[dirttile] = 0;
	typemap[stonetile] = solidtype;
	typemap[bgbluetile] = 0;
	typemap[greenballtile] = solidtype;

	typemap[bluetile] = 0;
	typemap[orangetile] = solidtype;
	typemap[pipeblock] = solidtype;
	typemap[hpipe] = solidtype;
	typemap[vpipe] = solidtype;
	typemap[magma] = solidtype | killtype;
	typemap[bluemagma] = solidtype;
	typemap[bridge] = plattype;
	typemap[crystaltile] = 0;
	typemap[keyblock] = solidtype;

	typemap[lava1] = solidtype | killtype | firekilltype;
	typemap[spiketile] = killtypehalf;
	typemap[lavamix1] = killtypehalf | firekilltype;

	soundB[sJump].loadFromFile("sfx/Jump2.wav");
	soundB[sShoot].loadFromFile("sfx/shoot.wav");
	soundB[sBoom].loadFromFile("sfx/missle.wav");
	soundB[sMBoom].loadFromFile("sfx/explode.wav");
	soundB[sShieldHit].loadFromFile("sfx/shieldhit.wav");
	soundB[sPowerUp].loadFromFile("sfx/Powerup.wav");
	soundB[sKill].loadFromFile("sfx/kablam.wav");
	soundB[sDie].loadFromFile("sfx/die2.wav");

	for (int i = 0; i < maxSounds; i++)
		sound[i].setBuffer(soundB[i]);

}

void Res::loadArt()
{

	//load tileset
	tileset.loadFromFile("gfx/tileset.png");
	tiletex.loadFromImage(tileset);
	tiletex.setSmooth(false);
	tiletex.setRepeated(false);
	tilesprite.setTexture(tiletex);

	// Load Images:
	img[herohead].loadFromFile("gfx/heroparts/herohead.png");
	img[herochest].loadFromFile("gfx/heroparts/herochest.png");
	img[herogun].loadFromFile("gfx/heroparts/herogun.png");
	img[legs1].loadFromFile("gfx/heroparts/legs1.png");
	img[legs2].loadFromFile("gfx/heroparts/legs2.png");
	img[legs3].loadFromFile("gfx/heroparts/legs3.png");
	img[legs4].loadFromFile("gfx/heroparts/legs4.png");
	img[legs5].loadFromFile("gfx/heroparts/legs5.png");
	img[legs6].loadFromFile("gfx/heroparts/legs6.png");
	img[legs7].loadFromFile("gfx/heroparts/legs7.png");
	img[legs8].loadFromFile("gfx/heroparts/legs8.png");

	img[legs1gold].loadFromFile("gfx/heroparts/legs1gold.png");
	img[legs2gold].loadFromFile("gfx/heroparts/legs2gold.png");
	img[legs3gold].loadFromFile("gfx/heroparts/legs3gold.png");
	img[legs4gold].loadFromFile("gfx/heroparts/legs4gold.png");
	img[legs5gold].loadFromFile("gfx/heroparts/legs5gold.png");
	img[legs6gold].loadFromFile("gfx/heroparts/legs6gold.png");
	img[legs7gold].loadFromFile("gfx/heroparts/legs7gold.png");
	img[legs8gold].loadFromFile("gfx/heroparts/legs8gold.png");

	img[death1].loadFromFile("gfx/heroparts/death1.png");
	img[death2].loadFromFile("gfx/heroparts/death2.png");
	img[death3].loadFromFile("gfx/heroparts/death3.png");
	img[death4].loadFromFile("gfx/heroparts/death4.png");
	img[fireball1].loadFromFile("gfx/fireball.png");
	img[fireball2].loadFromFile("gfx/fireball2.png");
	img[bat1].loadFromFile("gfx/bat1.png");
	img[bat2].loadFromFile("gfx/bat2.png");

	img[tail].loadFromFile("gfx/tail.png");

	img[bigstarsprite].loadFromFile("gfx/bigstar2.png");
	img[littlestarsprite].loadFromFile("gfx/littlestar.png");

	img[bullet1].loadFromFile("gfx/bullet1.png");
	img[bullet2].loadFromFile("gfx/bullet2.png");
	img[redbullet1].loadFromFile("gfx/redbullet1.png");
	img[redbullet2].loadFromFile("gfx/redbullet2.png");
	img[misslebullet].loadFromFile("gfx/misslebullet.png");

	img[boom1].loadFromFile("gfx/boom1.png");
	img[boom2].loadFromFile("gfx/boom2.png");
	img[boom3].loadFromFile("gfx/boom3.png");
	img[boom4].loadFromFile("gfx/boom4.png");
	img[boom5].loadFromFile("gfx/boom5.png");
	img[boom6].loadFromFile("gfx/boom6.png");

	img[goblin1].loadFromFile("gfx/goblin.png");
	img[goblin2].loadFromFile("gfx/goblin2.png");
	img[goblin3].loadFromFile("gfx/goblin3.png");

	img[bubble].loadFromFile("gfx/bubble.png");
	img[firebubble].loadFromFile("gfx/firebubble.png");

	img[splat1].loadFromFile("gfx/splat1.png");
	img[splat2].loadFromFile("gfx/splat2.png");
	img[splat3].loadFromFile("gfx/splat3.png");
	img[splat4].loadFromFile("gfx/splat4.png");

	img[mdeath1].loadFromFile("gfx/mdeath1.png");
	img[mdeath2].loadFromFile("gfx/mdeath2.png");
	img[mdeath3].loadFromFile("gfx/mdeath3.png");
	img[mdeath4].loadFromFile("gfx/mdeath4.png");
	img[mdeath5].loadFromFile("gfx/mdeath5.png");

	img[maiden1].loadFromFile("gfx/maiden.png");
	img[maidenhappy].loadFromFile("gfx/maidenhappy.png");

	img[boots].loadFromFile("gfx/boots.png");
	img[stars].loadFromFile("gfx/stars.png");
	img[misslepickup].loadFromFile("gfx/missle.png");
	img[shieldball].loadFromFile("gfx/shieldball.png");
	img[fireshieldball].loadFromFile("gfx/fireshieldball.png");
	img[spread].loadFromFile("gfx/spread.png");
	img[key].loadFromFile("gfx/key.png");
	img[acorn].loadFromFile("gfx/leaf.png");


	for (int i = 0; i < sprite_max; i++)
	{
		img[i].createMaskFromColor(sf::Color::Magenta);
		tex[i].loadFromImage(img[i]);
		tex[i].setSmooth(false);
		tex[i].setRepeated(false);
		sprite[i].setTexture(tex[i]);
	}

	levels[0] = "lvl/zeroth.png";
	levels[1] = "lvl/first.png";
	levels[2] = "lvl/second.png";
	levels[3] = "lvl/third.png";
	levels[4] = "lvl/fourth.png";
	levels[5] = "lvl/test.png";


} // end loadArt
