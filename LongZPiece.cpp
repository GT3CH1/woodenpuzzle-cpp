#include "LongZPiece.h"
using namespace puzzle;
LongZPiece::LongZPiece() : PuzzlePiece('z') {
	this->set_block(0, 0);
	this->set_block(1, 0);
	this->set_block(1, 1);
	this->set_block(2, 1);
	this->set_block(3, 1);
}

