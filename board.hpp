#include <iostream>

#include "piece.hpp"

class Board {
 public:
  Board();
  void printBoard();
  void passMove(std::string move, int side);
  std::vector<Piece> pieces;

 private:
  std::vector<Board> states;
};
