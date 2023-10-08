#include "MPiece.h"
using namespace puzzle;
MPiece::MPiece() : PuzzlePiece('M') {
    this->set_block(0,2);
    this->set_block(0,1);
    this->set_block(1,1);
    this->set_block(1,0);
    this->set_block(2,0);
}

