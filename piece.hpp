#include <iostream>

class Board;

class Piece {
 private:
  Board* local_board;
  int side;
  int file;
  int rank;
  char type;
  char symb;
  void disambiguate(std::string move, std::vector<std::string>& possible_moves);

 public:
  Piece(Board* board, int side, int file, int rank, char type, char symb);
  void makeMove(Piece* piece, int fin_file, int fin_rank, int castle,
                bool taking);
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
