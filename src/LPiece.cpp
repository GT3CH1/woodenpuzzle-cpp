#include "LPiece.h"
using namespace puzzle;
LPiece::LPiece() : PuzzlePiece('L') {
    this->set_block(0,0);
    this->set_block(0,1);
    this->set_block(0,2);
    this->set_block(0,3);
    this->set_block(1,3);
}

