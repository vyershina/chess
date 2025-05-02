#include <iostream>

class Board;  // to avoid circular includes

class Piece {
 private:
  Board* local_board;
  int side;
  int file;
  int rank;
  char type;
  char symb;

  // Instance method (in private because it is not called outside of the class)
  void disambiguate(std::string move, std::vector<std::string>& possible_moves);

 public:
  // Constructor
  Piece(Board* board, int side, int file, int rank, char type, char symb);

  // Instance methods
  void makeMove(Piece* piece, int fin_file, int fin_rank, int castle,
                bool taking);
  bool isBlocked(int side, int file2check, int rank2check);
  std::vector<std::string> possibleMoves();

  // Setter methods
  void setRank(int n);
  void setFile(int n);
  void setSide(int n);
  void setType(char c);
  void setSymb(char c);

  // Getter methods
  char getSymb();
  char getType();
  int getRank();
  int getFile();
  int getSide();
};  // end Piece
