#include "ShortTPiece.h"
using namespace puzzle;
ShortTPiece::ShortTPiece() : PuzzlePiece('t') {
	this->set_block(0,0);
	this->set_block(1,0);
    this->set_block(2,0);
	this->set_block(3,0);
	this->set_block(2,1);
}

