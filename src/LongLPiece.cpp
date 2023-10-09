#include "LongLPiece.h"
using namespace puzzle;
LongLPiece::LongLPiece() : PuzzlePiece('B') {
	this->set_block(0,0);
	this->set_block(1,0);
	this->set_block(2,0);
	this->set_block(2,1);
	this->set_block(2,2);
}

