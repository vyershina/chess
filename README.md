# Chess - CSC1060 Final Project
## Constructs (10/10)
### functions/vectors/loops/if-else
chess.cpp line 114
```cpp
void movesInVector(std::string moves_str, std::vector<std::string>& moves) {
  int i = 0;
  int move_num = 0;
  std::regex valid_move(
      "(([RNBKQ])?([a-h])?([1-8])?(x)?([a-h][1-8])(\\+|\\#)?)"
      "|((O-O)(-O)?)"
      "|(([a-h][1-8])(=)([RNBQ]))");
  for (int i = 0; i < moves_str.length(); i++) {
    if (moves_str[i] == '\n') {
      if (i == 0) {
        continue;
      }  // end if
      if (std::regex_match(moves[move_num], valid_move) == false) {
        std::cout << moves[move_num] << " -> ";
        std::cout << "Invalid move detected!\n";
      }  // end if
      move_num++;
    } else if (moves_str[i] == '\0') {
      return;
    } else if (moves_str[i] == ' ') {
      if (moves_str[i + 1] == '\n') {
        continue;
      }  // end if
      move_num++;
      continue;
    } else {
      moves[move_num] += moves_str[i];
    }  // end if(s) and else(s)
  }  // end for
}  // end movesInVector()
```

### struct
stats.hpp
```cpp
struct Stats {
  int pawn_moves = 0;
  int knight_moves = 0;
  int rook_moves = 0;
  int queen_moves = 0;
  int king_moves = 0;
  int bishop_moves = 0;
  int takes = 0;
};
```

### classes and objects
piece.hpp
```cpp
class Piece {
 private:
  Board* local_board;
  int side;
  int file;
  int rank;
  char type;
  char symb;
  std::vector<std::string> directions;

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
  void getPosMovesRec(Piece piece, std::vector<std::string>& possible_moves,
                      int curr_rank, int curr_file, std::string direction,
                      bool start);

  // Setter methods
  void setRank(int n);
  void setFile(int n);
  void setSide(int n);
  void setType(char c);
  void setSymb(char c);
  void setDir(std::vector<std::string> directions);

  // Getter methods
  std::vector<std::string> getDirs();
  char getSymb();
  char getType();
  int getRank();
  int getFile();
  int getSide();
};  // end Piece
```
### an instance of a piece
board.cpp line 20
```cpp
Piece wrook1(this, 0, 0, 0, 'R', 'R');
```

### pointers
piece.hpp line 20
```cpp
Piece(Board* board, int side, int file, int rank, char type, char symb);
io-stream
chess.cpp line 81

  std::fstream game_file("game.txt");
  std::string moves_str;
  getline(game_file, moves_str);
```

### exceptions
board.cpp line 82
```cpp
          try {
            if (found > 1) {
              throw(found);
            }  // end if
          } catch (int found) {
            std::cout << "\nTwo pieces are stacked on top of each other. "
                         "Terminating process. ";
            std::exit(-1);
          }  // end try and catch
```
### recursion
piece.cpp line 44
```cpp
void Piece::getPosMovesRec(Piece piece,
                           std::vector<std::string>& possible_moves,
                           int curr_rank, int curr_file, std::string direction,
                           bool start) {
  std::string move;
  if (!start) {
    for (Piece tmp_piece : local_board->pieces) {
      if (tmp_piece.getFile() == curr_file &&
          tmp_piece.getRank() == curr_rank) {
        if (tmp_piece.getSide() != piece.getSide()) {
          move = piece.getType();
          move += 'x';
          move += curr_file + 'a';
          move += std::to_string(curr_rank + 1);
          possible_moves.push_back(move);
          disambiguate(move, possible_moves);
        }  // end if
        return;
      }  // end if
    }  // end for
    move = piece.getType();
    move += curr_file + 'a';
    move += std::to_string(curr_rank + 1);
    possible_moves.push_back(move);
    disambiguate(move, possible_moves);
  }  // end if

  if (direction == "n") {
    if (curr_rank == 7) {
      return;
    }  // end if
    getPosMovesRec(piece, possible_moves, curr_rank + 1, curr_file, direction,
                   false);
  }  // end if
  if (direction == "w") {
    if (curr_file == 0) {
      return;
    }  // end if
    getPosMovesRec(piece, possible_moves, curr_rank, curr_file - 1, direction,
                   false);
  }  // end if
  if (direction == "s") {
    if (curr_rank == 0) {
      return;
    }  // end if
    getPosMovesRec(piece, possible_moves, curr_rank - 1, curr_file, direction,
                   false);
  }  // end if
  if (direction == "e") {
    if (curr_file == 7) {
      return;
    }  // end if
    getPosMovesRec(piece, possible_moves, curr_rank, curr_file + 1, direction,
                   false);
  }  // end if
  if (direction == "nw") {
    if (curr_rank == 7 || curr_file == 0) {
      return;
    }  // end if
    getPosMovesRec(piece, possible_moves, curr_rank + 1, curr_file - 1,
                   direction, false);
  }  // end if
  if (direction == "ne") {
    if (curr_rank == 7 || curr_file == 7) {
      return;
    }  // end if
    getPosMovesRec(piece, possible_moves, curr_rank + 1, curr_file + 1,
                   direction, false);
  }  // end if
  if (direction == "sw") {
    if (curr_rank == 0 || curr_file == 0) {
      return;
    }  // end if
    getPosMovesRec(piece, possible_moves, curr_rank - 1, curr_file - 1,
                   direction, false);
  }  // end if
  if (direction == "se") {
    if (curr_rank == 0 || curr_file == 7) {
      return;
    }  // end if
    getPosMovesRec(piece, possible_moves, curr_rank - 1, curr_file + 1,
                   direction, false);
  }  // end if
}  // end getPosMovesRec()
```
