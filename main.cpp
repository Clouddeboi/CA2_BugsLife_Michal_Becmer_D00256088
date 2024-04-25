#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <utility>

#include "Bug.h"
#include "Direction.h"
#include "Board.h"
#include "Crawler.h"
#include "Hopper.h"

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

int main() {
    while(true)
    {
        vector<Bug*> vect; // Vector to hold all bugs
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
        cin >> userChoice; // Get user's choice

        //adds bug to the board
        for(const auto& bug: vect)//loops through the vector of bugs
        {
            bugBoard.addBugToBoard(*bug);//adds to the board
        }

        // Based on user's choice, perform appropriate action
        switch (userChoice) {
            case 1:
                cout << "Bug Board Initialized!\n" << endl;
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
                cout << "----Crawlers----\n" << endl;
                for(Bug* bug : vect)
                {
                    if(bug->getType()== 'C')//for moving crawlers only
                    {
                        bug->move();
                    }
                }
                cout << "----Hoppers----\n" << endl;
                for(Bug* bug : vect)
                {
                    if(bug ->getType() == 'H')
                    {
                        bug->move();
                    }
                }
                //bugBoard.displayBoard();

                break;
            case 5:
                // Display Life History of all bugs
                break;
            case 6:
                // Display all Cells
                bugBoard.displayAllCells(vect);
                break;
            case 7:
                // PLAY GAME
                break;
            case 8:
                // Exit
                return 0;
            default:
                cerr << "Invalid Option!" << endl;
                break;
        }
    }
    return 0;
}
