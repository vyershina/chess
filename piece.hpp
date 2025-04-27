#include <iostream>

class Piece {
 private:
  int rank;
  int file;
  int side;
  char symb;
  char type;
  void disambiguate(std::string move, std::vector<std::string>& possible_moves);

 public:
  std::vector<std::string> possibleMoves();

  void setRank(int n);
  void setFile(int n);
  void setSide(int n);
  void setType(char c);
  void setSymb(char c);

  char getSymb();
  char getType();
  int getRank();
  int getFile();
  int getSide();
};
