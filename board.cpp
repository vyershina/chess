#include <iostream>

#include "board.hpp"

Board::Board() {
  Piece piece;

  // Pawns
  for (int i = 0; i < 8; i++) {
    piece.setType('P');
    piece.setRank(1);
    piece.setFile(i);
    piece.setSide('w');
    pieces.push_back(piece);
  }
  for (int i = 0; i < 8; i++) {
    piece.setType('p');
    piece.setRank(6);
    piece.setFile(i);
    piece.setSide('b');
    pieces.push_back(piece);
  }

  // Rooks
  {
    piece.setFile(0);
    piece.setRank(0);
    piece.setSide('w');
    piece.setType('R');
    pieces.push_back(piece);
  }
  {
    piece.setFile(7);
    piece.setRank(0);
    piece.setSide('w');
    piece.setType('R');
    pieces.push_back(piece);
  }
  {
    piece.setFile(0);
    piece.setRank(7);
    piece.setSide('b');
    piece.setType('r');
    pieces.push_back(piece);
  }
  {
    piece.setFile(7);
    piece.setRank(7);
    piece.setSide('b');
    piece.setType('r');
    pieces.push_back(piece);
  }

  // Bishop
  {
    piece.setFile(2);
    piece.setRank(0);
    piece.setSide('w');
    piece.setType('B');
    pieces.push_back(piece);
  }
  {
    piece.setFile(5);
    piece.setRank(0);
    piece.setSide('w');
    piece.setType('B');
    pieces.push_back(piece);
  }
  {
    piece.setFile(2);
    piece.setRank(7);
    piece.setSide('b');
    piece.setType('b');
    pieces.push_back(piece);
  }
  {
    piece.setFile(5);
    piece.setRank(7);
    piece.setSide('b');
    piece.setType('b');
    pieces.push_back(piece);
  }

  // Knights
  {
    piece.setFile(1);
    piece.setRank(0);
    piece.setSide('w');
    piece.setType('N');
    pieces.push_back(piece);
  }
  {
    piece.setFile(6);
    piece.setRank(0);
    piece.setSide('w');
    piece.setType('N');
    pieces.push_back(piece);
  }
  {
    piece.setFile(1);
    piece.setRank(7);
    piece.setSide('b');
    piece.setType('n');
    pieces.push_back(piece);
  }
  {
    piece.setFile(6);
    piece.setRank(7);
    piece.setSide('b');
    piece.setType('n');
    pieces.push_back(piece);
  }

  // Kings
  {
    piece.setFile(4);
    piece.setRank(0);
    piece.setSide('w');
    piece.setType('K');
    pieces.push_back(piece);
  }
  {
    piece.setRank(7);
    piece.setSide('b');
    piece.setType('k');
    pieces.push_back(piece);
  }

  // Queens
  {
    piece.setFile(3);
    piece.setRank(0);
    piece.setSide('w');
    piece.setType('Q');
    pieces.push_back(piece);
  }
  {
    piece.setFile(3);
    piece.setRank(7);
    piece.setSide('b');
    piece.setType('q');
    pieces.push_back(piece);
  }
}

void Board::boardPrinter() {
  bool found = false;
  for (int rank = 7; rank >= 0; rank--) {
    for (int file = 0; file < 8; file++) {
      for (int i = 0; i < 32; i++) {
        if (pieces[i].getRank() == rank && pieces[i].getFile() == file) {
          std::cout << pieces[i].getType() << " ";
          found = true;
        }
      }
      if (found == false) {
        std::cout << "- ";
      }
      found = false;
    }
    std::cout << "\n";
  }
}
