#include "IPiece.h"
#include "puzzlepiece.h"
using namespace puzzle;
IPiece::IPiece() : PuzzlePiece('I') {
	this->set_block(0, 0);
		this->set_block(1, 0);
		this->set_block(2, 0);
		this->set_block(3, 0);
		this->set_block(4, 0);
}
