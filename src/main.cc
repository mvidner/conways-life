#include "conways_life.h"
#include "random.h"

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
int LIVE_MAX = int (live_p * MY_RAND_MAX);

void random_setup(ConwaysLife &cl) {
  for (unsigned y = 0; y < cl.size_y(); ++y) {
    for (unsigned x = 0; x < cl.size_x(); ++x) {
      cl.set(x, y, ConwaysLife::State(myrand() <= LIVE_MAX));
    }
  }
}

int main(int argc, char ** argv) {
  int seed = time(NULL);
  int quiet = 0;
  int opt;
  while ((opt = getopt(argc, argv, "qs:")) != -1) {
    switch (opt) {
    case 'q':
      quiet = 1;
      break;
    case 's':
      // 17 produces 2869 generations :)
      seed = atoi(optarg);
      break;
    default: /* '?' */
      fprintf(stderr, "Usage: %s [-s seed] [-q(uiet)]\n",
	      argv[0]);
      exit(EXIT_FAILURE);
    }
  }
  if (optind < argc) {
      fprintf(stderr, "Superfluous argument '%s'\n",
	      argv[optind]);
      exit(EXIT_FAILURE);
  }

  int generations = 0;
  mysrand(seed);
  ConwaysLife cl;
  random_setup(cl);
  int period;
  do {
    if (!quiet) {
      usleep(50000);
      puts("\e[2J");		// VT102 erase whole display
      print(cl);
    }
    cl.next();
    ++generations;
    if (!quiet) {
      printf("%d\n", generations);
    }
    period = cl.stabilized();
  } while (period == 0);
  printf("generations: %d, period: %d, seed: %d\n",
	 generations, period, seed);
  return 0;
}
