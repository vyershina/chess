#include <iostream>
#include <string>

#include "board.hpp"

Piece::Piece(Board* board, int side, int rank, int file, char type, char symb)
    : local_board(board),
      side(side),
      rank(rank),
      file(file),
      type(type),
      symb(symb) {}

void Piece::disambiguate(std::string move,
                         std::vector<std::string>& possible_moves) {
  move.erase(move.begin() + 1);
  move.insert(1, 1, file + 'a');
  move.insert(2, std::to_string(rank + 1));
  move.insert(3, 1, 'x');
  possible_moves.push_back(move);
}

std::vector<std::string> Piece::possibleMoves() {
  std::vector<std::string> possible_moves;
  std::string move;

  // Pawn
  if (type == 'P') {
    if (side == 0) {
      // normal movement
      for (Piece piece : local_board->pieces) {
        if (piece.getSide() == side && piece.getFile() == file &&
            piece.getRank() == rank + 1) {
          break;
        } else if (piece.getSide() == side && piece.getFile() == file &&
                   piece.getRank() == rank + 2) {
          break;
        } else {
          move = file + 'a';
          move += std::to_string(rank + 2);
          possible_moves.push_back(move);
          if (rank == 1) {
            move = file + 'a';
            move += std::to_string(rank + 3);
            possible_moves.push_back(move);
          }
        }
      }

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
    }
    if (side == 1) {
      // normal movement
      for (Piece piece : local_board->pieces) {
        if (piece.getSide() == side && piece.getFile() == file &&
            piece.getRank() == rank - 1) {
          break;
        } else if (piece.getSide() == side && piece.getFile() == file &&
                   piece.getRank() == rank - 2) {
          break;
        } else {
          move = file + 'a';
          move += std::to_string(rank);
          possible_moves.push_back(move);
          if (rank == 6) {
            move = file + 'a';
            move += std::to_string(rank - 1);
            possible_moves.push_back(move);
          }
        }
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
    }
  }

  // Rook
  if (type == 'R') {
    // On file
    for (int i = 1; i < 8; i++) {
      if (i != rank) {
        move = 'R';
        move += file + 'a';
        move += std::to_string(i + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      }
    }
    // On rank
    for (int i = 1; i < 8; i++) {
      if (i != file) {
        move = 'R';
        move += i + 'a';
        move += std::to_string(rank + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      }
    }
  }

  // Bishop
  if (type == 'B') {
    // top left
    for (int i = 1; file - i >= 0 && rank + i < 8; i++) {
      move = 'B';
      move += file - i + 'a';
      move += std::to_string(rank + i + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
    // top right
    for (int i = 1; file + i < 8 && rank + i < 8; i++) {
      move = 'B';
      move += file + i + 'a';
      move += std::to_string(rank + i + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
    // bottom left
    for (int i = 1; file - i >= 0 && rank - i >= 0; i++) {
      move = 'B';
      move += file - i + 'a';
      move += std::to_string(rank - i + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
    // bottom right
    for (int i = 1; file + i < 8 && rank - i >= 0; i++) {
      move = 'B';
      move += file + i + 'a';
      move += std::to_string(rank - i + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
  }

  // Queen
  if (type == 'Q') {
    // top left
    for (int i = 1; file - i >= 0 && rank + i < 8; i++) {
      move = 'Q';
      move += file - i + 'a';
      move += std::to_string(rank + i + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
    // top right
    for (int i = 1; file + i < 8 && rank + i < 8; i++) {
      move = 'Q';
      move += file + i + 'a';
      move += std::to_string(rank + i + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
    // bottom left
    for (int i = 1; file - i >= 0 && rank - i >= 0; i++) {
      move = 'Q';
      move += file - i + 'a';
      move += std::to_string(rank - i + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
    // bottom right
    for (int i = 1; file + i < 8 && rank - i >= 0; i++) {
      move = 'B';
      move += file + i + 'a';
      move += std::to_string(rank - i + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
    // File-wise
    for (int i = 1; i < 8; i++) {
      if (i != rank) {
        move = 'Q';
        move += file + 'a';
        move += std::to_string(rank + i);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      }
    }
    // Rank-wise
    for (int i = 1; i < 8; i++) {
      if (i != file) {
        move = 'Q';
        move += file + i + 'a';
        move += std::to_string(rank);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      }
    }
  }

  // King
  if (type == 'K') {
    if (file < 7) {
      move = 'K';
      move += file + 1 + 'a';
      move += std::to_string(rank);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
      if (rank < 7) {
        move = 'K';
        move += file + 1 + 'a';
        move += std::to_string(rank + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      }
      if (rank > 0) {
        move = 'K';
        move += file + 1 + 'a';
        move += std::to_string(rank - 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      }
    }
    if (file > 0) {
      move = 'K';
      move += file - 1 + 'a';
      move += std::to_string(rank);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
      if (rank < 7) {
        move = 'K';
        move += file - 1 + 'a';
        move += std::to_string(rank + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      }
      if (rank > 0) {
        move = 'K';
        move += file - 1 + 'a';
        move += std::to_string(rank - 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      }
    }
    if (rank < 7) {
      move = 'K';
      move += file + 'a';
      move += std::to_string(rank + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
    if (rank > 0) {
      move = 'K';
      move += file + 'a';
      move += std::to_string(rank - 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
    move = "O-O-O";
    possible_moves.push_back(move);
    move = "O-O";
    possible_moves.push_back(move);
  }

  // Knight
  if (type == 'N') {
    // up right
    if (file + 1 < 8 && rank + 2 < 8) {
      move = 'N';
      move += file + 1 + 'a';
      move += std::to_string(rank + 3);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
    // down right
    if (file + 1 < 8 && rank - 2 >= 0) {
      move = 'N';
      move += file + 1 + 'a';
      move += std::to_string(rank - 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
    // up left
    if (file - 1 >= 0 && rank + 2 < 8) {
      move = 'N';
      move += file - 1 + 'a';
      move += std::to_string(rank + 3);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
    // down left
    if (file - 1 >= 0 && rank - 2 >= 0) {
      move = 'N';
      move += file - 1 + 'a';
      move += std::to_string(rank - 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
    // right up
    if (file + 2 < 8 && rank + 1 < 8) {
      move = 'N';
      move += file + 2 + 'a';
      move += std::to_string(rank + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
    // right down
    if (file + 2 < 8 && rank - 1 >= 0) {
      move = 'N';
      move += file + 2 + 'a';
      move += std::to_string(rank - 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
    // left up
    if (file - 2 >= 0 && rank + 1 > 8) {
      move = 'N';
      move += file - 2 + 'a';
      move += std::to_string(rank + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
    // left down
    if (file - 2 >= 0 && rank - 1 >= 0) {
      move = 'N';
      move += file - 2 + 'a';
      move += std::to_string(rank - 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      // disambiguate
      disambiguate(move, possible_moves);
    }
  }
  return possible_moves;
}

void Piece::makeMove(Piece* piece, int fin_file, int fin_rank, int castle,
                     bool taking) {
  if (castle == 1) {
    for (Piece& rook : local_board->pieces) {
      if (rook.getFile() == 7 && rook.getRank() == piece->getRank() &&
          rook.getSide() == piece->getSide()) {
        rook.setFile(5);
        piece->setFile(6);
      }
    }
  } else if (castle == 2) {
    for (Piece& rook : local_board->pieces) {
      if (rook.getFile() == 0 && rook.getRank() == piece->getRank() &&
          rook.getSide() == piece->getSide()) {
        rook.setFile(3);
        piece->setFile(2);
      }
    }
  } else {
    piece->setFile(fin_file);
    piece->setRank(fin_rank);
  }
}

// setters
void Piece::setRank(int n) { rank = n; }

void Piece::setFile(int n) { file = n; }

void Piece::setSide(int n) { side = n; }

void Piece::setType(char c) { type = c; }

void Piece::setSymb(char c) { symb = c; }

// getters
char Piece::getType() { return type; }

char Piece::getSymb() { return symb; }

int Piece::getFile() { return file; }

int Piece::getRank() { return rank; }

int Piece::getSide() { return side; }
