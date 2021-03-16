#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "MultiplayerTetris.h"


int main()
{
	MultiplayerTetris multiplayerTetris;
	if (multiplayerTetris.Construct(2*(91 + 2 * 72), 2 * 163, 2, 2))
		multiplayerTetris.Start();
	return 0;
}
