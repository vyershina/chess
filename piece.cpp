#include <iostream>
#include <string>  // for strings

#include "board.hpp"

// Input Parameters: Reference to the board the game is being played on,
//                   Which side the piece belongs to.
//                   The starting rank of the piece.
//                   The starting file of the piece.
//                   The type (bishop, rook, pawn, etc) of the piece.
//                   The symbol of the piece (for differentation)
// Process: Initializes the piece with all the inputs.
// Return Value: None.
Piece::Piece(Board* board, int side, int rank, int file, char type, char symb)
    : local_board(board),
      side(side),
      rank(rank),
      file(file),
      type(type),
      symb(symb) {}  // end Piece()

// Input Parameters: The move being played.
//                   A reference to the possible_moves vector.
// Process: Inserts characters to disambiguate the moves in
//          case move is ambiguous.
// Return Value: None.
void Piece::disambiguate(std::string move,
                         std::vector<std::string>& possible_moves) {
  move.insert(1, 1, file + 'a');
  possible_moves.push_back(move);
  move.insert(2, std::to_string(rank + 1));
  possible_moves.push_back(move);
}  // end disambiguate()

// Base case: if direction the piece is headed in ends (end of board or blocked)
// Input Parameters: A piece, its possible moves, the current rank and file we
//                   are interested in, the direction which the piece is going
//                   in, if the current square we're on is the starting position
//                   or not
// Process: Builds all possible moves for a piece on a certain square.
//          Calls itself to go further in original direction.
// Output: None.
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

// Input Parameters: The side which the piece belongs to.
//                   The file being checked.
//                   The rank being checked.
// Process: Checks if a piece exists on the file and rank given.
// Return Value: Bool, true if exists, false if not.
bool Piece::isBlocked(int side, int file2check, int rank2check) {
  for (Piece piece : local_board->pieces) {
    if (piece.getSide() == side && piece.getFile() == file2check &&
        piece.getRank() == rank2check) {
      return true;
    }  // end if
  }  // end for
  return false;
}  // end isBlocked()

