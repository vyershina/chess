#include <iostream>

class Piece {
 private:
  int rank;
  int file;
  char side;
  char type;

 public:
  std::vector<std::string> possibleMoves();

  void setRank(int n);

  void setFile(int n);

  void setSide(char c);

  void setType(char c);
};
