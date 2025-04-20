#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

#include "piece.hpp"

void replaySystem();

std::vector<std::vector<std::string>> readInput();

// counts number of '\n' to declare 2d vector.
int countNewLines(const std::string* str);

void vectorPopulation(const std::string* moves_str,
                      std::vector<std::vector<std::string>>& moves);

std::vector<std::vector<std::string>> readInput() {
  // getting the PGN
  std::fstream game_file("game.txt");
  std::string moves_str;
  getline(game_file, moves_str);

  // regex is a digit followed by a literal dot
  std::regex pattern("(\\d+\\.)");
  moves_str = std::regex_replace(moves_str, pattern, "\n");

  int size = countNewLines(&moves_str);
  std::vector<std::vector<std::string>> moves(size,
                                              std::vector<std::string>(1, ""));
  vectorPopulation(&moves_str, moves);
  for (int i = 0; i < size; i++) {
    std::cout << moves[i][0] << " " << moves[i][1] << "\n";
  }
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

void vectorPopulation(const std::string* moves_str,
                      std::vector<std::vector<std::string>>& moves) {
  int i = 0;
  int move_num = 0;
  int side = 0;
  for (char c : *moves_str) {
    if (c == '\n') {
      if (i == 0) {
        i++;
        continue;
      }
      side = 0;
      move_num++;
    } else if (c == '\0') {
      return;
    } else if (c == ' ') {
      side++;
    } else {
      moves[move_num][side] += c;
    }
  }
}

int main() {
  Piece piece;
  piece.setFile(4);
  piece.setRank(3);
  piece.setSide('w');
  piece.setType('K');
  std::vector<std::string> moves = piece.possibleMoves();
  for (int i = 0; i < moves.size(); i++) {
    std::cout << moves[i] << " ";
  }
  return 0;
}
