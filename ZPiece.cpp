#include "ZPiece.h"
using namespace puzzle;
ZPiece::ZPiece() : PuzzlePiece('Z') {
	this->set_block(0, 0);
	this->set_block(1, 0);
	this->set_block(1, 1);
	this->set_block(1, 2);
	this->set_block(1, 3);
	this->set_block(2, 3);
}

