#include "Puzzle.h"
using namespace puzzle;



std::tuple<bool, Board> Puzzle::solve(Board board, std::set<PuzzlePiece> available, std::set<PuzzlePiece> placed) {
    Board copy = Board(board);
    // iterate over all available Pieces
    for(auto piece : available) {
        if(placed.count(piece) != 0 or copy.piece_placed(piece.get_symbol())) {
            continue;
        }
        auto placed_copy = std::set<PuzzlePiece>(placed);
        auto piece_copy = PuzzlePiece(piece);
        for( int y = 0; y < 6; y++) {
            for(int x = 0; x < 10; x++) {
                for(int flip = 0; flip < 1; flip++) {
                    for(int rotate = 0; rotate < 4; rotate++){
                        if(copy.can_add_piece(x,y, piece_copy)) {
                            copy.add_piece(x,y, piece_copy);
                            if(!copy.is_invalid()) {
                                copy.print_board();
                                placed_copy.insert(piece_copy);
                                if(copy.is_solved()) {
                                    return std::make_tuple(true, copy);
                                }
                                else {
                                    if(std::get<0>(solve(Board(copy), available, placed_copy))) {
                                        return std::make_tuple(true, copy);
                                    }
                                }
                            }
                        } else {
                            copy = Board(board);
                            if (piece_copy.can_rotate()) {
                                piece_copy = piece_copy.rotate();
                            }
                            else {
                                break;
                            }
                        }
                    }
                }
                copy = Board(board);
                if (!piece_copy.is_symmetric()) {
                    piece_copy = piece_copy.flip_horizontal();
                }
                else {
                    break;
                }
            }
        }
    }

    return std::make_tuple(false, board);
}


int main() {
    auto pieces = std::set<PuzzlePiece>();
    auto placed = std::set<PuzzlePiece>();
    //pieces.insert(PlusPiece());
    //pieces.insert(UtahPiece());
    //pieces.insert(IPiece());
    pieces.insert(UPiece());
    //pieces.insert(TPiece());
    //pieces.insert(T2Piece());
    //pieces.insert(LongZPiece());
    //pieces.insert(ZPiece());
    Board board = Board();
    Puzzle::solve(Board(), pieces, placed);

}
