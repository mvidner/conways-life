#ifndef CONWAYS_LIFE_H
#define CONWAYS_LIFE_H

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
#endif
