#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <thread>
#include <SFML/Graphics.hpp>

#include "Bug.h"
#include "Direction.h"
#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"
#include "BattleAnt.h"

using namespace std;

//function for converting int to direction
int directionToInt(Direction direction) {
    switch(direction) {
        case Direction::North:
            return 1;
        case Direction::East:
            return 2;
        case Direction::South:
            return 3;
        case Direction::West:
            return 4;
        default:
            return 0; // Handle unknown direction
    }
}
// Function to convert direction integer to string
string directionString(int direction) {
    switch(direction) {
        case 1:
            return "North";
        case 2:
            return "East";
        case 3:
            return "South";
        case 4:
            return "West";
        default:
            return "Unknown";//return unknown if direction doesn't equal the ones above
    }
}

void headings(){
    //Headings
    printf("%-5s %-6s %s %12s %10s %7s\n",
           "Type", "ID", "Position", "Direction", "Size", "Alive");
}

// Function to display Bug information
void display(const Bug& bug) {
    // Print bug information
    printf("%-5c %-6d %d,%-9d %-16s %-5d %-5s ",
           bug.getType(), bug.getId(), bug.getPosition().first, bug.getPosition().second,
           directionString(static_cast<int>(bug.getDirection())).c_str(), bug.getSize(), bug.isAlive() ? "true" : "false");
    printf("\n");
}

void findByID(const vector<Bug*>& bugs) {
    int searchId;
    cout << "Enter the ID of the bug you wish to find: ";
    cin >> searchId;

    bool found = false;
    for (const Bug* bug : bugs)
    {
        if (bug->getId() == searchId)
        {
            cout << "\nBug with ID " << searchId << " found!\n" << endl;
            headings();
            display(*bug);
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Bug with ID " << searchId << " not found." << endl;
    }
}

void displayLifeHistory(const vector<Bug*>& vect) {
    //iterating through the bug vector (going through each bug)
    for (const auto& bug : vect)
    {
        cout << "ID: " << bug->getId() << " :Path: ";

        if(bug->isAlive())
        {
            //Get the bug's path history
            const auto& path = bug->getPath();

            //Iterate through aquired path history
            auto iterate = path.begin();

            if (iterate != path.end())
            {
                //Display the first position
                cout << "(" << iterate->first << "," << iterate->second << ")";
                ++iterate;
            }

            //Display next positions
            for (; iterate != path.end(); ++iterate)
            {
                cout << " -> (" << iterate->first << "," << iterate->second << ")";
            }
        }
        else
        {
            cout << "Dead";
        }

        cout << endl;//skip line for next bug
    }
}

void writeBugHistoryToFile(const vector<Bug*> vect, const string& filename){

    //opening the file to write to
    ofstream outputFile(filename);

    //checking if its successfully open
    if(!outputFile.is_open())
    {
        cout<< "Couldn't open file!" << filename << endl;
        return;
    }

    //Iterate through bug vector
    for(const auto& bug : vect)
    {
        //write the bug's ID to the file
        outputFile << "ID: " << bug->getId() << " Path: ";

        //checking if the bug is alive
        if(bug->isAlive())
        {
            //bugs life history
            const auto& path = bug->getPath();

            //iterates through bugs path history
            for(auto iterate = path.begin(); iterate != path.end(); ++iterate)
            {
                //writing position to file
                outputFile << "(" << iterate->first << "," << iterate->second << ")";
                if(next(iterate) != path.end())
                {
                    outputFile << " ->";
                }
                //check if the bug died at that specific position
                if (!bug->isAlive()) {
                    break; //Stop writing the path history if the bug is dead
                }
            }
        }
        else
        {
            outputFile << "Dead";
        }

        //moves to next line to get next bug
        outputFile << endl;
    }
}

void runWindow(Board& board, vector<Bug*> vect) {

    //render window 480 x 480
    sf::RenderWindow window(sf::VideoMode(480, 480), "----BugsLife----");

        while (window.isOpen())
        {
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                //Tap Board feature with fighting
                //Check for keyboard events
                if (event.type == sf::Event::KeyPressed)
                {
                    //Check if spacebar is clicked
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        if(!board.isGameOver(vect))
                        {
                            // Move all bugs
                            board.tapBoard(vect);
                            board.fight(vect);
                        }
                        else if (board.isGameOver(vect))
                        {
                            cout << "GAME OVER!" << endl;
                            writeBugHistoryToFile(vect, "bugs_life_history_date_time.out");
                            //window.close();
                        }
                    }
                }
            }
            window.clear();
            board.draw(window, vect);
            window.display();
        }
}

