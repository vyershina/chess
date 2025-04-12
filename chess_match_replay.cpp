#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

void replaySystem();

std::vector<std::vector<std::string>> readInput();

int countNewLines(const std::string* str);

void vectorPopulation(const std::string* moves_str,
                      std::vector<std::vector<std::string>>& moves);

void printMoves(const std::vector<std::vector<std::string>>& moves);

std::vector<std::vector<std::string>> readInput() {
  // getting the PGN
  std::fstream game_file("game.txt");
  std::string moves_str;
  getline(game_file, moves_str);

  // regex is a digit followed by a literal dot
  std::regex pattern("(\\d+\\.)");
  moves_str = std::regex_replace(moves_str, pattern, "\n");

  // counting the number of '\n' to declare a 2d vector to store all the moves.
  int size = countNewLines(&moves_str);
  std::vector<std::vector<std::string>> moves(size,
                                              std::vector<std::string>(1, ""));

  vectorPopulation(&moves_str, moves);
  printMoves(moves);

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

void printMoves(const std::vector<std::vector<std::string>>& moves) {
  for (int i = 0; i < 53; i++) {
    std::cout << moves[i][0] << " " << moves[i][1] << " " << moves[52][2]
              << std::endl;
  }
}

int main() {
  readInput();
  return 0;
}
