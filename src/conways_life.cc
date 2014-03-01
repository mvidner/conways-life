#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <ctime>

class ConwaysLife {
  static const unsigned SIZE_X = 120;
  static const unsigned SIZE_Y = 30;
public:
  enum State { DEAD = 0, ALIVE = 1 };

  ConwaysLife();

  void clear();
  void next();
  bool stabilized() const;

  unsigned size_x() const { return SIZE_X; };
  unsigned size_y() const { return SIZE_Y; };
  
  State get(int x, int y) const;
  void set(unsigned x, unsigned y, State s);

private:
  State * board;
  State * next_board;
  State board1[SIZE_X * SIZE_Y];
  State board2[SIZE_X * SIZE_Y];
};

ConwaysLife::ConwaysLife() {
  clear();
}

void ConwaysLife::clear() {
  //  memset(board, 0, SIZE_X * SIZE_Y);
  board = board1;
  next_board = board2;
  for (unsigned y = 0; y < size_y(); ++y) {
    for (unsigned x = 0; x < size_x(); ++x) {
      set(x, y, DEAD);
    }
  }

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

// input: spaces dead, other alive
void set_lines(ConwaysLife& cl, const char ** lines) {
  unsigned x, y;
  const char * line;
  char cell;
  for (y = 0, line = lines[y];
       y < cl.size_y() && line != NULL;
       ++y, line = lines[y]) {
    for (x = 0, cell = line[x];
	 x < cl.size_x() && cell != '\0';
	 ++x, cell = line[x]) {
      cl.set(x, y, ConwaysLife::State(cell != ' '));
    }
  }
}

void print(const ConwaysLife &cl) {
  for (unsigned y = 0; y < cl.size_y(); ++y) {
    for (unsigned x = 0; x < cl.size_x(); ++x) {
      putchar(cl.get(x, y) ? 'o' : ' ');
    }
    putchar('\n');
  }
  putchar('\n');
}

const double live_p = 0.2;
int LIVE_MAX = int (live_p * RAND_MAX);

void random_setup(ConwaysLife &cl) {
  for (unsigned y = 0; y < cl.size_y(); ++y) {
    for (unsigned x = 0; x < cl.size_x(); ++x) {
      cl.set(x, y, ConwaysLife::State(rand() <= LIVE_MAX));
    }
  }
}

int main() {
  srand(time(NULL));
  ConwaysLife cl;
  const char * preset[] = {" x ", "  x", "xxx", NULL};
  set_lines(cl, preset);
  random_setup(cl);
  while(true) {
    puts("\e[2J");		// VT102 erase whole display
    print(cl);
    cl.next();
    usleep(50000);
  }
  return 0;
}
