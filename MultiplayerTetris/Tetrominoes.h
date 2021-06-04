#ifndef TETROMINOES_H
#define TETROMINOES_H

#include "olcPixelGameEngine.h"

struct Tetromino {
	int color;
	int rotations;
	int shape[4 * 4] { 0 };
	int XOffset(int index, int rotation) { 
		switch (rotation) {
			case 0:		return index % 4;			//  0 deg
			case 1:		return 4 - int(index / 4);	// 90 deg
			case 2:		return 4 - index % 4;		//180 deg
			default:	return int(index / 4);		//270 deg
		}
	}
	int YOffset(int index, int rotation) { 
		switch (rotation) {
			case 0:		return int(index / 4);		//  0 deg
			case 1:		return index % 4;			// 90 deg
			case 2:		return 4 - int(index / 4);  //180 deg
			default:	return 4 - index % 4;		//270 deg
		}
	}
};

extern olc::Pixel colors[9];
extern Tetromino I;
extern Tetromino O;
extern Tetromino T;
extern Tetromino S;
extern Tetromino Z;
extern Tetromino J;
extern Tetromino L;
extern Tetromino tetrominoTypes[7];
#endif