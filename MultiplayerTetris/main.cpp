#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "MultiplayerTetris.h"


int main()
{
	MultiplayerTetris multiplayerTetris;
//	if (multiplayerTetris.Construct(2*(91 + 2 * 72), 2 * 163, 2, 2))
	if (multiplayerTetris.Construct(1280, 720, 1, 1, false))
		multiplayerTetris.Start();
	return 0;
}

