//
// Created by Gursimar Singh on 28/03/2023.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "Board.h"
#include "Crawler.h"
#include "Bug.h"
#include "Hopper.h"
#include "SuperBug.h"
#include "SmartBug.h"
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <list>
#include <thread>

Board::Board() {
    bugs = std::vector<Bug *>();
    deadBugs = std::vector<Bug *>();

}


void Board::gameSFML(bool manualPlay) {

    // creating sprite for all bugs
    sf::Texture crawlertexture, hoppertexture, superbugtexture, smartbugtexture;
    if (!(crawlertexture.loadFromFile("Crawler.png") &&
          hoppertexture.loadFromFile("Hopper.png") &&
          superbugtexture.loadFromFile("SuperBug.png") &&
          smartbugtexture.loadFromFile("SmartBug.png"))) {
        std::cerr << "Failed to load one of the bug images." << std::endl;
        return;
    }

    // Create the window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bugs Life");

// Load the font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font arial.ttf" << std::endl;
        return;
    }

// Game loop
    bool mKeyPressed = false, winnerDeclared = false, superBugControlled = false, bugSelected = false;
    sf::Sprite bugSprite;
    sf::Text bugType, bugInfo, killLogger;
    bugType.setFont(font);
    bugType.setCharacterSize(16);
    bugType.setFillColor(sf::Color::Black);
    bugInfo.setFont(font);
    bugInfo.setCharacterSize(16);
    bugInfo.setFillColor(sf::Color::White);
    killLogger.setFont(font);
    killLogger.setCharacterSize(16);
    killLogger.setFillColor(sf::Color::White);

    Bug* selectedBug = nullptr;

    while (window.isOpen()) {

        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);

        // If its manual play, check for key presses
        if (!manualPlay) {
            tap();
           sleep(1);
        } else {
            if (this->hasSuperBug) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    if (!superBugControlled) {
                        setSuperBugDirection(3);
                        tap();
                        superBugControlled = true;
                    }
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    if (!superBugControlled) {
                        setSuperBugDirection(1);
                        tap();
                        superBugControlled = true;
                    }
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    if (!superBugControlled) {
                        setSuperBugDirection(4);
                        tap();
                        superBugControlled = true;
                    }
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    if (!superBugControlled) {
                        setSuperBugDirection(2);
                        tap();
                        superBugControlled = true;
                    }
                } else {
                    superBugControlled = false;
                }
            } else {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
                    if (!mKeyPressed) {
                        // 'm' key was just pressed
                        mKeyPressed = true;
                        tap();
                    }
                } else {
                    mKeyPressed = false;
                }
            }
        }
        // Draw the grid
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                sf::RectangleShape box(sf::Vector2f(BOX_SIZE, BOX_SIZE));
                box.setPosition(i * BOX_SIZE, j * BOX_SIZE);
                box.setOutlineThickness(1.3);
                box.setOutlineColor(sf::Color(200, 200, 200)); // light gray outline color
                box.setFillColor(sf::Color(240, 240, 240)); // light gray box color
                window.draw(box);
            }
        }

        // Draw the sidebar
        // create the black bar with white border
        sf::RectangleShape bar(sf::Vector2f(SIDEBAR_WIDTH, WINDOW_HEIGHT));
        bar.setPosition(WINDOW_WIDTH - SIDEBAR_WIDTH, 0);
        bar.setFillColor(sf::Color::Black);
        bar.setOutlineThickness(2);
        bar.setOutlineColor(sf::Color::White);
        window.draw(bar);
        float yPos = BOX_PADDING;

        // Draw the bugs
        sf::Sprite bufferSprite;
        sf::Text bugInfo;
        bugInfo.setFont(font);
        bugInfo.setCharacterSize(16);
        bugInfo.setFillColor(sf::Color::White);

        //killLog
        sf::Text killLogger;
        killLogger.setFont(font);
        killLogger.setCharacterSize(16);
        killLogger.setFillColor(sf::Color::White);

        //looping through killLog vector and adding to killLog string
        std::string killLogString = "";

        if (killLog.size() > 0) {

            for (int i = killLog.size() - 1; i >= 0; i--) {
                killLogString += killLog[i] + "\n";

            }

        }

        killLogger.setString(killLogString);


        killLogger.setPosition(WINDOW_WIDTH - SIDEBAR_WIDTH + BOX_PADDING, BOX_PADDING);
        window.draw(killLogger);

        sf::RectangleShape box(sf::Vector2f(SIDEBAR_WIDTH, 200));
        box.setPosition(WINDOW_WIDTH - SIDEBAR_WIDTH + BOX_PADDING, WINDOW_HEIGHT / 2);
        box.setFillColor(sf::Color::White);
        box.setOutlineThickness(1);
        box.setOutlineColor(sf::Color::Black);
        window.draw(box);


        if (bugSelected) {
            int x = selectedBug->getPosition().first * BOX_SIZE;
            int y = selectedBug->getPosition().second * BOX_SIZE;

            bufferSprite.setPosition(x, y); // Set sprite position
            bufferSprite.setScale(0.25, 0.25); // Set sprite scale
            if (typeid(*selectedBug) == typeid(Crawler)) {
                bufferSprite.setTexture(crawlertexture);
                bugType.setString("Type: Crawler\nSize: " + std::to_string(selectedBug->getSize()) + "\nID: " +
                                  std::to_string(selectedBug->getId()));
            } else if (typeid(*selectedBug) == typeid(Hopper)) {
                bufferSprite.setTexture(hoppertexture);
                bugType.setString("Type: Hopper\nSize: " + std::to_string(selectedBug->getSize()) + "\nID: " +
                                  std::to_string(selectedBug->getId()));
            } else if (typeid(*selectedBug) == typeid(SuperBug)) {
                bufferSprite.setTexture(superbugtexture);
                bugType.setString("Type: SuperBug\nSize: " + std::to_string(selectedBug->getSize()) + "\nID: " +
                                  std::to_string(selectedBug->getId()));
            } else if (typeid(*selectedBug) == typeid(SmartBug)) {
                bufferSprite.setTexture(smartbugtexture);
                bugType.setString("Type: SmartBug\nSize: " + std::to_string(selectedBug->getSize()) + "\nID: " +
                                  std::to_string(selectedBug->getId()));
            }
            bugSprite.setTexture(*bufferSprite.getTexture());
            bugSprite.setPosition(WINDOW_WIDTH - SIDEBAR_WIDTH + BOX_PADDING + box.getSize().x / 2 -
                                  bugSprite.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 + BOX_PADDING);
            bugSprite.setScale(0.5, 0.5);
            bugType.setPosition(WINDOW_WIDTH - SIDEBAR_WIDTH + BOX_PADDING + box.getSize().x / 2 -
                                bugType.getGlobalBounds().width / 2,
                                WINDOW_HEIGHT / 2 + BOX_PADDING + bugSprite.getGlobalBounds().height + 10);

            // Draw bug sprite
            window.draw(bugSprite);

            // Draw bug info
            window.draw(bugType);

            //If mouse is clicked outside the bug info box, deselect the bug
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::FloatRect bounds = bugType.getGlobalBounds();
                bounds.width += 20;
                bounds.height += 20;
                bounds.left -= 10;
                bounds.top -= 10;
                if (!bounds.contains(mousePos.x, mousePos.y)) {
                    bugSelected = false;
                }
            }
        }else{
            //get biggest bug
            int biggestBugSize = 0;
            Bug* biggestBug = nullptr;
            for(int i = 0; i < bugs.size(); i++){
                if(bugs[i]->getSize() > biggestBugSize){
                    biggestBugSize = bugs[i]->getSize();
                    biggestBug = bugs[i];
                }
            }

            selectedBug = biggestBug;

            // Draw biggest bug sprite
            if(biggestBug != nullptr){
                int x = biggestBug->getPosition().first * BOX_SIZE;
                int y = biggestBug->getPosition().second * BOX_SIZE;

                bufferSprite.setPosition(x, y); // Set sprite position
                bufferSprite.setScale(0.25, 0.25); // Set sprite scale
                if (typeid(*biggestBug) == typeid(Crawler)) {
                    bufferSprite.setTexture(crawlertexture);
                    bugType.setString("Type: Crawler\nSize: " + std::to_string(biggestBug->getSize()) + "\nID: " +
                                      std::to_string(biggestBug->getId()));
                } else if (typeid(*biggestBug) == typeid(Hopper)) {
                    bufferSprite.setTexture(hoppertexture);
                    bugType.setString("Type: Hopper\nSize: " + std::to_string(biggestBug->getSize()) + "\nID: " +
                                      std::to_string(biggestBug->getId()));
                } else if (typeid(*biggestBug) == typeid(SuperBug)) {
                    bufferSprite.setTexture(superbugtexture);
                    bugType.setString("Type: SuperBug\nSize: " + std::to_string(biggestBug->getSize()) + "\nID: " +
                                      std::to_string(biggestBug->getId()));
                } else if (typeid(*biggestBug) == typeid(SmartBug)) {
                    bufferSprite.setTexture(smartbugtexture);
                    bugType.setString("Type: SmartBug\nSize: " + std::to_string(biggestBug->getSize()) + "\nID: " +
                                      std::to_string(biggestBug->getId()));
                }
                bugSprite.setTexture(*bufferSprite.getTexture());
                bugSprite.setPosition(WINDOW_WIDTH - SIDEBAR_WIDTH + BOX_PADDING + box.getSize().x / 2 -
                                      bugSprite.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 + BOX_PADDING);
                bugSprite.setScale(0.5, 0.5);
                bugType.setPosition(WINDOW_WIDTH - SIDEBAR_WIDTH + BOX_PADDING + box.getSize().x / 2 -
                                    bugType.getGlobalBounds().width / 2,
                                    WINDOW_HEIGHT / 2 + BOX_PADDING + bugSprite.getGlobalBounds().height + 10);
                bugSelected = true;
            }

        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            for (int i = 0; i < bugs.size(); i++) {
                int x = bugs[i]->getPosition().first * BOX_SIZE;
                int y = bugs[i]->getPosition().second * BOX_SIZE;

                bufferSprite.setPosition(x, y); // Set sprite position
                bufferSprite.setScale(0.25, 0.25); // Set sprite scale
                if (typeid(bugs[i]) == typeid(Crawler)) {
                    bufferSprite.setTexture(crawlertexture);
                    bugType.setString("Type: Crawler\nSize: " + std::to_string(bugs[i]->getSize()) + "\nID: " +
                                      std::to_string(bugs[i]->getId()));
                } else if (typeid(bugs[i]) == typeid(Hopper)) {
                    bufferSprite.setTexture(hoppertexture);
                    bugType.setString("Type: Hopper\nSize: " + std::to_string(bugs[i]->getSize()) + "\nID: " +
                                      std::to_string(bugs[i]->getId()));
                } else if (typeid(bugs[i]) == typeid(SuperBug)) {
                    bufferSprite.setTexture(superbugtexture);
                    bugType.setString("Type: SuperBug\nSize: " + std::to_string(bugs[i]->getSize()) + "\nID: " +
                                      std::to_string(bugs[i]->getId()));
                } else if (typeid(bugs[i]) == typeid(SmartBug)) {
                    bufferSprite.setTexture(smartbugtexture);
                    bugType.setString("Type: SmartBug\nSize: " + std::to_string(bugs[i]->getSize()) + "\nID: " +
                                      std::to_string(bugs[i]->getId()));
                }

                sf::FloatRect bounds = bufferSprite.getGlobalBounds();
                // Increase the size of the hit box
                bounds.width += 10;
                bounds.height += 10;
                bounds.left -= 5;
                bounds.top -= 5;
                if (bounds.contains(mousePos.x, mousePos.y)) {
                    // Show pop-up box with bug image and type
                    bugSelected = true;
                    selectedBug = bugs[i];
                    bugSprite.setTexture(*bufferSprite.getTexture());
                    bugSprite.setPosition(WINDOW_WIDTH - SIDEBAR_WIDTH + BOX_PADDING + box.getSize().x / 2 -
                                          bugSprite.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2 + BOX_PADDING);
                    bugSprite.setScale(0.5, 0.5);
                    bugType.setPosition(WINDOW_WIDTH - SIDEBAR_WIDTH + BOX_PADDING + box.getSize().x / 2 -
                                        bugType.getGlobalBounds().width / 2,
                                        WINDOW_HEIGHT / 2 + BOX_PADDING + bugSprite.getGlobalBounds().height + 10);

                    break;
                }
            }
        }

        // For showing co-ordinates of bugs and print bugs
        for (int i = 0; i < bugs.size(); i++) {
            int x = bugs[i]->getPosition().first;
            int y = bugs[i]->getPosition().second;

            bufferSprite.setPosition(x * BOX_SIZE, y * BOX_SIZE);
            bufferSprite.setScale(0.25, 0.25);
            if (bugs[i]->getType() == "Crawler") {
                bufferSprite.setTexture(crawlertexture);
            } else if (bugs[i]->getType() == "Hopper") {
                bufferSprite.setTexture(hoppertexture);
            } else if (bugs[i]->getType() == "SuperBug") {
                bufferSprite.setTexture(superbugtexture);
            } else {
                bufferSprite.setTexture(smartbugtexture);
            }
            window.draw(bufferSprite);
            // set bug info string and position it at the bottom of the black bar
            bugInfo.setString(bugs[i]->getType() + " - X: " + std::to_string(x) + ", Y: " + std::to_string(y));
            bugInfo.setPosition(WINDOW_WIDTH - SIDEBAR_WIDTH + BOX_PADDING,
                                WINDOW_HEIGHT - (yPos + bugInfo.getGlobalBounds().height));
            window.draw(bugInfo);
            yPos += bugInfo.getGlobalBounds().height + BOX_PADDING;

        }

        if (isGameOver()) {
            sf::Text gameOver;
            gameOver.setFont(font);
            gameOver.setString("Game Over! " + getWinner() + " wins!");
            gameOver.setCharacterSize(50);
            gameOver.setFillColor(sf::Color::Red);
            gameOver.setStyle(sf::Text::Bold);

            // Center the text horizontally and vertically
            sf::FloatRect gameOverBounds = gameOver.getLocalBounds();
            gameOver.setOrigin(gameOverBounds.left + gameOverBounds.width / 2.0f,
                               gameOverBounds.top + gameOverBounds.height / 2.0f);
            gameOver.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f));

            // Add a background rectangle to make the text more visible
            sf::RectangleShape background(sf::Vector2f(gameOverBounds.width + 20.0f, gameOverBounds.height + 20.0f));
            background.setFillColor(sf::Color::White);
            background.setOrigin(background.getSize() / 2.0f);
            background.setPosition(gameOver.getPosition());

            // Draw the background and text
            window.clear();
            window.draw(background);
            window.draw(gameOver);
            window.display();

            // Wait for 5 seconds before closing the window
            sf::sleep(sf::seconds(5));
            window.close();
        }


        // Update the window
        window.display();

    }
}