// Input Parameters: None.
// Process: Creates a list of possible moves for a piece.
//          Calls disambiguate() and isBlocked().
// Return Value: List of possible moves in a vector, possible_moves.
std::vector<std::string> Piece::possibleMoves() {
  std::vector<std::string> possible_moves;
  std::string move;

  // Pawn
  if (type == 'P') {
    if (side == 0) {
      if (rank == 1) {
        move = file + 'a';
        move += std::to_string(rank + 3);
        possible_moves.push_back(move);
      }
      // end if
      move = file + 'a';
      move += std::to_string(rank + 2);
      possible_moves.push_back(move);

      // taking
      move = file + 'a';
      move += 'x';
      move += file + 1 + 'a';
      move += std::to_string(rank + 2);
      possible_moves.push_back(move);

      move = file + 'a';
      move += 'x';
      move += file - 1 + 'a';
      move += std::to_string(rank + 2);
      possible_moves.push_back(move);
    }  // end if

    if (side == 1) {
      // normal movement
      if (rank == 6) {
        if (!isBlocked(0, file, rank - 1) && !isBlocked(0, file, rank - 2)) {
          if (!isBlocked(1, file, rank - 1) && !isBlocked(1, file, rank - 2)) {
            move = file + 'a';
            move += std::to_string(rank - 1);
            possible_moves.push_back(move);
          }
        }
      }  // end if
      if (!isBlocked(0, file, rank + 1) && !isBlocked(1, file, rank + 1)) {
        move = file + 'a';
        move += std::to_string(rank);
        possible_moves.push_back(move);
      }

      // taking
      move = file + 'a';
      move += 'x';
      move += file + 1 + 'a';
      move += std::to_string(rank);
      possible_moves.push_back(move);

      move = file + 'a';
      move += 'x';
      move += file - 1 + 'a';
      move += std::to_string(rank);
      possible_moves.push_back(move);
    }  // end if
  }  // end if

  // King
  if (type == 'K') {
    // right
    if (file < 7) {
      if (!isBlocked(side, file + 1, rank)) {
        move = 'K';
        move += file + 1 + 'a';
        move += std::to_string(rank + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
      }  // end if

      // right up
      if (rank < 7) {
        if (!isBlocked(side, file + 1, rank + 1)) {
          move = 'K';
          move += file + 1 + 'a';
          move += std::to_string(rank + 2);
          possible_moves.push_back(move);
          // taking
          move.insert(1, 1, 'x');
          possible_moves.push_back(move);
        }  // end if
      }  // end if

      // right down
      if (rank > 0) {
        if (!isBlocked(side, file + 1, rank - 1)) {
          move = 'K';
          move += file + 1 + 'a';
          move += std::to_string(rank);
          possible_moves.push_back(move);
          // taking
          move.insert(1, 1, 'x');
          possible_moves.push_back(move);
        }  // end if
      }  // end if
    }  // end if

    // up
    if (rank < 7) {
      if (!isBlocked(side, file, rank + 1)) {
        move = 'K';
        move += file + 'a';
        move += std::to_string(rank + 2);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
      }  // end if
    }  // end if

    // down
    if (rank > 0) {
      if (!isBlocked(side, file, rank - 1)) {
        move = 'K';
        move += file + 'a';
        move += std::to_string(rank);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
      }  // end if
    }  // end if

    // left
    if (file > 0) {
      if (!isBlocked(side, file - 1, rank)) {
        move = 'K';
        move += file - 1 + 'a';
        move += std::to_string(rank + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
      }  // end if

      // left up
      if (rank < 7) {
        if (!isBlocked(side, file - 1, rank + 1)) {
          move = 'K';
          move += file - 1 + 'a';
          move += std::to_string(rank + 2);
          possible_moves.push_back(move);
          // taking
          move.insert(1, 1, 'x');
          possible_moves.push_back(move);
        }  // end if
      }  // end if
    }  // end if

    // left down
    if (rank > 0) {
      if (!isBlocked(side, file - 1, rank - 1)) {
        move = 'K';
        move += file - 1 + 'a';
        move += std::to_string(rank);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
      }  // end if
    }  // end if

    // castling
    move = "O-O-O";
    possible_moves.push_back(move);
    move = "O-O";
    possible_moves.push_back(move);
  }  // end if

  // Knight
  if (type == 'N') {
    // up right
    if (file + 1 < 8 && rank + 2 < 8) {
      move = 'N';
      move += file + 1 + 'a';
      move += std::to_string(rank + 3);
      possible_moves.push_back(move);
      disambiguate(move, possible_moves);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      disambiguate(move, possible_moves);
    }  // end if

    // down right
    if (file + 1 < 8 && rank - 2 >= 0) {
      move = 'N';
      move += file + 1 + 'a';
      move += std::to_string(rank - 1);
      possible_moves.push_back(move);
      disambiguate(move, possible_moves);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      disambiguate(move, possible_moves);
    }  // end if

    // up left
    if (file - 1 >= 0 && rank + 2 < 8) {
      move = 'N';
      move += file - 1 + 'a';
      move += std::to_string(rank + 3);
      possible_moves.push_back(move);
      disambiguate(move, possible_moves);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      disambiguate(move, possible_moves);
    }  // end if

    // down left
    if (file - 1 >= 0 && rank - 2 >= 0) {
      move = 'N';
      move += file - 1 + 'a';
      move += std::to_string(rank - 1);
      possible_moves.push_back(move);
      disambiguate(move, possible_moves);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      disambiguate(move, possible_moves);
    }  // end if

    // right up
    if (file + 2 < 8 && rank + 1 < 8) {
      move = 'N';
      move += file + 2 + 'a';
      move += std::to_string(rank + 2);
      possible_moves.push_back(move);
      disambiguate(move, possible_moves);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      disambiguate(move, possible_moves);
    }  // end if

    // right down
    if (file + 2 < 8 && rank - 1 >= 0) {
      move = 'N';
      move += file + 2 + 'a';
      move += std::to_string(rank);
      possible_moves.push_back(move);
      disambiguate(move, possible_moves);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      disambiguate(move, possible_moves);
    }  // end if

    // left up
    if (file - 2 >= 0 && rank + 1 < 8) {
      move = 'N';
      move += file - 2 + 'a';
      move += std::to_string(rank + 2);
      possible_moves.push_back(move);
      disambiguate(move, possible_moves);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      disambiguate(move, possible_moves);
    }  // end if

    // left down
    if (file - 2 >= 0 && rank - 1 >= 0) {
      move = 'N';
      move += file - 2 + 'a';
      move += std::to_string(rank);
      possible_moves.push_back(move);
      disambiguate(move, possible_moves);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      disambiguate(move, possible_moves);
    }  // end if
  }  // end if
  return possible_moves;
}  // end possibleMoves()

void Piece::makeMove(Piece* piece, int fin_file, int fin_rank, int castle,
                     bool taking) {
  Piece local_piece = *piece;
  if (castle == 1) {
    for (Piece& rook : local_board->pieces) {
      if (rook.getFile() == 7 && rook.getRank() == piece->getRank() &&
          rook.getSide() == piece->getSide()) {
        rook.setFile(5);
        piece->setFile(6);
        return;
      }  // end if
    }  // end for
  } else if (castle == 2) {
    for (Piece& rook : local_board->pieces) {
      if (rook.getFile() == 0 && rook.getRank() == piece->getRank() &&
          rook.getSide() == piece->getSide()) {
        rook.setFile(3);
        piece->setFile(2);
        return;
      }  // end if
    }  // end for
  }  // end if(s) and else(s)
  if (taking) {
    for (int i = 0; i < local_board->pieces.size(); i++) {
      if (local_board->pieces[i].getRank() == fin_rank &&
          local_board->pieces[i].getFile() == fin_file) {
        piece->setFile(fin_file);
        piece->setRank(fin_rank);
        if (local_board->pieces[i].getSymb() == piece->getSymb()) {
          continue;
        } else {
          local_board->pieces.erase(local_board->pieces.begin() + i);
          return;
        }  // end if(s) and else(s)
      }  // end if
    }  // end for
  }  // end if
  piece->setFile(fin_file);
  piece->setRank(fin_rank);
}  // end makeMove()

// Setter methods
void Piece::setRank(int n) { rank = n; }

void Piece::setFile(int n) { file = n; }

void Piece::setSide(int n) { side = n; }

void Piece::setType(char c) { type = c; }

void Piece::setSymb(char c) { symb = c; }

void Piece::setDir(std::vector<std::string> dirs) { directions = dirs; }

// Getter methods
std::vector<std::string> Piece::getDirs() { return directions; }

char Piece::getType() { return type; }

char Piece::getSymb() { return symb; }

int Piece::getFile() { return file; }

int Piece::getRank() { return rank; }

int Piece::getSide() { return side; }
