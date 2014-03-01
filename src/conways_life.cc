#include <cstdlib>
#include <cstdio>
#include <unistd.h>

class ConwaysLife {
  static const unsigned SIZE_X = 84;
  static const unsigned SIZE_Y = 48;
public:
  enum State { DEAD = 0, ALIVE = 1 };

  ConwaysLife();

  void clear();
  void next();
  bool stabilized() const;

  unsigned size_x() const;
  unsigned size_y() const;
  
  State get(unsigned x, unsigned y) const;
  State set(unsigned x, unsigned y, State s);
};

// input: spaces dead, other alive
void set_lines(ConwaysLife& cl, const char ** lines) {
  unsigned x, y;
  const char * line;
  char cell;
  for (x = 0, line = lines[x];
       x < cl.size_x() && line != NULL;
       ++x, line = lines[x]) {
    for (y = 0, cell = line[y];
	 y < cl.size_y() && cell != '\0';
	 ++y, cell = line[y]) {
      cl.set(x, y, ConwaysLife::State(cell != ' '));
    }
  }
}

void print(const ConwaysLife &cl) {
  for (unsigned x = 0; x < cl.size_x(); ++x) {
    for (unsigned y = 0; y < cl.size_y(); ++y) {
      putchar(cl.get(x, y) ? 'o' : ' ');
    }
    putchar('\n');
  }
  putchar('\n');
}

int main() {
  ConwaysLife cl;
  const char * preset[] = {" x ", "xxx", " x ", NULL};
  set_lines(cl, preset);
  while(true) {
    print(cl);
    cl.next();
    usleep(500000);
  }
  return 0;
}
