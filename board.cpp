#include <cstdlib>    // for idk
#include <exception>  // for exceptions
#include <iostream>

#include "board.hpp"

Board::Board() {
  // Pawns
  for (int i = 0; i < 8; i++) {
    Piece pawn(this, 0, 1, i, 'P', 'P');
    pieces.push_back(pawn);
  }  // end for
  for (int i = 0; i < 8; i++) {
    Piece pawn(this, 1, 6, i, 'P', 'p');
    pieces.push_back(pawn);
  }  // end for

  // Rooks
  Piece wrook1(this, 0, 0, 0, 'R', 'R');
  wrook1.setDir({"n", "e", "w", "s"});
  pieces.push_back(wrook1);
  Piece wrook2(this, 0, 0, 7, 'R', 'R');
  wrook2.setDir({"n", "e", "w", "s"});
  pieces.push_back(wrook2);
  Piece brook1(this, 1, 7, 0, 'R', 'r');
  brook1.setDir({"n", "e", "w", "s"});
  pieces.push_back(brook1);
  Piece brook2(this, 1, 7, 7, 'R', 'r');
  brook2.setDir({"n", "e", "w", "s"});
  pieces.push_back(brook2);

  // Bishop
  Piece wbishop1(this, 0, 0, 2, 'B', 'B');
  wbishop1.setDir({"ne", "nw", "se", "sw"});
  pieces.push_back(wbishop1);
  Piece wbishop2(this, 0, 0, 5, 'B', 'B');
  wbishop2.setDir({"ne", "nw", "se", "sw"});
  pieces.push_back(wbishop2);
  Piece bbishop1(this, 1, 7, 2, 'B', 'b');
  bbishop1.setDir({"ne", "nw", "se", "sw"});
  pieces.push_back(bbishop1);
  Piece bbishop2(this, 1, 7, 5, 'B', 'b');
  bbishop2.setDir({"ne", "nw", "se", "sw"});
  pieces.push_back(bbishop2);

  // Knights
  Piece wknight1(this, 0, 0, 1, 'N', 'N');
  pieces.push_back(wknight1);
  Piece wknight2(this, 0, 0, 6, 'N', 'N');
  pieces.push_back(wknight2);
  Piece bknight1(this, 1, 7, 1, 'N', 'n');
  pieces.push_back(bknight1);
  Piece bknight2(this, 1, 7, 6, 'N', 'n');
  pieces.push_back(bknight2);

  // Kings
  Piece wking(this, 0, 0, 4, 'K', 'K');
  pieces.push_back(wking);
  Piece bking(this, 1, 7, 4, 'K', 'k');
  pieces.push_back(bking);

  // Queens
  Piece wqueen(this, 0, 0, 3, 'Q', 'Q');
  wqueen.setDir({"n", "e", "w", "s", "ne", "nw", "se", "sw"});
  pieces.push_back(wqueen);
  Piece bqueen(this, 1, 7, 3, 'Q', 'q');
  bqueen.setDir({"n", "e", "w", "s", "ne", "nw", "se", "sw"});
  pieces.push_back(bqueen);
}  // end Board()

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
            }  // end if
          } catch (int found) {
            std::cout << "\nTwo pieces are stacked on top of each other. "
                         "Terminating process. ";
            std::exit(-1);
          }  // end try and catch
          exists = true;
        }  // end if
      }  // end for
      if (exists == false) {
        std::cout << "- ";
      }  // end if
      exists = false;
    }  // end for
    std::cout << "\n";
  }  // end for
}  // end printBoard()

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
    }  // end if(s) and else(s)
  }  // end if

  // handle checks and checkmate
  if (move[mv_len - 1] == '+' || move[mv_len - 1] == '#') {
    fin_file = move[mv_len - 3] - 'a';
    fin_rank = move[mv_len - 2] - '1';
    move.erase(move.end() - 1);
  }  // end if

  // handle taking
  for (char c : move) {
    if (c == 'x') {
      taking = true;
      break;
    }  // end if
  }  // end for

  for (int i = 0; i < pieces.size(); i++) {
    if (pieces[i].getType() == piece_type && pieces[i].getSide() == side) {
      std::vector<std::string> possible_moves;
      if (piece_type == 'Q' || piece_type == 'B' || piece_type == 'R') {
        for (std::string direction : pieces[i].getDirs()) {
          pieces[i].getPosMovesRec(pieces[i], possible_moves,
                                   pieces[i].getRank(), pieces[i].getFile(),
                                   direction, true);
        }
      } else {
        possible_moves = pieces[i].possibleMoves();
      }
      for (std::string a_move : possible_moves) {
        if (a_move == move) {
          pieces[i].makeMove(&pieces[i], fin_file, fin_rank, castle, taking);
        }  // end if
      }  // end for
    }  // end if
  }  // end for
}  // end passMove()
