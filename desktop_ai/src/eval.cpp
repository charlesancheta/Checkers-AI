#include "eval.h"

// returns a piece value
double pieceValue(Piece pc) {
  double pieceVal = 0; // assume empty at first
  if (pc != E) {
    if (pc == BK) {pieceVal = kingVal;}    
    else if (pc == B) {pieceVal = pawnVal;}    
    else if (pc == WK) {pieceVal = -kingVal;}    
    else if (pc == W) {pieceVal = -pawnVal;}
  }
  return pieceVal;
}

double positionValue(Piece pc, int8 pos) {
  // if the conditions are not met,
  // the piece does not contribute to the decision making
  int posVal = 0; 
  if (pc != E) {
    // check if the pieces are defending their back row
    if (pc == W || pc == WK) {
      if (pos > 27) {
        return backrow;
      }
    } else {
      if (pos < 4) {
        return backrow;
      }
    }
    // if piece is in the middle row
    if (pos > 11 && pos < 20) {
      posVal = midrow;
      // if the piece is in the middle box
      if (!(((pos - 13) % 4) && ((pos - 14) % 4))) {
        posVal = midbox;
      }
    }
  }
  return posVal;
}

// performs a static evaluation on the board
// according to the given heuristics
double staticEval(const Board& board) {
  double eval = 0;
  for (int i = 0; i < bSize; i++) {
    Piece pc = board.get(i);
    double posVal = positionValue(pc, i);
    // checks if the piece has not been evaluated yet
    if (posVal == 0) {
      posVal = secondCheck(board, i);
    }
    eval += pieceValue(pc) * posVal;
  }
  
  return eval;
}