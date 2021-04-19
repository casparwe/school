#ifndef CHESSHEAD
#define CHESSHEAD

#define WHITE 1
#define BLACK 0



#include <iostream>
#include <string>
#include <memory>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include "matris_chess.h"
#include <uchar.h>
#include <stdint.h>




class ChessBoard;
class ChessPiece;
struct ChessMove;
bool inBoard(int to_x,int to_y);
void print_moves(std::vector<ChessMove> move_vector);

struct ChessMove {
    int from_x;
    int from_y;
    int to_x;
    int to_y;

    ChessPiece* piece;   // you can change the position of the chess piece with this pointer.
    ChessMove(int from_x_new,int from_y_new,int to_x_new,int to_y_new,ChessPiece* piece_new);
};

class ChessBoard {
  private:
    Matris<ChessPiece*> state; // Matris from lab 4 Matrix
  public:
    void print_board();
    void move_piece(ChessMove chessMove);
    void place_piece(int x,int y,ChessPiece* chessPiece);
    void init_board();
    void clear_board();
    bool check_empty(int x,int y);
    bool same_color(int x,int y, bool isWhite);
    std::vector<ChessMove> capturingMoves(bool isWhite);
    std::vector<ChessMove> nonCapturingMoves(bool isWhite);

    std::vector<std::shared_ptr<ChessPiece>> white_pieces;
    std::vector<std::shared_ptr<ChessPiece>> black_pieces;

    ChessBoard ();

    ~ChessBoard ();
};
ChessBoard & operator>>(std::istream & is, ChessBoard & chessBoard);


class ChessPiece {
  friend void ChessBoard::place_piece(int x,int y,ChessPiece* chessPiece);
  friend void ChessBoard::move_piece(ChessMove p);
  friend bool ChessBoard::same_color(int x,int y, bool isWhite);
  protected:                               // protected will cause problems
      int x,y;
      bool isWhite;
      ChessBoard* board;
      /**
       * Returns 0 if target square is unreachable.
       * Returns 1 if target square is reachable and empty.
       * Returns 2 if move captures a piece.
       */
      virtual int validMove(int to_x, int to_y){std::cout<<"undefined method 1"<<std::endl;return 0;}
  public:
      virtual char32_t utfRepresentation(){std::cout<<"undefined method 2"<<std::endl;return '-';}     // may be implemented as string
      virtual char latin1Representation(){std::cout<<"undefined method 3"<<std::endl;return '-';}
  //public: why utfRepresentation and latin1Representation protected?
      ChessPiece(int x, int y, bool isWhite, ChessBoard * board);
      ChessPiece(bool isWhite);
      bool capturingMove(int to_x, int to_y);
      bool nonCapturingMove(int to_x, int to_y);

      /*
      virtual std::vector<ChessMove> capturingMoves() {
        std::cout<<"undefined method 4"<<std::endl;
        std::vector<ChessMove> tmp;
        return tmp;
      }


      virtual std::vector<ChessMove> nonCapturingMoves() {
        std::cout<<"undefined method 5"<<std::endl;
        std::vector<ChessMove> tmp;
        return tmp;
      }
      */

      std::vector<ChessMove> capturingMoves() {
        std::vector<ChessMove> tmp;
        for (int i = 0; i < 8;i++){
          for (int j = 0; j < 8;j++){
            if (capturingMove(i, j)){
              ChessMove tmpMove(x,y,i,j,this);
              tmp.push_back(tmpMove);
            }
          }
        }
        return tmp;
      }


      std::vector<ChessMove> nonCapturingMoves() {
        std::vector<ChessMove> tmp;
        for (int i = 0; i < 8;i++){
          for (int j = 0; j < 8;j++){
            if (nonCapturingMove(i, j)){
              tmp.push_back(ChessMove(x,y,i,j,this));
            }
          }
        }
        return tmp;
      }

      void printMoves();

  /**
  * For testing multiple inheritance
  */
  int unnecessaryInt;
};




