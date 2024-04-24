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
Direction DirectionToInt(int value) {
    switch(value) {
        case 1:
            return Direction::North;
        case 2:
            return Direction::East;
        case 3:
            return Direction::South;
        case 4:
            return Direction::West;
        default:
            return Direction::North; // Default to North if unknown direction
    }
}
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


void findByID(vector<Bug*> bugs)
{
    int search;//searched id

    cout << "Enter Id of the bug you wish to find:";
    cin >> search;//gets search parameters from user

    bool found = false;//bool to check if id is found

    for(const Bug* bug : bugs)//iterates through each bug
    {
        if(bug -> getId() == search)//if the id matches the search
        {
            cout << "\nBug with ID " << search << " found!\n" << endl;
            printf("%-5s %-6s %s %12s %10s %7s\n",
                   "Type", "ID", "Position", "Direction", "Size", "Alive");
            display(*bug);//if found it displays the bug
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
    vector<Bug*> vect; // Vector to hold all bugs
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

    cout << "1"<< endl;
    ifstream file("Bugs.txt");//Open file for reading bugs

    if (!file.is_open())
    {
        //Check if file can be opened
        cout << "Cannot Open File!" << endl;
        return 1;
    }

    cout << "1";
    string line; //for storing each line read from file
    while(getline(file,line)){
        vector<string> tokens;
        stringstream s(line);
        string token;

        //storing tokens in vector using a delimiter
        while(getline(s, token, ';'))
        {
            tokens.push_back(token);
        }

        for(string s: tokens){
            cout << "\n"<<s;
        }

        //conversion with tokens
        char type = tokens[0][0];

        if(!tokens.at(0).compare("C"))
        {
            auto *crawler = new Crawler(
                    'C',
                    stoi(tokens.at(1)),//string to integer
                    stoi(tokens[2]),
                    stoi(tokens[3]), //strings to integers and creating pair
                    stoi(tokens[4]), //string to integer and then to Direction enum
                    stoi(tokens[5]) //string to integer
                    );
        }
        else if(!tokens.at(0).compare("H"))
        {
            auto poo = new Hopper(
                    'H',
                    stoi(tokens.at(1)),//string to integer
                    stoi(tokens[2]),
                    stoi(tokens[3]),//strings to integers and creating pair
                    stoi(tokens[4]), //string to integer and then to Direction enum
                    stoi(tokens[5]),//string to integer
                    stoi(tokens[6])
            );
        }
    }
    // Close the file
    file.close();

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
