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

bool Piece::isBlocked(int side, int file2check, int rank2check) {
  for (Piece piece : local_board->pieces) {
    if (piece.getSide() == side && piece.getFile() == file2check &&
        piece.getRank() == rank2check) {
      return true;
      break;
    }
  }
  return false;
}

std::vector<std::string> Piece::possibleMoves() {
  std::vector<std::string> possible_moves;
  std::string move;

  // Pawn
  if (type == 'P') {
    bool blocked = false;
    if (side == 0) {
      if (rank == 1) {
        move = file + 'a';
        move += std::to_string(rank + 3);
        possible_moves.push_back(move);
      }
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
    }
    if (side == 1) {
      // normal movement
      if (rank == 6) {
        move = file + 'a';
        move += std::to_string(rank);
        possible_moves.push_back(move);
      }
      move = file + 'a';
      move += std::to_string(rank - 1);
      possible_moves.push_back(move);

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
    // up
    for (int i = rank + 1; i < 8; i++) {
      if (!isBlocked(side, file, i)) {
        move = 'R';
        move += file + 'a';
        move += std::to_string(i + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      } else {
        break;
      }
    }

    // down
    for (int i = rank - 1; i > 0; i--) {
      if (!isBlocked(side, file, i)) {
        move = 'R';
        move += file + 'a';
        move += std::to_string(i - 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      } else {
        break;
      }
    }

    // right
    for (int i = file + 1; i < 8; i++) {
      if (!isBlocked(side, i, rank)) {
        move = 'R';
        move += i + 'a';
        move += std::to_string(rank + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      } else {
        break;
      }
    }

    // left
    for (int i = file - 1; i > 0; i--) {
      if (!isBlocked(side, i, rank)) {
        move = 'R';
        move += i + 'a';
        move += std::to_string(rank + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      } else {
        break;
      }
    }
  }

  // Bishop
  if (type == 'B') {
    // top left
    for (int i = 1; file - i >= 0 && rank + i < 8; i++) {
      if (!isBlocked(side, file - i, rank + i)) {
        move = 'B';
        move += file - i + 'a';
        move += std::to_string(rank + i + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      } else {
        break;
      }
    }

    // top right
    for (int i = 1; file + i < 8 && rank + i < 8; i++) {
      if (!isBlocked(side, file + i, rank + i)) {
        move = 'B';
        move += file + i + 'a';
        move += std::to_string(rank + i + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      } else {
        break;
      }
    }

    // bottom left
    for (int i = 1; file - i >= 0 && rank - i >= 0; i++) {
      if (!isBlocked(side, file - i, rank - i)) {
        move = 'B';
        move += file - i + 'a';
        move += std::to_string(rank - i + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      } else {
        break;
      }
    }

    // bottom right
    for (int i = 1; file + i < 8 && rank - i >= 0; i++) {
      if (isBlocked(side, file + i, rank - i)) {
        move = 'B';
        move += file + i + 'a';
        move += std::to_string(rank - i + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      } else {
        break;
      }
    }
  }

  // Queen
  if (type == 'Q') {
    // up
    for (int i = rank + 1; i < 8; i++) {
      if (!isBlocked(side, file, i)) {
        move = 'R';
        move += file + 'a';
        move += std::to_string(i + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      } else {
        break;
      }
    }

    // down
    for (int i = rank - 1; i > 0; i--) {
      if (!isBlocked(side, file, i)) {
        move = 'R';
        move += file + 'a';
        move += std::to_string(i - 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      } else {
        break;
      }
    }

    // right
    for (int i = file + 1; i < 8; i++) {
      if (!isBlocked(side, i, rank)) {
        move = 'R';
        move += i + 'a';
        move += std::to_string(rank + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      } else {
        break;
      }
    }

    // left
    for (int i = file - 1; i > 0; i--) {
      if (!isBlocked(side, i, rank)) {
        move = 'R';
        move += i + 'a';
        move += std::to_string(rank + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      } else {
        break;
      }
    }

    // top left
    for (int i = 1; file - i >= 0 && rank + i < 8; i++) {
      if (!isBlocked(side, file - i, rank + i)) {
        move = 'B';
        move += file - i + 'a';
        move += std::to_string(rank + i + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      } else {
        break;
      }
    }

    // top right
    for (int i = 1; file + i < 8 && rank + i < 8; i++) {
      if (!isBlocked(side, file + i, rank + i)) {
        move = 'B';
        move += file + i + 'a';
        move += std::to_string(rank + i + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      } else {
        break;
      }
    }

    // bottom left
    for (int i = 1; file - i >= 0 && rank - i >= 0; i++) {
      if (!isBlocked(side, file - i, rank - i)) {
        move = 'B';
        move += file - i + 'a';
        move += std::to_string(rank - i + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      } else {
        break;
      }
    }

    // bottom right
    for (int i = 1; file + i < 8 && rank - i >= 0; i++) {
      if (isBlocked(side, file + i, rank - i)) {
        move = 'B';
        move += file + i + 'a';
        move += std::to_string(rank - i + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      } else {
        break;
      }
    }
  }

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
        // disambiguate
        disambiguate(move, possible_moves);
      }

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
          // disambiguate
          disambiguate(move, possible_moves);
        }

        // up
        if (!isBlocked(side, file, rank + 1)) {
          move = 'K';
          move += file + 'a';
          move += std::to_string(rank + 2);
          possible_moves.push_back(move);
          // taking
          move.insert(1, 1, 'x');
          possible_moves.push_back(move);
          // disambiguate
          disambiguate(move, possible_moves);
        }
      }

      // right down
      if (rank > 0) {
        if (!isBlocked(side, file + 1, rank - 1)) {
          move = 'K';
          move += file + 1 + 'a';
          move += std::to_string(rank - 2);
          possible_moves.push_back(move);
          // taking
          move.insert(1, 1, 'x');
          possible_moves.push_back(move);
          // disambiguate
          disambiguate(move, possible_moves);
        }

        // down
        if (!isBlocked(side, file, rank - 1)) {
          move = 'K';
          move += file + 'a';
          move += std::to_string(rank - 2);
          possible_moves.push_back(move);
          // taking
          move.insert(1, 1, 'x');
          possible_moves.push_back(move);
          // disambiguate
          disambiguate(move, possible_moves);
        }
      }
    }

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
        // disambiguate
        disambiguate(move, possible_moves);
      }

      // left up
      if (rank < 7) {
        if (!isBlocked(side, file - 1, rank)) {
          move = 'K';
          move += file - 1 + 'a';
          move += std::to_string(rank + 2);
          possible_moves.push_back(move);
          // taking
          move.insert(1, 1, 'x');
          possible_moves.push_back(move);
          // disambiguate
          disambiguate(move, possible_moves);
        }
      }
    }

    // left down
    if (rank > 0) {
      if (!isBlocked(side, file - 1, rank - 1)) {
        move = 'K';
        move += file - 1 + 'a';
        move += std::to_string(rank - 2);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
        // disambiguate
        disambiguate(move, possible_moves);
      }
    }

    // castling
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