class Rook : virtual public ChessPiece {
public:
  using ChessPiece::ChessPiece;

  char32_t utfRepresentation() {
    if (isWhite) {return U'♖';}
    else {return U'♜';}
  }

  char latin1Representation() {
    if (isWhite) return 'R';
    else return 'r';
  }
protected:
  int validMove(int to_x, int to_y){
    if (inBoard(to_x,to_y) && (to_x == x)!=(to_y == y)){

      int y_cnt,x_cnt,y_change,x_change;
      if (to_x < x) {y_change = 0;x_change = -1;}
      else if (to_x > x) {y_change = 0;x_change = 1;}
      else if (to_y < y) {y_change = -1;x_change = 0;}
      else if (to_y > y) {y_change = 1;x_change = 0;}

      y_cnt = y + y_change;
      x_cnt = x + x_change;


      while (inBoard(x_cnt,y_cnt))
      {
        //std::cout<< "checking x = " <<x_cnt<< " y = "  << y_cnt<< std::endl;
        if(!board->check_empty(x_cnt,y_cnt))
        {
          if(x_cnt == to_x && y_cnt == to_y)
          {
            if(board->same_color(x_cnt,y_cnt,isWhite)) return 0;
            else return 2;
          }
          else return 0;
        }
        else if (x_cnt == to_x && y_cnt == to_y) return 1;

        y_cnt += y_change;
        x_cnt += x_change;
      }
      throw "should not be here";
    }
    return 0;
  }
};

/*
int tmp_int;
bool empty;
for (int x_dir = -1; x_dir <= 1; x_dir ++){
  for (int y_dir = -1; y_dir <= 1; y_dir ++){

    if(x_dir != 0 && y_dir != 0 || x_dir == 0 && y_dir == 0){continue;}

    tmp_int = 0;
    while(inBoard(x + tmp_int*x_dir,y + tmp_int*y_dir)){
      empty = check_empty(x + tmp_int,y)
    }
  }
*/



class Bishop : virtual public ChessPiece {
public:
  using ChessPiece::ChessPiece;

  char32_t utfRepresentation() {
    if (isWhite) {return U'♗';}
    else {return U'♝';}
  }

  char latin1Representation(){
    if (isWhite) {return 'B';}
    else {return 'b';}
  }
protected:
  int validMove(int to_x, int to_y){
    if (inBoard(to_x,to_y) && (to_x+to_y == x+y || to_x-to_y == x-y) && to_x != x){
      int xChange = 1, yChange = 1;
      bool done;
      if (to_x < x) {xChange = -1;}
      if (to_y < y) {yChange = -1;}
      int i = x + xChange;
      int j = y + yChange;

      while(inBoard(i,j)){
        done = (i == to_x && j == to_y);
        if (!board->check_empty(i,j)){
          if (done){
            if (board->same_color(i,j,isWhite)){return 0;}
            else {return 2;}
          }
          return 0;
        }
        else if (done){return 1;}
        i+=xChange;
        j+=yChange;
      }
    }
    return 0;
  }
};


class Knight : public ChessPiece {
  using ChessPiece::ChessPiece;

  int validMove(int to_x, int to_y){
    if (inBoard(to_x,to_y) && (pow((to_x - x),2) + pow((to_y-y),2)) == 5){
      if (board->check_empty(to_x,to_y)){return 1;}
      else if (!board->same_color(to_x,to_y,isWhite)) {return 2;}
    }
    return 0;
  }

  char32_t utfRepresentation() {
    if (isWhite) {return U'♘';}
    else {return U'♞';}
  }


  char latin1Representation(){
    if (isWhite) {return 'N';}
    else {return 'n';}
  }
};

class Pawn : public ChessPiece {
  using ChessPiece::ChessPiece;

