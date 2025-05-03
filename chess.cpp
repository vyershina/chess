#include <cassert>
#include <fstream>  // for getting input from file
#include <iostream>
#include <regex>   // for input/move validation
#include <vector>  // for vectors

#include "board.hpp"
#include "stats.hpp"

void replaySystem();

std::vector<std::string> parseInput();

int countNewLines(const std::string* str);

void movesInVector(std::string moves_str, std::vector<std::string>& moves);

void printStats(Stats gamestats);

// Input: None
// Process: Calls replaySystem()
// Output: None
int main() {
  replaySystem();
  return 0;
}  // end main()

// Input Parameters: None.
// Process: Calls parseInput() to get vector of parsed moves.
//          Instantiates the game board.
//          Feeds/Passes in the moves to the board.
// Return Value: None.
void replaySystem() {
  int choice;
  std::cout << "Which would you like to do?\n";
  std::cout << "1. Replay (Read from file)\n";
  std::cout << "2. Play\n";
  std::cout << "Your choice: ";
  std::cin >> choice;
  while (choice != 1 && choice != 2) {
    std::cout << "Invalid input. Try again: ";
    std::cin >> choice;
    std::cout << '\n';
  }
  std::vector<std::string> moves;
  if (choice == 1) {
    moves = parseInput();
  }

  Board board;
  Stats gamestats;
  bool side = 0;

  if (choice == 1) {
    for (int i = 0; i < moves.size(); i++) {
      int side = i % 2;
      std::cout << "\nmove: " << moves[i] << "\nside: " << side
                << "\nmove num: " << i + 1 << "\n";
      board.passMove(moves[i], side, gamestats);
      board.printBoard();
    }  // end for
  } else if (choice == 2) {
    while (true) {
      std::string move;
      std::cout << "Make your move: ";
      std::cin >> move;
      std::cout << '\n';
      if (move == "end") {
        break;
      }
      board.passMove(move, side, gamestats);
      board.printBoard();
      side = !side;
    }
  }
  printStats(gamestats);
}  // end replaySystem()

// Input Parameters: None.
// Process: Reads game.txt file to get the PGN and store it in moves_str.
//          Replaces all the move numbers in moves_str with '\n'.
//          Calls countNewLines() and movesInVector().
// Return Value: Returns the moves vector which contains all parsed moves.
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
}  // end parseInput()

// Input Parameters: the string that contains all the moves
// Process: The '\n' in moves_str is counted.
// Return Value: Number of '\n' in moves_str.
int countNewLines(const std::string* moves_str) {
  int count = 0;
  for (char c : *moves_str) {
    if (c == '\n') {
      count++;
    }  // end if
  }  // end for
  return count;
}  // end countNewLines()

// Input Parameters: the string that contains all the moves, a reference to
//                   moves vector
// Process: moves in moves_str are parsed and placed into the moves
//          vector.
// Return Value: None.
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

void printStats(Stats gamestats) {
  std::cout << "\nGame stats:\n";
  std::cout << "Number of pawn moves: " << gamestats.pawn_moves << '\n';
  std::cout << "Number of queen moves: " << gamestats.queen_moves << '\n';
  std::cout << "Number of bishop moves: " << gamestats.bishop_moves << '\n';
  std::cout << "Number of rook moves: " << gamestats.rook_moves << '\n';
  std::cout << "Number of king moves: " << gamestats.king_moves << '\n';
  std::cout << "Number of knight moves: " << gamestats.knight_moves << '\n';
  std::cout << "Number of takes: " << gamestats.takes << '\n';
}
