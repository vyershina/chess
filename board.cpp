#include <cstdlib>
#include <exception>
#include <iostream>

#include "board.hpp"

Board::Board() {
  // Pawns
  for (int i = 0; i < 8; i++) {
    Piece pawn(this, 0, 1, i, 'P', 'P');
    pieces.push_back(pawn);
  }
  for (int i = 0; i < 8; i++) {
    Piece pawn(this, 1, 6, i, 'P', 'p');
    pieces.push_back(pawn);
  }

  // Rooks
  {
    Piece wrook1(this, 0, 0, 0, 'R', 'R');
    pieces.push_back(wrook1);
    Piece wrook2(this, 0, 0, 7, 'R', 'R');
    pieces.push_back(wrook2);
    Piece brook1(this, 1, 7, 0, 'R', 'r');
    pieces.push_back(brook1);
    Piece brook2(this, 1, 7, 7, 'R', 'r');
    pieces.push_back(brook2);
  }

  // Bishop
  {
    Piece wbishop1(this, 0, 0, 2, 'B', 'B');
    pieces.push_back(wbishop1);
    Piece wbishop2(this, 0, 0, 5, 'B', 'B');
    pieces.push_back(wbishop2);
    Piece bbishop1(this, 1, 7, 2, 'B', 'b');
    pieces.push_back(bbishop1);
    Piece bbishop2(this, 1, 7, 5, 'B', 'b');
    pieces.push_back(bbishop2);
  }

  // Knights
  {
    Piece wknight1(this, 0, 0, 1, 'N', 'N');
    pieces.push_back(wknight1);
    Piece wknight2(this, 0, 0, 6, 'N', 'N');
    pieces.push_back(wknight2);
    Piece bknight1(this, 1, 7, 1, 'N', 'n');
    pieces.push_back(bknight1);
    Piece bknight2(this, 1, 7, 6, 'N', 'n');
    pieces.push_back(bknight2);
  }

  // Kings
  {
    Piece wking(this, 0, 0, 4, 'K', 'K');
    pieces.push_back(wking);
    Piece bking(this, 1, 7, 4, 'K', 'k');
    pieces.push_back(bking);
  }

  // Queens
  {
    Piece wqueen(this, 0, 0, 3, 'Q', 'Q');
    pieces.push_back(wqueen);
    Piece bqueen(this, 1, 7, 3, 'Q', 'q');
    pieces.push_back(bqueen);
  }
}

void Board::printBoard() {
  bool exists = false;
  int found = 0;
  for (int rank = 7; rank >= 0; rank--) {
    for (int file = 0; file < 8; file++) {
      found = 0;
      for (Piece piece : pieces) {
        if (piece.getRank() == rank && piece.getFile() == file) {
          std::cout << piece.getSymb() << " ";
          found++;
          try {
            if (found > 1) {
              throw(found);
            }
          } catch (int found) {
            std::cout << "\nTwo pieces are stacked on top of each other. "
                         "Terminating process. ";
            std::exit(-1);
          }
          exists = true;
        }
      }
      if (exists == false) {
        std::cout << "- ";
      }
      exists = false;
    }
    std::cout << "\n";
  }
}

void Board::passMove(std::string move, int side) {
  int mv_len = move.length();
  int fin_file = move[mv_len - 2] - 'a';
  int fin_rank = move[mv_len - 1] - '1';
  int castle = 0;
  char piece_type = move[0];
  bool taking = false;

  // handle unique
  if (piece_type >= 'a' && piece_type <= 'h') {
    piece_type = 'P';
  } else if (piece_type == 'O') {
    piece_type = 'K';
    if (mv_len == 5) {
      castle = 2;
    } else {
      castle = 1;
    }
  }

  // handle checks and checkmate
  if (fin_rank + '1' == '+') {
    fin_file = move[mv_len - 3] - 'a';
    fin_rank = move[mv_len - 2] - '1';
  }

  // handle taking
  for (char c : move) {
    if (c == 'x') {
      taking = true;
      break;
    }
  }
  if (taking == true) {
    for (int i = 0; i < pieces.size(); i++) {
      if (pieces[i].getRank() == fin_rank && pieces[i].getFile() == fin_file) {
        pieces.erase(pieces.begin() + i);
      }
    }
  }

  for (int i = 0; i < pieces.size(); i++) {
    if (pieces[i].getType() == piece_type && pieces[i].getSide() == side) {
      for (std::string a_move : pieces[i].possibleMoves()) {
        if (a_move == move) {
          pieces[i].makeMove(&pieces[i], fin_file, fin_rank, castle, taking);
        }
      }
    }
  }
}