  int validMove(int to_x, int to_y){
    int xChange = 1;

    if (isWhite) xChange = -1; //Detta gör att vit har höga x-sidan och svart har låga x-sidan

    bool start_pos = (isWhite && x == 6 )||( !isWhite && x == 1);

    if (inBoard(to_x,to_y)){

      if (to_x == x + xChange && to_y == y && board->check_empty(to_x,to_y)) return 1;

      else if (start_pos && to_x == x + 2*xChange && to_y == y && board->check_empty(to_x,to_y) && board->check_empty(to_x - xChange,to_y)) return 1;

      else if (to_x == x + xChange && abs(to_y - y) == 1 && !board->check_empty(to_x,to_y) && !board->same_color(to_x,to_y,isWhite) ) return 2;
    }
    return 0;
  }

  char32_t utfRepresentation() {
    if (isWhite) {return U'♙';}
    else {return U'♟︎';}
  }


  char latin1Representation(){
  if (isWhite) {return 'P';}
  else {return 'p';}
  }
};

class King : public ChessPiece {
    using ChessPiece::ChessPiece;

    int validMove(int to_x, int to_y){

      if (inBoard(to_x,to_y) && abs(to_x - x) <= 1 && abs(to_y - y) <= 1 && !((to_x == x) && (to_y == y))){
        if (board->check_empty(to_x,to_y)) return 1;
        else if (!board->same_color(to_x,to_y,isWhite)) return 2;
      }
      return 0;
    }


    char32_t utfRepresentation() {
      if (isWhite) {return U'♔';}
      else {return U'♚';}
    }


    char latin1Representation(){
    if (isWhite) {return 'K';}
    else {return 'k';}
    }

};



class Queen : public ChessPiece {  /*public Rook , public Bishop {

protected:

    int validMove(int to_x, int to_y){

      if (inBoard(to_x,to_y) && (to_x+to_y == x + y || to_x-to_y == x-y) && to_x != x) return Bishop::validMove(to_x,to_y);

      else if (inBoard(to_x,to_y) && !(to_x-x == 0 && to_y-y == 0)) return Rook::validMove(to_x,to_y);

      else return 0;
  }*/

public:

  //Queen(bool newIsWhite);


  char32_t utfRepresentation() {
    if (isWhite) {return U'♕';}
    else {return U'♛';}
  }


  char latin1Representation(){
  if (isWhite) {return 'Q';}
  else {return 'q';}
  }


protected:
  using ChessPiece::ChessPiece;

  int validMove(int to_x, int to_y){
    if (inBoard(to_x,to_y) && (to_x+to_y == x+y || to_x-to_y == x-y) && to_x != x){
      int xChange = 1, yChange = 1;
      bool done;
      if (to_x < x) {xChange = -1;}
      if (to_y < y) {yChange = -1;}
      int i = x + xChange;
      int j = y + yChange;

      while(inBoard(i,j)){
        done = (i == to_x && j == to_y);
        if (!board->check_empty(i,j)){
          if (done){
            if (board->same_color(i,j,isWhite)){return 0;}
            else {return 2;}
          }
          return 0;
        }
        else if (done){return 1;}
        i+=xChange;
        j+=yChange;
      }
    }
    else if (inBoard(to_x,to_y) && (to_x == x)!=(to_y == y)){

      int y_cnt,x_cnt,y_change = 0,x_change = 0;

      if (to_x < x)        x_change = -1;
      else if (to_x > x)   x_change = 1;
      else if (to_y < y)   y_change = -1;
      else if (to_y > y)   y_change = 1;

      y_cnt = y + y_change;
      x_cnt = x + x_change;

      while (inBoard(x_cnt,y_cnt))
      {
        //std::cout<< "checking x = " <<x_cnt<< " y = "  << y_cnt<< std::endl;
        if(!board->check_empty(x_cnt,y_cnt))
        {
          if(x_cnt == to_x && y_cnt == to_y)
          {
            if(board->same_color(x_cnt,y_cnt,isWhite)) return 0;
            else return 2;
          }
          else return 0;
        }
        else if (x_cnt == to_x && y_cnt == to_y) return 1;

        y_cnt += y_change;
        x_cnt += x_change;
      }
      throw "you shouldnt be here";
    }
    return 0;
  }


};



#endif
