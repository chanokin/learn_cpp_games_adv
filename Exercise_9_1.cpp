#include <iostream>

using namespace std;
char *piece_names[] = {
    "Pawn", "Rook", "Knight", "Bishop", "Queen", "King"
};
int num_pieces[] = {8, 2, 2, 2, 1, 1};
enum PieceType{PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
int num_types = 6;

char* color_names[] = {
    "Black", "White"
};
enum Color{BLACK, WHITE};

class Piece{
    public:
        Piece(): type(0), color(0), movement(0), row(0), col(0){}
        inline void setType(int t){type = t;}
        inline int getType()const {return type;}
        inline void setColor(int c){color = c;}
        inline int getColor()const {return color;}
        inline void setMovement(int m){movement = m;}
        inline int getMovement()const {return movement;}
        inline void setPosition(const int in_row, const int in_col){
            row = in_row;
            col = in_col;
        }
        inline void getPosition(int &out_row, int &out_col) const{
            out_row = row;
            out_col = col;
        }

        inline void print() const{
            cout << color_names[color] << " - " << piece_names[type] << " at " << row << ", " << col << endl;}
    private:
        int type;
        int color;
        int movement; // needs something like an array
        int row, col;
};

class Pawn: public Piece{
    public:
        Pawn(int color=0){
            setColor(color); setType(PAWN); setMovement(PAWN);
        }
};

class Rook: public Piece{
    public:
        Rook(int color=0){
            setColor(color); setType(ROOK); setMovement(ROOK);
        }
};

class Knight: public Piece{
    public:
        Knight(int color=0){
            setColor(color); setType(KNIGHT); setMovement(KNIGHT);
        }
};

class Bishop: public Piece{
    public:
        Bishop(int color=0){
            setColor(color); setType(BISHOP); setMovement(BISHOP);
        }
};

class Queen: public Piece{
    public:
        Queen(int color=0){
            setColor(color); setType(QUEEN); setMovement(QUEEN);
        }
};

class King: public Piece{
    public:
        King(int color=0){
            setColor(color); setType(KING); setMovement(KING);
        }
};

class Set{
    public:
        Set(int color){
            int total_pieces = 0;
            int i;
            for(i = 0; i < num_types; i++){
                total_pieces += num_pieces[i];
            }
            _n_pieces = total_pieces;
            _pieces = new Piece[total_pieces];
            int processed = 0;
            for(i = 0; i < num_pieces[PAWN]; i++){
                _pieces[processed] = Pawn(color);

                if(color == BLACK){
                    _pieces[processed].setPosition(1, i);
                } else{
                    _pieces[processed].setPosition(6, i);
                }
                processed += 1; 
            }
            for(i = 0; i < num_pieces[ROOK]; i++){
                _pieces[processed] = Rook(color);

                if(color == BLACK){
                    _pieces[processed].setPosition(0, 7*i);
                } else{
                    _pieces[processed].setPosition(7, 7*i);
                }

                processed += 1; 
            }
            for(i = 0; i < num_pieces[KNIGHT]; i++){
                _pieces[processed] = Knight(color);

                if(color == BLACK){
                    _pieces[processed].setPosition(0, 1 + 5*i);
                } else{
                    _pieces[processed].setPosition(7, 1 + 5*i);
                }
                
                processed += 1; 
            }
            for(i = 0; i < num_pieces[BISHOP]; i++){
                _pieces[processed] = Bishop(color);

                if(color == BLACK){
                    _pieces[processed].setPosition(0, 2 + 3*i);
                } else{
                    _pieces[processed].setPosition(7, 2 + 3*i);
                }

                processed += 1; 
            }
            for(i = 0; i < num_pieces[QUEEN]; i++){
                _pieces[processed] = Queen(color);
                if(color == BLACK){
                    _pieces[processed].setPosition(0, 3);
                } else{
                    _pieces[processed].setPosition(7, 3);
                }

                processed += 1; 
            }
            for(i = 0; i < num_pieces[KING]; i++){
                _pieces[processed] = King(color);

                if(color == BLACK){
                    _pieces[processed].setPosition(0, 4);
                } else{
                    _pieces[processed].setPosition(7, 4);
                }

                processed += 1; 
            }



        }

        void print(){
            for(int i = 0; i < _n_pieces; i++){
                _pieces[i].print();
            }
        }
    private:
        Piece* _pieces;
        int _n_pieces;
};

int main(int argc, char* argv[]){
    Set blacks(BLACK);
    blacks.print();
    Set whites(WHITE);
    whites.print();

    return 0;

}