//
// Created by Gursimar Singh on 28/03/2023.
//

#ifndef BUGSLIFE_BOARD_H
#define BUGSLIFE_BOARD_H

#include <vector>
#include "Bug.h"

#include <SFML/Graphics.hpp>
#include <list>
class Board {

    private:
            std::vector<Bug*> bugs;
            std::vector<Bug*> deadBugs;
            std::vector<string> killLog;
            int gameBoard[10][10]{};
            bool hasSuperBug = false;
            sf::RenderWindow window;

            //CONSTANTS
    const int WINDOW_WIDTH = 900;
    const int WINDOW_HEIGHT = 650;
    const float BOX_SIZE = 64;
    const int BOX_PADDING = 5;
    const int GRID_SIZE = 10;
    const int SIDEBAR_WIDTH = WINDOW_WIDTH * 0.28; // ~20% of the screen width


public:

        Board();

        //we can pass the width and height of the board as parameters
        Board(int width, int height);
        bool superBugPresent();
        //main Game loop
        void gameSFML(bool manualPlay);

        void searchBug(int id);
        void addBugsFromFile(std::string fileName);
        void parseLine(std::string line);
        string writeBugsLifeHistoryToFile();
        void printBugPaths();
        void removeBug(Bug* bug);
        void tap();
        void displayAllCells();
        vector<Bug *> getBugs();
        void createSuperBug(int id);
        void displayBugs();
        bool isGameOver();
        string getWinner();
        void setSuperBugDirection(int direction);
        void createSmartBug(int id);
};


#endif //BUGSLIFE_BOARD_H
