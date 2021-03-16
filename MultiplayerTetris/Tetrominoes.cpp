#include "Tetrominoes.h"

olc::Pixel colors[8] = { //DARK_BLUE IS USED BY GRID
olc::DARK_GREY,
olc::GREEN,
olc::BLUE,
olc::YELLOW,
olc::CYAN,
olc::MAGENTA,
olc::DARK_MAGENTA,
olc::RED
};

Tetromino I = { 1, 2,
{ 0, 0, 1, 0,
  0, 0, 1, 0,
  0, 0, 1, 0,
  0, 0, 1, 0 }
};

Tetromino O = { 2, 1,
{ 0, 0, 0, 0,
  0, 1, 1, 0,
  0, 1, 1, 0,
  0, 0, 0, 0 }
};

Tetromino T = { 3, 4,
{ 0, 0, 0, 0,
  0, 0, 1, 0,
  0, 1, 1, 1,
  0, 0, 0, 0 }
};

Tetromino S = { 4, 2,
{ 0, 0, 0, 0,
  0, 0, 1, 1,
  0, 1, 1, 0,
  0, 0, 0, 0 }
};

Tetromino Z = { 5, 2,
{ 0, 0, 0, 0,
  0, 0, 0, 0,
  0, 1, 1, 0,
  0, 0, 1, 1 }
};

Tetromino J = { 6, 4,
{ 0, 0, 0, 0,
  0, 1, 0, 0,
  0, 1, 1, 1,
  0, 0, 0, 0 }
};

Tetromino L = { 7, 4,
{ 0, 0, 0, 0,
  0, 0, 0, 1,
  0, 1, 1, 1,
  0, 0, 0, 0 }
};

Tetromino tetrominoTypes[7] = { I, O, T, S, Z, J, L };
