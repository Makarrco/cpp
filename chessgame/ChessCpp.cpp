/******************************************************************************



*******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int SIZE = 8;

struct Moves {
    int x;
    int y;
};

struct Position {
    string field[SIZE][SIZE]; 
};

vector<string> taken_white_pieces;
vector<string> taken_black_pieces;


vector<Moves> highlighted_moves = {};
string selected_piece = "none";
string turn = "white";

void initField(Position &p) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            p.field[i][j] = ".";
}

void placeStartingPieces(Position &p, const vector<string>& white, const vector<string>& black) {
    int index = 0;
    for (int j = 0; j < SIZE; ++j)
        p.field[1][j] = black[index++];
    for (int j = 0; j < SIZE; ++j)
        p.field[0][j] = black[index++];
    
    index = 0;
    for (int j = 0; j < SIZE; ++j)
        p.field[6][j] = white[index++];
    for (int j = 0; j < SIZE; ++j)
        p.field[7][j] = white[index++];
}


vector<Moves> get_valid_moves(int row, int col, const Position &p) {
    vector<Moves> moves;
    
    if (p.field[row][col] == "♟") { // white pawn
        if (row > 0 && p.field[row - 1][col] == ".") {
            moves.push_back({row - 1, col});
        }
        if (row == 6 && p.field[row - 2][col] == ".") {
            moves.push_back({row - 2, col});
        }

        string enemy_pieces = "♙♖♘♗♕♔";
        if (row > 0 && col > 0 && enemy_pieces.find(p.field[row - 1][col - 1]) != string::npos) {
            moves.push_back({row - 1, col - 1});
        }
        if (row > 0 && col < 7 && enemy_pieces.find(p.field[row - 1][col + 1]) != string::npos) {
            moves.push_back({row - 1, col + 1});
        }
        return moves;
    }

    else if (p.field[row][col] == "♙") { // black pawn
        if (row < 7 && p.field[row + 1][col] == ".") {
            moves.push_back({row + 1, col});
        }
        if (row == 1 && p.field[row + 2][col] == ".") {
            moves.push_back({row + 2, col});
        }

        string enemy_pieces = "♟♜♞♝♛♚";
        if (row < 7 && col > 0 && enemy_pieces.find(p.field[row + 1][col - 1]) != string::npos) {
            moves.push_back({row + 1, col - 1});
        }
        if (row < 7 && col < 7 && enemy_pieces.find(p.field[row + 1][col + 1]) != string::npos) {
            moves.push_back({row + 1, col + 1});
        }
        return moves;
    }

    string own_pieces = (turn == "white") ? "♟♜♞♝♛♚" : "♙♖♘♗♕♔" ;

    auto is_own_piece = [&](const string& target) {
        return own_pieces.find(target) != string::npos;
    };

    if (p.field[row][col] == "♖" || p.field[row][col] == "♜") { // The Rook
        vector<Moves> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto dir : directions) {
            int r = row + dir.x;
            int c = col + dir.y;
            while (r >= 0 && r < SIZE && c >= 0 && c < SIZE) {
                string target = p.field[r][c];
                if (target == ".") {
                    moves.push_back({r, c});
                } else if (!is_own_piece(target)) {
                    moves.push_back({r, c});
                    break;
                } else {
                    break;
                }
                r += dir.x;
                c += dir.y;
            }
        }
    }

    else if (p.field[row][col] == "♘" || p.field[row][col] == "♞") { //The Knight
        vector<Moves> knight_moves = {{-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}};
        for (auto move : knight_moves) {
            int r = row + move.x;
            int c = col + move.y;
            if (r >= 0 && r < SIZE && c >= 0 && c < SIZE) {
                string target = p.field[r][c];
                if (target == "." || !is_own_piece(target)) {
                    moves.push_back({r, c});
                }
            }
        }
    }

    else if (p.field[row][col] == "♗" || p.field[row][col] == "♝") { //The Bishop
        vector<Moves> directions = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
        for (auto dir : directions) {
            int r = row + dir.x;
            int c = col + dir.y;
            while (r >= 0 && r < SIZE && c >= 0 && c < SIZE) {
                string target = p.field[r][c];
                if (target == ".") {
                    moves.push_back({r, c});
                } else if (!is_own_piece(target)) {
                    moves.push_back({r, c});
                    break;
                } else {
                    break;
                }
                r += dir.x;
                c += dir.y;
            }
        }
    }

    else if (p.field[row][col] == "♛" || p.field[row][col] == "♕") { //The Queen
        vector<Moves> directions = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto dir : directions) {
            int r = row + dir.x;
            int c = col + dir.y;
            while (r >= 0 && r < SIZE && c >= 0 && c < SIZE) {
                string target = p.field[r][c];
                if (target == ".") {
                    moves.push_back({r, c});
                } else if (!is_own_piece(target)) {
                    moves.push_back({r, c});
                    break;
                } else {
                    break;
                }
                r += dir.x;
                c += dir.y;
            }
        }
    }
    else if (p.field[row][col] == "♔" || p.field[row][col] == "♚") { // The King
    vector<Moves> directions = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto dir : directions) {
            int r = row + dir.x;
            int c = col + dir.y;
            if (r >= 0 && r < SIZE && c >= 0 && c < SIZE) {
                string target = p.field[r][c];
                if (target == "." || !is_own_piece(target)) {
                    moves.push_back({r, c});
                }
            }
        }
    }


    return moves;
}


void printDeckWithHighligtedMoves(const Position& p, vector<Moves>& highlighted_moves) {
    cout << "  ";
    for (int i = 0; i < SIZE; i++) cout<< i << " ";
    cout<<endl;
    
    for (int i = 0; i < SIZE; i++) {
        cout << 8 - i << " ";
        for (int j = 0; j < SIZE; j++) {
            bool isHighlighted = false;
            for (const auto& m : highlighted_moves) {
                if (m.x == i && m.y == j ) {
                    isHighlighted = true;
                    break;
                }
            }
            if (isHighlighted) {
                cout << "* ";
            } else {
                cout << p.field[i][j] << " ";
            }
        }
        cout << "\n";
    }
    cout << "  a b c d e f g h\n";
}

void printTakenPieces() {
    cout << "\nTaken Pieces:\n";
    cout << "White taken: ";
    if (taken_white_pieces.empty()) cout << "None";
    else {
        for (auto &t : taken_white_pieces) cout << t << " ";
    }
    cout << "\nBlack taken: ";
    if (taken_black_pieces.empty()) cout << "None";
    else {
        for (auto &t : taken_black_pieces) cout << t << " ";
    }
    cout << "\n";
}


void MovePiece(Position& p, const vector<Moves> highlighted_moves, int xx, int yy, int r, int c) {
    bool valid = false;
    
    for (const auto& m : highlighted_moves) {
        if (m.x == xx && m.y == yy) {
            valid = true;
            break;
        }
    }
    

    
    if (valid) {
        if (p.field[xx][yy] != ".") {
            string captured = p.field[xx][yy];
            if (turn == "white") {
                taken_white_pieces.push_back(captured);
            } else {
                taken_black_pieces.push_back(captured);
            }
        }
        
        p.field[xx][yy] = p.field[r][c];
        p.field[r][c] = ".";
    } else {
        cout << "Invalid move!" << endl;
    }

    
    cout << "  ";
    for (int i = 0; i < SIZE; i++) cout << i << " ";
    cout << "\n";

    for (int i = 0; i < SIZE; i++) {
        cout << 8 - i << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << p.field[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "  a b c d e f g h\n";
    printTakenPieces();

}


int main() {
    vector<string> whitepieces{
        "♙","♙","♙","♙","♙","♙","♙","♙",
        "♖","♘","♗","♕","♔","♗","♘","♖"
    };
    vector<string> blackpieces{
        "♟","♟","♟","♟","♟","♟","♟","♟",
        "♜","♞","♝","♛","♚","♝","♞","♜"
    };

    Position p;
    initField(p);
    placeStartingPieces(p, blackpieces, whitepieces);
    cout << "  ";
    for (int i = 0; i < SIZE; i++) cout << i << " ";
    cout << "\n";

    for (int i = 0; i < SIZE; i++) {
        cout << 8 - i << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << p.field[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "  a b c d e f g h\n";
    
    while (true) {
        cout << "\nIt's " << turn << "'s move.\n";
        
        int row, col;
        cout << "Choose a piece to move (row col): ";
        cin >> row >> col;

        vector<Moves> moves = get_valid_moves(row, col, p);
        
        if (moves.empty()) {
            cout << "No valid moves for this piece or not your piece. Try again.\n";
            continue;
        }

        printDeckWithHighligtedMoves(p, moves);
        cout << "Valid moves for " << p.field[row][col] << " at [" << row << "," << col << "]:\n";
        for (auto m : moves) {
            cout << "[" << m.x << "," << m.y << "]\n";
        }

        int xx, yy;
        cout << "Now choose where to move (row col): ";
        cin >> xx >> yy;

        MovePiece(p, moves, xx, yy, row, col);

        if (turn == "white") {
            turn = "black";
        } else {
            turn = "white";
        }
        
        for (auto m : taken_white_pieces) {
            if (m == "♔") {
                cout<<"Congratulations!!!! White WON!"<<endl;
                return 0;
            }
        }
        for (auto m : taken_black_pieces) {
            if (m == "♚") {
                cout<<"Congratulations!!!! White WON!"<<endl;
                return 0;
            }
        }
    }

    return 0;
}