int main() {
        vector<Bug*> vect; //Vector to hold all bugs
        Board bugBoard; //BugBoard obj

        ifstream file("Bugs.txt");//Open file for reading bugs

        if (!file.is_open())
        {
            //Check if file can be opened
            cout << "Cannot Open File!" << endl;
            return 1;
        }

        string line; //for storing each line read from file
        while (getline(file, line))
        {
            stringstream ss(line);
            vector<string> tokens;//vector for storing tokens
            string token;
            //get tokens using delimiter ;
            while (getline(ss, token, ';'))
            {
                //stores tokens in token vector
                tokens.push_back(token);
            }

            try {
                //Extracting the bug information from the tokenized line
                char type = tokens[0][0];
                int id = stoi(tokens[1]);
                int x = stoi(tokens[2]);
                int y = stoi(tokens[3]);
                int direction = stoi(tokens[4]);
                int size = stoi(tokens[5]);

                //line for testing
                //cout << "Creating bug from line: " << line << endl;

                Bug* bug = nullptr;//Initialize a pointer to Bug object to nullptr
                //if the bugs type is Crawler(C)
                if (type == 'C')
                {
                    bug = new Crawler(type, id, x, y, direction, size);
                    //cout << "Created Crawler with ID " << id << " at position (" << x << ", " << y << ") facing " << directionString(direction) << endl;
                }
                    //if the bugs type is Hopper(H)
                else if (type == 'H')
                {
                    int hopLength = stoi(tokens[6]);
                    bug = new Hopper(type, id, x, y, direction, size, hopLength);
                }
                else if(type == 'B')
                {
                    bug = new BattleAnt(type, id, x, y, direction, size);
                }

                //Check if the bug pointer is not null
                if (bug) {
                    vect.push_back(bug);//Add the bug pointer to vector
                    bugBoard.addBugToBoard(*bug);//Add the bug object to board
                }
            }
            catch (const invalid_argument& e)
            {
                cerr << "Invalid input: " << e.what() << endl;
            }

        }
        // Close the file
        file.close();

        int userChoice; // Variable to store user's choice
        bool run = true;
        bool isBoardInitialized = false;//checks if the board is initialized before allowing users to continue using features

    while(run)
    {
        // Display menu
        cout << "----Menu----" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Initialize Bug Board" << endl;
        cout << "2. Display All Bugs" << endl;
        cout << "3. Find Bug By ID" << endl;
        cout << "4. SHAKE BOARD!!!" << endl;
        cout << "5. Display Life History of all bugs" << endl;
        cout << "6. Display all Cells" << endl;
        cout << "7. PLAY GAME" << endl;
        cout << "8. Exit" << endl;
        cout << "9. Run SFML" << endl;
        cin >> userChoice; // Get user's choice

        //adds bug to the board
        for(const auto& bug: vect)//loops through the vector of bugs
        {
            bugBoard.addBugToBoard(*bug);//adds to the board
        }

        if(!isBoardInitialized && userChoice != 1)
        {
            cout << "Please initialize the board first!" << endl;
            continue;
        }
        // Based on user's choice, perform appropriate action
        switch (userChoice) {
            case 1:
                cout << "Bug Board Initialized!\n" << endl;
                isBoardInitialized = true;
                bugBoard.displayBoard();
                break;
            case 2:
                //headers
                headings();
                // Display All Bugs
                for (Bug* bug : vect) {
                    display(*bug);
                }
                break;
            case 3:
                //Find Bug By ID
                findByID(vect);
                break;
            case 4:
                // SHAKE BOARD!!!
                bugBoard.tapBoard(vect);
                bugBoard.fight(vect);
                //bugBoard.displayBoard();

                break;
            case 5:
                // Display Life History of all bugs
                displayLifeHistory(vect);
                break;
            case 6:
                // Display all Cells
                bugBoard.displayAllCells(vect);
                break;
            case 7:
                // PLAY GAME
                cout << "Starting Game...." << endl;
                cout << "START!" << endl;

                //if the game isnt over
                while (!bugBoard.isGameOver(vect))
                {
                    //tap the board and check if they can fight
                    bugBoard.tapBoard(vect);
                    bugBoard.fight(vect);

                    //From stack overflow: https://stackoverflow.com/questions/10807681/loop-every-10-second
                    this_thread::sleep_for(chrono::seconds(1));//allows the loop to run once per second
                }
                //if the game is over
                if(bugBoard.isGameOver(vect))
                {
                    //print out msg and write to file
                    cout<< "GAME OVER!!!!" << endl;
                    writeBugHistoryToFile(vect, "bugs_life_history_date_time.out");
                }
                break;
            case 8:
                // Exit
                writeBugHistoryToFile(vect, "bugs_life_history_date_time.out");
                run = false;
                break;
            case 9:
                runWindow(bugBoard, vect);
                break;
            default:
                cerr << "Invalid Option!" << endl;
                break;
        }
    }
    return 0;
}