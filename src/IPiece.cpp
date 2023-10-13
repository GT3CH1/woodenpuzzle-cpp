#include "IPiece.h"
#include "PuzzlePiece.h"
using namespace puzzle;
IPiece::IPiece()
    : PuzzlePiece('I')
{
	this->set_block(0, 0);
	this->set_block(0, 1);
	this->set_block(0, 2);
	this->set_block(0, 3);
	this->set_block(0, 4);
}
