#include "conways_life.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <ctime>

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
  int generations = 0;
  srand(time(NULL));
  ConwaysLife cl;
  const char * preset[] = {" x ", "  x", "xxx", NULL};
  set_lines(cl, preset);
  random_setup(cl);
  while(true) {
    puts("\e[2J");		// VT102 erase whole display
    print(cl);
    cl.next();
    printf("%d\n", generations++);
    usleep(50000);
  }
  return 0;
}
