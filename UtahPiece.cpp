#include "UtahPiece.h"

using namespace puzzle;

UtahPiece::UtahPiece() : PuzzlePiece('U') {
    this->set_block(0, 0);
    this->set_block(0, 1);
    this->set_block(0, 2);
    this->set_block(1, 1);
    this->set_block(1, 2);
}
