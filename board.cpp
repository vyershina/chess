#include <cstdlib>
#include <exception>
#include <iostream>

#include "board.hpp"

void pieceMover(std::vector<std::string> moves);

Board::Board() {
  Piece piece;

  // Pawns
  for (int i = 0; i < 8; i++) {
    piece.setSymb('P');
    piece.setType('P');
    piece.setRank(1);
    piece.setFile(i);
    piece.setSide(0);
    pieces.push_back(piece);
  }
  for (int i = 0; i < 8; i++) {
    piece.setSymb('p');
    piece.setType('P');
    piece.setRank(6);
    piece.setFile(i);
    piece.setSide(1);
    pieces.push_back(piece);
  }

  // Rooks
  piece.setFile(0);
  piece.setRank(0);
  piece.setSide(0);
  piece.setType('R');
  piece.setSymb('R');
  pieces.push_back(piece);

  piece.setFile(7);
  piece.setRank(0);
  piece.setSide(0);
  piece.setType('R');
  piece.setSymb('R');
  pieces.push_back(piece);

  piece.setFile(0);
  piece.setRank(7);
  piece.setSide(1);
  piece.setType('R');
  piece.setSymb('r');
  pieces.push_back(piece);

  piece.setFile(7);
  piece.setRank(7);
  piece.setSide(1);
  piece.setType('R');
  piece.setSymb('r');
  pieces.push_back(piece);

  // Bishop
  piece.setFile(2);
  piece.setRank(0);
  piece.setSide(0);
  piece.setType('B');
  piece.setSymb('B');
  pieces.push_back(piece);

  piece.setFile(5);
  piece.setRank(0);
  piece.setSide(0);
  piece.setType('B');
  piece.setSymb('B');
  pieces.push_back(piece);

  piece.setFile(2);
  piece.setRank(7);
  piece.setSide(1);
  piece.setType('B');
  piece.setSymb('b');
  pieces.push_back(piece);

  piece.setFile(5);
  piece.setRank(7);
  piece.setSide(1);
  piece.setType('B');
  piece.setSymb('b');
  pieces.push_back(piece);

  // Knights
  piece.setFile(1);
  piece.setRank(0);
  piece.setSide(0);
  piece.setType('N');
  piece.setSymb('N');
  pieces.push_back(piece);

  piece.setFile(6);
  piece.setRank(0);
  piece.setSide(0);
  piece.setType('N');
  piece.setSymb('N');
  pieces.push_back(piece);

  piece.setFile(1);
  piece.setRank(7);
  piece.setSide(1);
  piece.setType('N');
  piece.setSymb('n');
  pieces.push_back(piece);

  piece.setFile(6);
  piece.setRank(7);
  piece.setSide(1);
  piece.setType('N');
  piece.setSymb('n');
  pieces.push_back(piece);

  // Kings
  piece.setFile(4);
  piece.setRank(0);
  piece.setSide(0);
  piece.setType('K');
  piece.setSymb('K');
  pieces.push_back(piece);

  piece.setFile(4);
  piece.setRank(7);
  piece.setSide(1);
  piece.setType('K');
  piece.setSymb('k');
  pieces.push_back(piece);

  // Queens
  piece.setFile(3);
  piece.setRank(0);
  piece.setSide(0);
  piece.setType('Q');
  piece.setSymb('Q');
  pieces.push_back(piece);

  piece.setFile(3);
  piece.setRank(7);
  piece.setSide(1);
  piece.setType('Q');
  piece.setSymb('q');
  pieces.push_back(piece);
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
  // for (Piece piece : pieces) {
  //   if (piece.getType() == 'R') {
  //     std::vector<std::string> moves = piece.possibleMoves();
  //     std::cout << "\nRook on rank = " << piece.getRank()
  //               << ", file = " << piece.getFile() << "\n";
  //     for (int i = 0; i < moves.size(); i++) {
  //       std::cout << moves[i] << " ";
  //     }
  //   }
  // }
}

void Board::movePiece(std::string move, int side) {
  int mv_len = move.length();
  int fin_file = move[mv_len - 2] - 'a';
  int fin_rank = move[mv_len - 1] - '1';
  char piece_type = move[0];
  bool taking = false;
  bool placed = false;

  // handle pawns
  if (piece_type >= 'a' && piece_type <= 'h') {
    piece_type = 'P';
  } else if (piece_type == 'O') {
    piece_type = 'K';
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

  // handle castling
  if (move == "O-O-O" || move == "O-O") {
    for (int i = 0; i < pieces.size(); i++) {
      if (placed == false) {
        if (pieces[i].getSide() == side && pieces[i].getType() == piece_type) {
          std::vector<std::string> possibleMoves = pieces[i].possibleMoves();
          for (std::string local_move : possibleMoves) {
            if (local_move == "O-O") {
              pieces[i].setFile(6);
            } else {
              pieces[i].setFile(2);
            }
          }
        }
        if (pieces[i].getSide() == side && pieces[i].getType() == 'R') {
          if (move == "O-O") {
            if (pieces[i].getFile() == 7) {
              pieces[i].setFile(5);
              placed = true;
            }
          } else {
            if (pieces[i].getFile() == 0) {
              pieces[i].setFile(3);
              placed = true;
            }
          }
        }
      }
    }
  }

  // make moves
  if (placed == false) {
    for (int i = 0; i < pieces.size(); i++) {
      if (pieces[i].getSide() == side && pieces[i].getType() == piece_type) {
        std::vector<std::string> possible_moves = pieces[i].possibleMoves();
        for (std::string local_move : possible_moves) {
          if (local_move == move) {
            pieces[i].setFile(fin_file);
            pieces[i].setRank(fin_rank);
            placed = true;
          }
        }
      }
    }
  }

  // when move wasnt made
  try {
    if (placed == false) {
      throw(placed);
    }
  } catch (bool placed) {
    std::cout << "Unable to make move. Terminating.";
    std::exit(-1);
  }
}

void Board::saveState() {}
