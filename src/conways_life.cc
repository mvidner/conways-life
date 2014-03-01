#include "conways_life.h"
#include <cstring>

ConwaysLife::ConwaysLife() {
  clear();
}

void ConwaysLife::clear() {
  board = board1;
  next_board = board2;
  memset(board, 0, SIZE_X * SIZE_Y);
}

ConwaysLife::State ConwaysLife::get(int x, int y) const {
  x = (x + SIZE_X) % SIZE_X;
  y = (y + SIZE_Y) % SIZE_Y;
  return State(board[SIZE_X * y + x]);
}

void ConwaysLife::set(unsigned x, unsigned y, ConwaysLife::State s) {
  if (x < SIZE_X && y < SIZE_Y) {
    board[SIZE_X * y + x] = s;
  }
}

void ConwaysLife::next() {
#define g(dx, dy) (unsigned ( get(x + (dx), y + (dy)) ))
  for (unsigned y = 0; y < size_y(); ++y) {
    for (unsigned x = 0; x < size_x(); ++x) {
      int count =
	g(-1, -1) + g(-1, 0) + g(-1, +1) +
	g( 0, -1) +     0    + g( 0, +1) +
	g(+1, -1) + g(+1, 0) + g(+1, +1);
      State next_state;
      if (g(0, 0))
	next_state = (count == 2 || count == 3)? ALIVE : DEAD;
      else
	next_state = (count == 3)? ALIVE : DEAD;
      next_board[SIZE_X * y + x] = next_state;
    }
  }
  State * tmp = board;
  board = next_board;
  next_board = tmp;
#undef g
}
