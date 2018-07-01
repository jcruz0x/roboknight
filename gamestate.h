//#include "lib.h"


class Gamestate
{
public:
	Gamestate(): menuOpen(false), inPlay(true), advanceMenu(false), blackouttick(0), stage(0) { };
	bool menuOpen;
	bool inPlay;
	bool advanceMenu;
	bool gameWin;

	int blackouttick;
	int stage;
	int wintick;
};


