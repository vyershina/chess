#include "piece.hpp"

class Board {
 public:
  Board();
  void printBoard();
  void saveState();
  void movePiece(std::string move, int side);

 private:
  std::vector<Piece> pieces;
  std::vector<Board> states;
};
