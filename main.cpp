#include <iostream>
#include <unordered_map>
#include <unordered_set>

#define ROWS 7
#define COLS 13

bool check(std::string board[], char player) {
    for(int row = 1; row < ROWS; row += 2) {
        int cnt = 0;
        for(int col = 2; col < COLS; col += 4) {
            if(board[row][col] == player) {
                cnt++;
            }
        }

        if(cnt == 3) return true;
    }

    for(int col = 2; col < COLS; col += 4) {
        int cnt = 0;
        for(int row = 1; row < ROWS; row += 2) {
            if(board[row][col] == player) {
                cnt++;
            }
        }

        if(cnt == 3) {
            return true;
        }
    }

    if((board[1][2] == board[3][6] && board[3][6] == board[5][10] && board[1][2] == player) ||
       (board[3][6] == board[1][10] && board[5][2] == board[3][6] && board[3][6] == player)) {
        return true;
    }

    return false;
}

void clear_screen() {
    std::cout << "\033[2J\033[H";
}

void print_board(std::string board[]) {
    for(int i = 0; i < ROWS; i++) {
        std::cout << board[i] << '\n';
    }
}

void render_board(std::string board[]) {
    clear_screen();
    std::cout << "+===========+\n";
    print_board(board);
    std::cout << "+===========+\n";
}

void print_coords_layout() {
    std::string cords[] = {
        "=== coords ===",
        "    |    |    ",
        " a1 | a2 | a3 ",
        "----|----|----",
        " b1 | b2 | b3 ",
        "----|----|----",
        " c1 | c2 | c3 ",
        "    |    |    ",
        "=============="
    };

    for(int i = 0; i < 9; i++) {
        std::cout << cords[i] << '\n';
    }
}


int main() {
    std::string board[] = {
        "    |   |   ",
        "    |   |   ",
        " ---|---|---",
        "    |   |   ",
        " ---|---|---",
        "    |   |   ",
        "    |   |   ",
    };

    std::unordered_map<std::string, std::pair<int, int>> mp;
    std::unordered_set<std::string> st;
    mp["a1"] = {1, 2};
    mp["a2"] = {1, 6};
    mp["a3"] = {1, 10};
    mp["b1"] = {3, 2};
    mp["b2"] = {3, 6};
    mp["b3"] = {3, 10};
    mp["c1"] = {5, 2};
    mp["c2"] = {5, 6};
    mp["c3"] = {5, 10};

    auto clear_board = [&]() {
        st.clear();
        for(int row = 1; row < ROWS; row += 2) {
            for(int col = 2; col < COLS; col += 4) {
                if(board[row][col] == 'X' || board[row][col] == 'O') {
                    board[row][col] = ' ';
                }
            }
        }
    };

    clear_screen();
    std::cout << "WELCOME TO tic-tac-toe by Kezak1\n";
    print_coords_layout();
    std::cout << "to start game enter 'run':\n\n";

    while(true) {
        
        std::cout << "command: ";
        std::string input;
        std::cin >> input;

        if(input == "run") {
            clear_board();
            render_board(board);

            int i = 0;
            while(i < 9) {
                char c = ((i & 1) ? 'O' : 'X');
                std::cout << c << " to move: ";
                
                std::string move;
                std::cin >> move;

                if(move == "exit") {
                    clear_screen();
                    break;
                }

                if(!mp.count(move)) {
                    std::cout << "error: invalid coordinate" << std::endl;
                    continue;
                }

                auto [row, col] = mp[move];
                if(st.count(move)) {
                    std::cout << "error: there is a elem already in " << move << " box" << std::endl;
                    continue;
                }
                
                board[row][col] = c;
                
                render_board(board);

                if(check(board, c)) {
                    std::cout << c << " WINS\n";
                    break;
                }

                st.insert(move);
                i++;
            }

            if(i == 9) {
                std::cout << "DRAW\n";
            }

        } else if(input == "exit") {
            break;
        } else {
            std::cout << "error: invalid command" << std::endl;
        }
    }

    return 0;
}