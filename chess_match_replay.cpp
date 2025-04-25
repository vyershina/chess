#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

#include "board.hpp"

void replaySystem();

std::vector<std::vector<std::string>> parseInput();

// counts number of '\n' to declare 2d vector.
int countNewLines(const std::string* str);

void vectorPopulation(const std::string* moves_str,
                      std::vector<std::vector<std::string>>& moves);

void replaySystem() {
  std::vector<std::vector<std::string>> moves = parseInput();
  Board board;
  board.boardPrinter();
}

std::vector<std::vector<std::string>> parseInput() {
  // getting the PGN
  std::fstream game_file("game.txt");
  std::string moves_str;
  getline(game_file, moves_str);

  // regex is a digit followed by a literal dot
  std::regex move_num("(\\d+\\.)");
  moves_str = std::regex_replace(moves_str, move_num, "\n");

  int size = countNewLines(&moves_str);
  std::vector<std::vector<std::string>> moves(size,
                                              std::vector<std::string>(2, ""));
  vectorPopulation(&moves_str, moves);
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
  bool side = 0;
  std::regex valid_move(
      "(([RNBKQ])?([a-h])?([1-8])?(x)?([a-h][1-8])(\\+|\\#)?)?((O-O)(-O)?)?");
  for (char c : *moves_str) {
    if (c == '\n') {
      if (i == 0) {
        i++;
        continue;
      }
      if (std::regex_match(moves[move_num][side], valid_move) == false) {
        std::cout << moves[move_num][side] << " -> ";
        std::cout << "Invalid move detected!\n";
      }
      side = !side;
      move_num++;
    } else if (c == '\0') {
      return;
    } else if (c == ' ') {
      side = !side;
    } else {
      moves[move_num][side] += c;
    }
  }
}

int main() {
  replaySystem();
  return 0;
}
