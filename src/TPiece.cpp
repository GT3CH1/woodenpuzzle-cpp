#include "TPiece.h"
using namespace puzzle;
TPiece::TPiece() : PuzzlePiece('T') {
	this->set_block(0,0);
	this->set_block(1,0);
    this->set_block(2,0);
	this->set_block(1,1);
	this->set_block(1,2);
}

