#include "UtahPiece.h"

using namespace puzzle;

UtahPiece::UtahPiece() : PuzzlePiece('U') {
    this->set_block(0, 0);
    this->set_block(1,0);
    this->set_block(2,0);
    this->set_block(1,1);
    this->set_block(2,1);
}
