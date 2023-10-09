#include "PlusPiece.h"
using namespace puzzle;
PlusPiece::PlusPiece() : PuzzlePiece('P') {
	this->set_block(0,1);
	this->set_block(1,0);
	this->set_block(1,1);
	this->set_block(1,2);
	this->set_block(2,1);
}

