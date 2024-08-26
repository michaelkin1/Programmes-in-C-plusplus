#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

const int rows = 3;
const int cols = 3;
const char symbols[] = {'A', 'O', 'X'};
const int symbol_count = sizeof(symbols) / sizeof(symbols[0]);

// Function to generate symbols
void generate_symbols(char board[rows][cols]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            board[i][j] = symbols[rand() % symbol_count];
        }
    }
}

// Function to print the board
void print_board(const char board[rows][cols]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to count the number of winning lines
int count_winning_lines(const char board[rows][cols]) {
    int count = 0;

    // Check horizontally
    for (int i = 0; i < rows; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            ++count;
        }
    }

    // Check vertically
    for (int j = 0; j < cols; ++j) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            ++count;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        ++count;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        ++count;
    }

    return count;
}

// Function to calculate winnings based on the bet and the number of winning lines
int calculate_winnings(int bet, int winning_lines) {
    switch (winning_lines) {
        case 1: return 2 * bet;
        case 2: return 3 * bet;
        case 3: return 4 * bet;
        case 4: return 5 * bet;
        case 5: return 7 * bet;
        case 8: return 10 * bet;
        default: return 0;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Random number generator
    int balance = 0;
    int bet = 0;
    char choice;

    // Rules and game instructions
    cout << "Hi and welcome to a game of slot machine! \n\n"
         << "The game works as follows: \n"
         << "1. Choose an amount of deposit. \n"
         << "2. Choose an amount to bet. \n"
         << "Symbols (A, O, X) will be randomly generated in a 3x3 grid. \n"
         << "1 winning line pays 2 times the bet. \n"
         << "2 winning lines pay 3 times the bet. \n"
         << "3 winning lines pay 4 times the bet. \n"
         << "4 winning lines pay 5 times the bet. \n"
         << "5 winning lines pay 7 times the bet. \n"
         << "Full grid (8 winning lines) pays 10 times the bet. \n"
         << "Play as many times as you want or until your money runs out. \n"
         << "\n\n"
         << "OKAY LET'S PLAY!"
         << "\n\n"
         << endl;

    // Initial deposit
    cout << "How much money would you like to deposit?: ";
    while (!(cin >> balance) || balance <= 0) {
        cout << "Invalid input, please enter a positive number: ";
        cin.clear(); // Allow new input after error
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear previous input
    }

    do {
        // Check if the user has money left
        if (balance <= 0) {
            cout << "You have run out of money!" << endl;
            break;
        }

        // Input for betting amount
        cout << "How much money would you like to bet?: ";
        while (!(cin >> bet) || bet <= 0 || bet > balance) {
            cout << "Invalid bet, please enter a positive number not exceeding your balance: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Generate and display the game board
        char board[rows][cols];
        generate_symbols(board);
        cout << "Randomized symbols:" << endl;
        print_board(board);

        // Calculate winnings and update balance
        int winning_lines = count_winning_lines(board);
        int winnings = calculate_winnings(bet, winning_lines);

        cout << "Number of winning rows: " << winning_lines << endl;
        if (winnings > 0) {
            cout << "Congratulations! You won " << winnings << " units!" << endl;
            balance += winnings - bet;
        } else {
            cout << "Sorry, no win :(" << endl;
            balance -= bet;
        }

        // Show current balance
        cout << "Your current balance is " << balance << " units." << endl;

        do {
            cout << "Would you like to play again? (y/n): ";
            cin >> choice;
            if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
                cout << "Invalid input, please enter 'y' or 'n': ";
            }
        } while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

    } while (choice == 'y' || choice == 'Y');

    cout << "Thanks for playing, your final balance is " << balance << " units." << endl;

    return 0;
}
