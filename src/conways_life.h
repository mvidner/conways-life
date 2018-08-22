#ifndef CONWAYS_LIFE_H
#define CONWAYS_LIFE_H

/// The main (and only) class of the simulation.
/// It contains several Boards (and compares them to detect cycles).
class ConwaysLife {
  static const unsigned SIZE_X = 84;
  static const unsigned SIZE_Y = 48;
  /// The maximum period of oscillation that we're able to detect
  static const unsigned MAX_PERIOD = 2;
  static const unsigned NBOARDS = MAX_PERIOD + 1;
public:
  /// Cell state: dead ot alive
  enum State { DEAD = 0, ALIVE = 1 };

  ConwaysLife();

  /// Clear all boards
  void clear();
  /// Calculate the next board from the current one
  void next();
  /// return 0 if the board has not yet stabilized,
  /// or the oscillation period
  int stabilized() const;

  unsigned size_x() const { return SIZE_X; };
  unsigned size_y() const { return SIZE_Y; };
  
  /// Get a cell in the current_board
  State get(int x, int y) const;
  /// Get a cell in the current_board
  void set(unsigned x, unsigned y, State s);
  /// Get a cell in any board
  void set_board(unsigned x, unsigned y, State s, unsigned board_idx);

private:
  typedef unsigned char Board[SIZE_X * SIZE_Y / 8];
  Board boards[NBOARDS];
  /// Index of the current board in \ref boards
  unsigned current_board;
};
#endif