string Board::getWinner() {
    return bugs[0]->getType() + " " + std::to_string(bugs[0]->getId());
}

bool Board::isGameOver() {

    if (bugs.size() == 1) {
        return true;
    }
    return false;

}

Board::Board(int width, int height) {
    bugs = std::vector<Bug *>();
    // initialize gameBoard to all zeroes
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            gameBoard[i][j] = 0;
        }
    }
}


void Board::searchBug(int id) {
    bool found = false;

    // Search for the bug with the given id in the vector of bugs
    for (Bug *bug: bugs) {
        if (bug->getId() == id) {
            //all details of the bug
            std::cout << bug->getType() << " bug " << id << " found at " << bug->getPosition().first << ", " << bug->getPosition().second
                       << std::endl ;

            found = true;
            break;
        }
    }
    // If the bug was not found, display a "bug not found" message
    if (!found) {
        std::cout << "bug " << id << " not found" << std::endl;
    }
}


void Board::addBugsFromFile(std::string fileName) {
    std::ifstream file(fileName);
    std::string line;

    while (std::getline(file, line)) {
        // Parse the line and create a new bug
        parseLine(line);

        // Add the bug to the vector of bugs
    }

    cout << "Bugs added from file" << endl;

    file.close();
}

void Board::removeBug(Bug *bug) {
    for (int i = 0; i < bugs.size(); i++) {
        if (bugs[i] == bug) {
            bugs.erase(bugs.begin() + i);

            break;
        }
    }
}



