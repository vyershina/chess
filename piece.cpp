#include <iostream>
#include <string>

#include "piece.hpp"

std::vector<std::string> Piece::possibleMoves() {
  std::vector<std::string> possible_moves;
  std::string move;

  // Pawn
  if (type == 'p' || type == 'P') {
    if (side == 'b') {
      // normal movement
      if (rank == 1) {
        move = file + 'a';
        move += std::to_string(rank + 3);
        possible_moves.push_back(move);
      }
      move = file + 'a';
      move += std::to_string(rank + 2);
      possible_moves.push_back(move);
      // taking
      if (rank != 1) {
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
    }
    if (side == 'w') {
      // normal movement
      if (rank == 6) {
        move = file + 'a';
        move += std::to_string(rank - 3);
        possible_moves.push_back(move);
      }
      move = file + 'a';
      move += std::to_string(rank - 2);
      possible_moves.push_back(move);
      // taking
      if (rank != 6) {
        move = file + 'a';
        move += 'x';
        move += file + 1 + 'a';
        move += std::to_string(rank - 2);
        possible_moves.push_back(move);

        move = file + 'a';
        move += 'x';
        move += file - 1 + 'a';
        move += std::to_string(rank - 2);
        possible_moves.push_back(move);
      }
    }
  }

  // Rook
  if (type == 'r' || type == 'R') {
    // File-wise
    for (int i = 0; i < 7; i++) {
      if (i != rank) {
        move = 'R';
        move += file + 'a';
        move += std::to_string(i + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
      }
    }
    // Rank-wise
    for (int i = 0; i < 7; i++) {
      if (i != file) {
        move = 'R';
        move += i + 1 + 'a';
        move += std::to_string(rank + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
      }
    }
  }

  // Bishop
  if (type == 'B' || type == 'b') {
    // top left
    for (int i = 0; file - i >= 0 && rank + i < 8; i++) {
      move = 'B';
      move += file - i + 'a';
      move += std::to_string(rank + i + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
    }
    // top right
    for (int i = 0; file + i < 8 && rank + i < 8; i++) {
      move = 'B';
      move += file + i + 'a';
      move += std::to_string(rank + i + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
    }
    // bottom left
    for (int i = 0; file - i >= 0 && rank - i >= 0; i++) {
      move = 'B';
      move += file - i + 'a';
      move += std::to_string(rank - i + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
    }
    // bottom right
    for (int i = 0; file + i < 8 && rank - i >= 0; i++) {
      move = 'B';
      move += file + i + 'a';
      move += std::to_string(rank - i + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
    }
  }

  // Queen
  if (type == 'Q' || type == 'q') {
    // top left
    for (int i = 0; file - i >= 0 && rank + i < 8; i++) {
      move = 'Q';
      move += file - i + 'a';
      move += std::to_string(rank + i + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
    }
    // top right
    for (int i = 0; file + i < 8 && rank + i < 8; i++) {
      move = 'Q';
      move += file + i + 'a';
      move += std::to_string(rank + i + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
    }
    // bottom left
    for (int i = 0; file - i >= 0 && rank - i >= 0; i++) {
      move = 'Q';
      move += file - i + 'a';
      move += std::to_string(rank - i + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
    }
    // bottom right
    for (int i = 0; file + i < 8 && rank - i >= 0; i++) {
      move = 'B';
      move += file + i + 'a';
      move += std::to_string(rank - i + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
    }
    // File-wise
    for (int i = 0; i < 7; i++) {
      if (i != rank) {
        move = 'Q';
        move += file + 'a';
        move += std::to_string(rank + i);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
      }
    }
    // Rank-wise
    for (int i = 0; i < 7; i++) {
      if (i != file) {
        move = 'Q';
        move += file + i + 'a';
        move += std::to_string(rank);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
      }
    }
  }

  // King
  if (type == 'K' || type == 'k') {
    if (file < 7) {
      move = 'K';
      move += file + 1 + 'a';
      move += std::to_string(rank);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
      if (rank < 7) {
        move = 'K';
        move += file + 1 + 'a';
        move += std::to_string(rank + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
      }
      if (rank > 0) {
        move = 'K';
        move += file + 1 + 'a';
        move += std::to_string(rank - 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
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
      if (rank < 7) {
        move = 'K';
        move += file - 1 + 'a';
        move += std::to_string(rank + 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
      }
      if (rank > 0) {
        move = 'K';
        move += file - 1 + 'a';
        move += std::to_string(rank - 1);
        possible_moves.push_back(move);
        // taking
        move.insert(1, 1, 'x');
        possible_moves.push_back(move);
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
    }
    if (rank > 0) {
      move = 'K';
      move += file + 'a';
      move += std::to_string(rank - 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
    }
  }

  // Knight
  if (type == 'N' || type == 'n') {
    // up right
    if (file + 1 < 8 && rank + 2 < 8) {
      move = 'N';
      move += file + 1 + 'a';
      move += std::to_string(rank + 2);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
    }
    // down right
    if (file + 1 < 8 && rank - 2 >= 0) {
      move = 'N';
      move += file + 1 + 'a';
      move += std::to_string(rank - 2);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
    }
    // up left
    if (file - 1 <= 0 && rank + 2 < 8) {
      move = 'N';
      move += file - 1 + 'a';
      move += std::to_string(rank + 2);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
    }
    // down left
    if (file - 1 <= 0 && rank - 2 >= 0) {
      move = 'N';
      move += file - 1 + 'a';
      move += std::to_string(rank - 2);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
    }
    // right up
    if (file + 2 < 8 && rank + 1 > 8) {
      move = 'N';
      move += file + 2 + 'a';
      move += std::to_string(rank + 1);
      possible_moves.push_back(move);
      // taking
      move.insert(1, 1, 'x');
      possible_moves.push_back(move);
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
    }
  }
  return possible_moves;
}

// setters
void Piece::setRank(int n) { rank = n; }

void Piece::setFile(int n) { file = n; }

void Piece::setSide(char c) { side = c; }

void Piece::setType(char c) { type = c; }

// getters
char Piece::getType() { return type; }

int Piece::getFile() { return file; }

int Piece::getRank() { return rank; }

char Piece::getSide() { return side; }
