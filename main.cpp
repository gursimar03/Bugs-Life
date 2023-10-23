#include <iostream>

#include <string>

#include "Board.h"

using namespace std;

// text color codes
const string COLOR_RESET = "\033[0m";
const string COLOR_RED = "\033[31m";
const string COLOR_GREEN = "\033[32m";
const string COLOR_YELLOW = "\033[33m";
const string COLOR_BLUE = "\033[34m";
const string COLOR_CYAN = "\033[36m";
const string COLOR_MAGENTA = "\033[35m";

// only One SuperBug can be created
bool superBugCreated = false;

// display the menu options
void displayMenu() {
    cout << COLOR_MAGENTA << "Welcome to Bug's Life" << endl;
    cout << COLOR_CYAN << "1. Add bugs from file" << endl;
    cout << "2. Display bugs" << endl;
    cout << "3. Find a Bug" << endl;
    cout << "4. Display Life History of all bugs" << endl;
    cout << "5. Move bugs" << endl;
    cout << "7. Start Game" << endl;
    cout << "8. Run Simulation" << endl;
    cout << "9. Create Super Bug" << endl;
    cout << "10. Create Smart Bug" << endl;
    cout << "11. Display all Cells" << endl;
    cout << "0. Exit" << COLOR_RESET << endl;
    cout << COLOR_YELLOW <<">>>>>>Enter your choice: " << COLOR_RESET;
}

// run the simulation until one bug is left
void simulateBoard(Board* board){
    // tap the board every second and display the board
    // if a bug dies, display the bug that died
    while (board->getBugs().size() > 1) {
        board->gameSFML(false);
    }
    //display the winner
    cout << COLOR_GREEN << "The winner is: " << board->getBugs()[0]->getType() << " " << board->getBugs()[0]->getId() << COLOR_RESET << endl;
}

int getInput(){
    int choice;
    while (true) {
        if (cin >> choice) {
            break;
        } else {
            cout << COLOR_RED << "Invalid input. Please enter a valid integer." << COLOR_RESET <<endl;
            cin.clear();
            cin.ignore(11, '\n');
        }
    }
    return choice;
}

int main(){
    Board board;

//    board.testWindow();
    cout << "\033[2J\033[1;1H";
    do{
        //clear the screen

        displayMenu();
        int choice = getInput();
        switch(choice){
            case 1:
                board.addBugsFromFile("bugs.txt");
                break;
            case 2:
                board.displayBugs();
                break;
            case 3:
                cout << COLOR_YELLOW << ">>>>>>Enter bug id: " << COLOR_RESET;
                board.searchBug(getInput());
                break;
            case 4:
                board.printBugPaths();
                break;
            case 5:
                board.tap();
                break;
            case 6:
                int id;
                cout << ">>>>>>Enter bug id: ";
                cin >> id;
                board.searchBug(id);
                break;
            case 7:
                if(board.getBugs().size() == 0){
                    cout << COLOR_RED << "No bugs on board. Please add bugs from file." << COLOR_RESET << endl;
                    break;
                }

                if(board.superBugPresent()){
                    cout << COLOR_RED << "Use Arrow keys to control the bug" << COLOR_RESET << endl;

                }else{
                    cout << COLOR_RED << "Use M to tap the board" << COLOR_RESET << endl;
                }
                board.gameSFML(true);
                break;
            case 8:
                if(board.getBugs().size() == 0){
                    cout << COLOR_RED << "No bugs on board. Please add bugs from file." << COLOR_RESET << endl;
                    break;
                }
                simulateBoard(&board);
                break;
            case 9:
                if (superBugCreated) {
                    cout << COLOR_RED << "Super Bug already created" << COLOR_RESET << endl;
                    break;
                }
                cout << COLOR_YELLOW << ">>>>>>Enter Bug ID : " << COLOR_RESET << endl;
                board.createSuperBug(getInput());
                cout << COLOR_BLUE << "Super Bug created" << COLOR_RESET << endl;
                superBugCreated = true;
                break;
            case 10:
                cout << COLOR_YELLOW << ">>>>>>Enter Bug ID : " << COLOR_RESET << endl;
                board.createSmartBug(getInput());
                cout << COLOR_BLUE << "Smart Bug created" << COLOR_RESET << endl;
                break;
            case 11:
                board.displayAllCells();
                break;
            case 0:

                cout << COLOR_BLUE << "Goodbye!" << COLOR_RESET << endl;

                if (board.getBugs().size() > 0) {
                    string filename = board.writeBugsLifeHistoryToFile();
                    cout << COLOR_BLUE << "Life history of all bugs written to " << filename << COLOR_RESET << endl;
                }
                else{
                    cout << COLOR_BLUE << "No bugs on board. No file written." << COLOR_RESET << endl;
                }

                return 0;

        }
    } while (true);

}
