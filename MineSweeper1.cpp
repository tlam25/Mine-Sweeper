#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

int m, n, K;

void get_input ();
void init_minefield (int minefield[][10]);
void place_mines (int minefield[][10]);
int count_surroungding_mines (int minefield[][10], int x, int y);
void play_game (int minefield[][10]);

int main () {
    get_input();
    int minefield[10][10];
    play_game(minefield);

    return 0;
}

void get_input () {
    do {
        cout << "Enter the size of the minefield (m, n):\n";
        cin >> m >> n;
    } while ((m >= 10 || m <= 0) && (n >= 10 || n <= 0));

    do {
        cout << "Enter the number of mines (K): \n";
        cin >> K;
    } while (K >= 10 || K <= 0);
}

void init_minefield (int minefield[][10]) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            minefield[i][j] = 0;
        }
    }
}

void place_mines (int minefield[][10]) {
    int placed_mines = 0;
    while (placed_mines < K) {
        // randomly generate coordinates of mines
        int x = rand() % m;
        int y = rand() % n;

        // if already mine, try again
        if (minefield[x][y] == -1) {
            continue;
        }

        // place a mine
        minefield[x][y] = -1;

        placed_mines++;
    }
}

int count_surroungding_mines (int minefield[][10], int x, int y) {
    int surrounding_mines = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if ((i >= 0 && i < m) && (j >= 0 && j < n)) {
                // count mines
                if (minefield[i][j] == -1) {
                    surrounding_mines++;
                }
            }
        }
    }
    return surrounding_mines;
}

void play_game (int minefield[][10]) {
    init_minefield(minefield);
    place_mines(minefield);

    bool game_over = false;
    while (!game_over) {
        int x, y;
        do {
            cout << "Please enter your present place (x, y):\n";
            cin >> x >> y;
        } while (x < 0 || x >= m || y < 0 || y >= n);

        // check mines
        if (minefield[x][y] == -1) {
            cout << "YOU'RE DEAD!" << endl;
            cout << "The final board is:\n";
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (minefield[i][j] == -1) {
                        cout << " X ";
                    } 
                    else {
                        cout << setw(2) << minefield[i][j] << " ";
                    }
                }
                cout << endl;
            }
            game_over = true;
        } 
        else {
            // if not, calculate the total mines in the 8 surrounding cells
            int surrounding_mines = count_surroungding_mines (minefield,x,y);

            // update
            if (surrounding_mines == 0)
                minefield[x][y] = 10; // the players will know where they went through by this '10' even if no mines around
            else
                minefield[x][y] = surrounding_mines;

            // print updated minefield to the screen
            cout << "The present board is:\n";
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (minefield[i][j] == -1) {
                        cout << " 0 "; // for not revealing the mines' places when the game is not yet over
                    } 
                    else {
                        cout << setw(2) << minefield[i][j] << " ";
                    }
                }
                cout << endl;
            }

            // check if the players won
            bool game_won = true;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    // if there is a cell that hasn't been tested and doesn't contain a mine, the game is not won yet
                    if (minefield[i][j] >= 0 && minefield[i][j] < 9) {
                        game_won = false;
                    }
                }
            }
            if (game_won) {
                cout << "YOU WIN!" << endl;
                game_over = true;
            }
        }
    }
}