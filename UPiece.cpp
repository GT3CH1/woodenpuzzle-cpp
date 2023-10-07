#include "UPiece.h"
using namespace puzzle;
UPiece::UPiece() : PuzzlePiece('u') {
	this->set_block(0,0);
	this->set_block(0,1);
	this->set_block(1,1);
	this->set_block(2,1);
	this->set_block(2,0);
}

