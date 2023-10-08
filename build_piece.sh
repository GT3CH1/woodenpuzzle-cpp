cp TPiece.cpp $1.cpp
cp TPiece.h $1.h
sed -i"" -e "s/TPiece/$1/g" $1.cpp
sed -i"" -e "s/TPiece/$1/g" $1.h
sed -i"" -e "s/T_PIECE/$2/g" $1.h
nvim $1.cpp Pieces.h
