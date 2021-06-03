#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "MultiplayerTetris.h"

int main()
{
	MultiplayerTetris multiplayerTetris;
	if (multiplayerTetris.Construct(640, 360, 2, 2)) {
		multiplayerTetris.Start();
	}
	return 0;
}