#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "MultiplayerTetris.h"

int main()
{
	MultiplayerTetris multiplayerTetris;
	if (multiplayerTetris.Construct(1280, 720, 1, 1))
		multiplayerTetris.Start();
	return 0;
}