//This function is called when the user "taps" the game board. It first checks if there are more than one bugs on the board.
// If there are, it loops through each bug and moves them according to their type.
// If the bug is a SmartBug, it calls its move function with a list of all the bugs on the board. If not, it just calls the regular move function.
//
//Next, it checks if any bugs are occupying the same position. If so, it determines which bug is the winner based on their size.
// If one bug is larger than the other, it kills the smaller bug and increases the size of the winner. If both bugs are the same size, it randomly selects one to be the winner.
//
//After resolving any collisions, it checks if there was a SuperBug that was killed. If so, it sets the hasSuperBug flag to false.
//
//Overall, this function handles the game logic for resolving collisions between bugs and updating their positions.
void Board::tap() {
    if (bugs.size() > 1) {
        for (Bug *&bug: bugs) {


            if (bug->getType() == "SmartBug") {
                SmartBug *smartBug = dynamic_cast<SmartBug *>(bug);
                smartBug->move(bugs);
            } else {
                bug->move();
            }

// Check for bugs on the same position
            bool collision = false;
            for (Bug *&otherBug: bugs) {
                if (bug != otherBug && bug->getPosition() == otherBug->getPosition()) {
                    collision = true;
                    if (bug->getSize() > otherBug->getSize()) {
                        // bug wins, kill otherBug
                        otherBug->setAlive(false);
                        otherBug->setKillerId(bug->getId());
                        bug->setSize(bug->getSize() + otherBug->getSize());
                        killLog.push_back(
                                bug->getType() + " " + std::to_string(bug->getId()) + " killed " + otherBug->getType() +
                                " " + std::to_string(otherBug->getId()));
                        deadBugs.push_back(otherBug);
                        removeBug(otherBug);
                        break; // exit the loop, we don't need to check other bugs anymore
                    } else if (otherBug->getSize() > bug->getSize()) {
                        // otherBug wins, kill bug
                        bug->setAlive(false);
                        bug->setKillerId(otherBug->getId());
                        otherBug->setSize(otherBug->getSize() + bug->getSize());
                        killLog.push_back(otherBug->getType() + " " + std::to_string(otherBug->getId()) + " killed " +
                                          bug->getType() + " " + std::to_string(bug->getId()));
                        deadBugs.push_back(bug);
                        removeBug(bug);
                        break; // exit the loop, we don't need to check other bugs anymore
                    } else {
                        // same size, randomly choose which bug to kill
                        int random = rand() % 2;
                        if (random == 0) {
                            otherBug->setAlive(false);
                            otherBug->setKillerId(bug->getId());
                            bug->setSize(bug->getSize() + otherBug->getSize());
                            killLog.push_back(bug->getType() + " " + std::to_string(bug->getId()) + " killed " +
                                              otherBug->getType() + " " + std::to_string(otherBug->getId()));
                            deadBugs.push_back(otherBug);
                            removeBug(otherBug);
                        } else {
                            bug->setAlive(false);
                            bug->setKillerId(otherBug->getId());
                            otherBug->setSize(otherBug->getSize() + bug->getSize());
                            killLog.push_back(
                                    otherBug->getType() + " " + std::to_string(otherBug->getId()) + " killed " +
                                    bug->getType() + " " + std::to_string(bug->getId()));
                            deadBugs.push_back(bug);
                            removeBug(bug);
                        }
                        break; // exit the loop, we don't need to check other bugs anymore
                    }
                }
            }

            if (hasSuperBug) {
                for (Bug *deadBug: deadBugs) {
                    if (deadBug->getType() == "super") {
                        this->hasSuperBug = false;
                    }
                }
            }

        }
    }

}

