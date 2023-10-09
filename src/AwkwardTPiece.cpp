#include "AwkwardTPiece.h"
using namespace puzzle;
AwkwardTPiece::AwkwardTPiece() : PuzzlePiece('a') {
    this->set_block(1, 0);
    this->set_block(0, 1);
    this->set_block(1, 1);
    this->set_block(2, 1);
    this->set_block(2, 2);
}

