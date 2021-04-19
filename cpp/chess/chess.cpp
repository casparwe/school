#include "chess.h"

///////                  support

bool inBoard(int to_x,int to_y){return to_x>=0 && to_x<=7 && to_y>=0 && to_y<=7;}


///////               ChessMove




ChessMove::ChessMove(int from_x_new,int from_y_new,int to_x_new,int to_y_new,ChessPiece* piece_new) : from_x(from_x_new), from_y(from_y_new), to_x(to_x_new), to_y(to_y_new), piece(piece_new) {}




///////               ChessPiece




ChessPiece::ChessPiece (int newX,int newY,bool newisWhite, ChessBoard* newBoard) : x (newX),y(newY),isWhite(newisWhite),board(newBoard) {}


ChessPiece::ChessPiece (bool newisWhite) : isWhite (newisWhite) {}

//Queen::Queen(bool newisWhite) : Rook(newisWhite) {}


bool ChessPiece::capturingMove(int to_x, int to_y){
  int8_t res = validMove(to_x,to_y);
  if(res == 2){return true;}
  else{return false;}
}


bool ChessPiece::nonCapturingMove(int to_x, int to_y){
  int8_t res = validMove(to_x,to_y);
  if(res == 1){return true;}
  else{return false;}
}


void ChessPiece::printMoves(){

  std::vector<ChessMove> nonCapMoves = nonCapturingMoves();
  std::vector<ChessMove> capMoves = capturingMoves();

  std::cout << "capturing moves:" <<std::endl;
  for (std::vector<ChessMove>::iterator it = capMoves.begin() ; it != capMoves.end(); ++it) {
    std::cout << "from " << it->from_x <<" "<< it->from_y << " to " << it->to_x << " " << it->to_y <<std::endl;
  }
  std::cout << '\n';

  std::cout << "non capturing moves:" <<std::endl;


  for (std::vector<ChessMove>::iterator it = nonCapMoves.begin() ; it != nonCapMoves.end(); ++it) {
    std::cout << "from " << it->from_x <<" "<< it->from_y << " to " << it->to_x << " " << it->to_y <<std::endl;
  }
  std::cout << '\n';
}




///////                ChessBoard



void ChessBoard::init_board(){
  for (int i = 0; i <= 7; i++){
    Pawn* blackPawn = new Pawn(BLACK);
    Pawn* whitePawn = new Pawn(WHITE);
    place_piece(1,i,blackPawn);
    place_piece(6,i,whitePawn);
  }


  for (int i = 0; i <= 7; i += 7){
    Rook* blackRook = new Rook(BLACK);
    Rook* whiteRook = new Rook(WHITE);
    place_piece(0,i,blackRook);
    place_piece(7,i,whiteRook);
  }

  for (int i = 1; i <= 7; i+=5){
    Knight* blackKnight = new Knight(BLACK);
    Knight* whiteKnight = new Knight(WHITE);
    place_piece(0,i,blackKnight);
    place_piece(7,i,whiteKnight);
  }


  for (int i = 2; i <= 5; i+=3){
    Bishop* blackBishop = new Bishop(BLACK);
    Bishop* whiteBishop = new Bishop(WHITE);
    place_piece(0,i,blackBishop);
    place_piece(7,i,whiteBishop);
  }

  King* blackKing = new King(BLACK);
  King* whiteKing = new King(WHITE);
  place_piece(0,4,blackKing);
  place_piece(7,4,whiteKing);

  Queen* blackQueen = new Queen(BLACK);
  Queen* whiteQueen = new Queen(WHITE);
  place_piece(0,3,blackQueen);
  place_piece(7,3,whiteQueen);


}


ChessBoard::~ChessBoard (){
  for (int i = 0; i < 8 ; i++){
    for (int j = 0; j < 8; j++){
      if (state(j,i) != nullptr){
        //delete state(j,i);
      }
    }
  }
}


void ChessBoard::clear_board(){
  for (int i = 0; i < 8 ; i++){
    for (int j = 0; j < 8; j++){
      if (state(j,i) != nullptr){
        //std::cout<<"delete piece on "<< j << " " << i << "\n";

        //ChessPiece * toremove = state(j,i);

        //std::cout<< state(j,i)->latin1Representation() <<"\n";

        //delete state(j,i);

        //std::cout<<"here 2\n";

        state(j,i) = nullptr;
      }
    }
  }
}

ChessBoard::ChessBoard(){
  Matris<ChessPiece*> tmpState(8);
  state = tmpState;
  /*
  for (int i = 0; i < 8 ; i++){
    for (int j = 0; j < 8; j++){
      state(j,i) = nullptr;
    }
  }
  */
}

void ChessBoard::place_piece(int x,int y,ChessPiece* chessPiece){//expects empty square
  state(x,y) = chessPiece;
  chessPiece->x = x;
  chessPiece->y = y;
  chessPiece->board = this;
}


bool ChessBoard::check_empty(int x,int y){
  return state(x,y)==nullptr;
}

bool ChessBoard::same_color(int x,int y, bool isWhite){
  if(state(x,y)==nullptr) throw "accessing empty square";
  return state(x,y)->isWhite==isWhite;
}

void ChessBoard::print_board(){
  for (int x = 0; x < 8 ; x++){
    for (int y = 0; y < 8; y++){
      if(state(x,y) == nullptr) std::cout<<"- ";
      else std::cout<<state(x,y)->latin1Representation()<<" ";
    }
    std::cout<<std::endl;
  }
  std::cout<<std::endl;
}