void Board::displayAllCells() {

    cout << "  ";
    for (int i = 0; i < 10; i++) {
        cout << i << " ";
    }
    cout << endl;

    // Print board with bugs' names and ids
    for (int i = 0; i < 10; i++) {
        cout << i << " ";
        for (int j = 0; j < 10; j++) {
            cout << "(" << i << "," << j << "): ";
            bool bugFound = false;
            for (int k = 0; k < bugs.size(); k++) {
                if (bugs[k]->getPosition().first == i && bugs[k]->getPosition().second == j) {
                    cout << bugs[k]->getType() << " " << bugs[k]->getId() << ", ";
                    bugFound = true;
                }
            }
            if (!bugFound) {
                cout << "empty";
            }
            cout << endl;
        }
    }

}

string Board::writeBugsLifeHistoryToFile() {
    // Generate file name based on current date and time
    time_t now = time(0);
    struct tm tstruct = *localtime(&now);
    char fileName[80];
    strftime(fileName, sizeof(fileName), "bugs_life_history_%Y-%m-%d_%H-%M-%S.out", &tstruct);

    // Open file for writing
    std::ofstream outFile(fileName);

    // Write each bug's life history to the file
    for (Bug* bug : bugs) {
        outFile << bug->getId() << " " << bug->getType() << " Path: ";
        std::list<std::pair<int, int>> path = bug->getPath();
        for (std::pair<int, int> position: path) {
            outFile << "(" << position.first << "," << position.second << "),";
        }
        outFile << " Winner!" << std::endl;
    }

    //write dead bugs to file
    for (Bug* bug : deadBugs) {
        outFile << bug->getId() << " " << bug->getType() << " Path: ";
        std::list<std::pair<int, int>> path = bug->getPath();
        for (std::pair<int, int> position: path) {
            outFile << "(" << position.first << "," << position.second << "),";
        }

        outFile << " Eaten by " << bug->getKillerId() << std::endl;

    }

    return fileName;
}


