#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

#include "board.hpp"

void replaySystem();

std::vector<std::string> parseInput();

// counts number of '\n' to declare 2d vector.
int countNewLines(const std::string* str);

void movesInVector(std::string moves_str, std::vector<std::string>& moves);

void replaySystem() {
  std::vector<std::string> moves = parseInput();
  Board board;
  // for (Piece piece : board.pieces) {
  //   if (piece.getType() == 'Q') {
  //     for (std::string move : piece.possibleMoves()) {
  //       std::cout << move << "\n";
  //     }
  //     break;
  //   }
  // }
  for (int i = 0; i < moves.size(); i++) {
    board.printBoard();
    std::cout << "move num: " << i + 1;
    std::cout << "\n";
    int side = i % 2;
    board.passMove(moves[i], side);
  }
}

std::vector<std::string> parseInput() {
  // getting the PGN
  std::fstream game_file("game.txt");
  std::string moves_str;
  getline(game_file, moves_str);

  // regex is a digit followed by a literal dot
  std::regex move_num("(\\d+\\.)");
  moves_str = std::regex_replace(moves_str, move_num, "\n");

  int size = countNewLines(&moves_str);

  std::vector<std::string> moves(size * 2, "");
  movesInVector(moves_str, moves);
  return moves;
}

int countNewLines(const std::string* moves_str) {
  int count = 0;
  for (char c : *moves_str) {
    if (c == '\n') {
      count++;
    }
  }
  return count;
}

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
      }
      if (std::regex_match(moves[move_num], valid_move) == false) {
        std::cout << moves[move_num] << " -> ";
        std::cout << "Invalid move detected!\n";
      }
      move_num++;
    } else if (moves_str[i] == '\0') {
      return;
    } else if (moves_str[i] == ' ') {
      if (moves_str[i + 1] == '\n') {
        continue;
      }
      move_num++;
      continue;
    } else {
      moves[move_num] += moves_str[i];
    }
  }
}

int main() {
  replaySystem();
  return 0;
}
