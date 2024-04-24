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

using namespace std;
// Function to convert direction integer to string
string directionString(int directionInt) {
    switch(directionInt) {
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

void displayBoard()
{
    const vector<vector<char>>& grid = Board().getGrid();
    for(int i = 0; i < 10; ++i)//loops rows
    {
        for(int j = 0; j < 10; ++j)//loops columns
        {
            cout << grid[i][j] << "  ";//output the location of the character followed by an empty space
        }
        cout << endl;//makes rows by moving to next line after a row
    }
}

void findByID(const vector<Bug>& bugs)
{
    int search;//searched id

    cout << "Enter Id of the bug you wish to find:";
    cin >> search;//gets search parameters from user

    bool found = false;//bool to check if id is found

    for(Bug bug : bugs)//iterates through each bug
    {
        if(bug.getId() == search)//if the id matches the search
        {
            cout << "\nBug with ID " << search << " found!\n" << endl;
            printf("%-5s %-6s %s %12s %10s %7s\n",
                   "Type", "ID", "Position", "Direction", "Size", "Alive");
            display(bug);//if found it displays the bug
            found = true;//sets to true if bug is found
            break;
        }
    }
    if(!found)//if it cant find the bug gives msg
    {
        cerr << "Couldn't find bug with ID " << search << endl;
    }
}

int main() {
    vector<Bug> bugs; // Vector to hold all bugs
    Board bugBoard; //BugBoard obj

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

    ifstream file("Bugs.txt"); // Open file for reading bugs

    if (!file.is_open())
    {
        // Check if file is successfully opened
        cout << "Cannot Open File!" << endl;
        return 1;
    }

    string line; // Variable to store each line read from file
    while (getline(file, line))
    { // Read each line from file
        stringstream s(line); // Create string stream from line
        char type; // Type of bug
        int id, x, y, directionInt, size; // Bug attributes
        list<pair<int, int>> path; // Path taken by the bug

        s >> type >> id >> x >> y >> directionInt >> size; // Read bug attributes

        int tempX, tempY;
        while (s >> tempX >> tempY)
        { // Read path taken by the bug
            path.push_back({tempX, tempY});
        }

        // Convert direction integer to enum
        Direction dir;
        switch (directionInt) {
            case 1:
                dir = Direction::North;
                break;
            case 2:
                dir = Direction::East;
                break;
            case 3:
                dir = Direction::South;
                break;
            case 4:
                dir = Direction::West;
                break;
            default:
                cerr << "Invalid direction!" << endl;
                continue; // Skip this line
        }

        // Create Bug object and add it to the vector
        bugs.push_back(Bug(type, id, {x, y}, dir, size, true, path));
    }

    // Close the file
    file.close();

    //adds bug to the board
    for(const auto& bug: bugs)//loops through the vector of bugs
    {
        Board().addBugToBoard(bug);//adds to the board
    }

    // Based on user's choice, perform appropriate action
    switch (userChoice) {
        case 1:
            cout << "Bug Board Initialized!\n" << endl;
            displayBoard();
            break;
        case 2:
            //headers
            headings();
            // Display All Bugs
            for (Bug bug : bugs) {
                display(bug);
            }
            break;
        case 3:
            //Find Bug By ID
            findByID(bugs);
            break;
        case 4:
            // SHAKE BOARD!!!
            break;
        case 5:
            // Display Life History of all bugs
            break;
        case 6:
            // Display all Cells
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

    return 0;
}
