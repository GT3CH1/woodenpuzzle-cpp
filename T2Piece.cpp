#include "T2Piece.h"
using namespace puzzle;
T2Piece::T2Piece() : PuzzlePiece('2') {
	this->set_block(0,0);
	this->set_block(1,0);
	this->set_block(2,0);
	this->set_block(1,1);
	this->set_block(1,2);
}

