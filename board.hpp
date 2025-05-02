#include <iostream>

#include "piece.hpp"

class Board {
 public:
  std::vector<Piece> pieces;

  // Constructor
  Board();

  // Instance methods
  void printBoard();
  void passMove(std::string move, int side);

 private:
};
