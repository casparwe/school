#include "chess.h"

int main() {
  ChessBoard testBoard;

  testBoard.print_board();

  Rook* testRook = new Rook(WHITE);

  testBoard.place_piece(1,2,testRook);

  testBoard.print_board();

  std::cout<<"rook: \n";
  testRook->printMoves();

  Bishop* testBishop = new Bishop(BLACK);

  testBoard.place_piece(3,4,testBishop);

  testBoard.print_board();

  std::cout<<"bishop: \n";

  testBishop->printMoves();

  Knight* testKnight = new Knight(BLACK);

  testBoard.place_piece(0,4,testKnight);

  testBoard.print_board();

  std::cout<<"Knight: \n";

  testKnight->printMoves();

  Rook* testRook2 = new Rook(BLACK);

  testBoard.place_piece(3,2,testRook2);

  testBoard.print_board();

  std::cout<<"rook2: \n";
  testRook2->printMoves();

  Pawn* testPawn = new Pawn(BLACK);
  Pawn* testPawn2 = new Pawn(WHITE);

  testBoard.place_piece(4,3,testPawn2);
  testBoard.place_piece(2,5,testPawn);

  testBoard.print_board();

  std::cout<<"Pawns: \n";
  testPawn->printMoves();
  testPawn2->printMoves();

  King* testKing2 = new King(WHITE);
  King* testKing = new King(WHITE);

  testBoard.place_piece(1,4,testKing);
  testBoard.place_piece(3,3,testKing2);

  testBoard.print_board();

  std::cout<<"Kings: \n";

  testKing->printMoves();
  testKing2->printMoves();

  Queen* testQueen2 = new Queen(WHITE);
  Queen* testQueen = new Queen(WHITE);

  testBoard.place_piece(4,5,testQueen);
  testBoard.place_piece(2,3,testQueen2);

  testBoard.print_board();

  std::cout<<"Queens: \n";

  testQueen->printMoves();
  testQueen2->printMoves();

  testBoard.print_board();

  testBoard.clear_board();

  testBoard.print_board();

  testBoard.init_board();

  testBoard.print_board();

  testBoard.clear_board();



  return 0;
}