void Board::printBugPaths() {
    for (int i = 0; i < bugs.size(); i++) {
        Bug *bug = bugs[i];
        std::cout << bug->getId() << " " << bug->getType() << " Path: ";
        std::list<std::pair<int, int>> path = bug->getPath();
        for (std::pair<int, int> position: path) {
            std::cout << "(" << position.first << "," << position.second << "),";
        }
       cout << " Alive!" << std::endl;
    }
    // Print dead bugs
    for (Bug* bug : deadBugs) {
        std::cout << bug->getId() << " " << bug->getType() << " Path: ";
        std::list<std::pair<int, int>> path = bug->getPath();
        for (std::pair<int, int> position: path) {
            std::cout << "(" << position.first << "," << position.second << "),";
        }
        std::cout << " Eaten by " << bug->getKillerId() << std::endl;
    }
}

void Board::displayBugs() {
    for (Bug *bug: bugs) {
        cout << *bug << endl;
    }
}

void Board::parseLine(string line) {
    char type;
    int id, x, y, dir, size, hopLength = 0;

    // Use stringstream to split the line by semicolons
    stringstream ss(line);
    string field;

    // Read the first field (type)
    getline(ss, field, ';');
    type = field[0];

    // Read the second field (id)
    getline(ss, field, ';');
    id = stoi(field);

    // Read the third field (x)
    getline(ss, field, ';');
    x = stoi(field);

    // Read the fourth field (y)
    getline(ss, field, ';');
    y = stoi(field);

    // Read the fifth field (direction)
    getline(ss, field, ';');
    dir = stoi(field);

    // Read the sixth field (size)
    getline(ss, field, ';');
    size = stoi(field);

    // If type is Hopper, read the hop length field
    if (type == 'H') {
        getline(ss, field, ';');
        hopLength = stoi(field);
    }
    list<pair<int, int>> path;
    path.push_back(make_pair(x, y));
    // Create a new Bug object based on the parsed fields and add it to the vector
    if (type == 'C') {

        bugs.push_back(new Crawler(id, make_pair(x, y), dir, size, path));

    } else if (type == 'H') {

        bugs.push_back(new Hopper(id, make_pair(x, y), dir, size, hopLength, path));

    }
}

void Board::setSuperBugDirection(int direction) {

    for (Bug *bug: bugs) {
        if (bug->getType() == "SuperBug") {
            bug->setDirection(direction);
        }
    }

}

vector<Bug *> Board::getBugs() {
    return bugs;
}

void Board::createSuperBug(int id) {

    //super bug that can be controlled by user using arrow keys
    bugs.push_back(new SuperBug(id, make_pair(4, 4), 1, 7, list<pair<int, int>>()));
    this->hasSuperBug = true;

}


void Board::createSmartBug(int id) {

    bugs.push_back(new SmartBug(id, make_pair(7, 3), 1, 7, list<pair<int, int>>()));


}

bool Board::superBugPresent() {
    return this->hasSuperBug;
}
