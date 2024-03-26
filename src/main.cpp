#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <utility>

using namespace std;

// Enum for the directions
enum class Direction { North = 1, East = 2, South = 3, West = 4 };

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
            return "Unknown";
    }
}
// Bug class
class Bug {
private:
    char type; // Type of bug
    int id; // Identification number
    pair<int,int> position; // Position coordinates
    Direction direction; // Direction the bug is facing
    int size; // Size of the bug
    bool alive; // Flag indicating if the bug is alive
    list<pair<int,int>> path; // Path taken by the bug

public:
    // Constructor to initialize variables
    Bug(char _type, int _id, pair<int,int> _position, Direction _direction, int _size, bool _alive, list<pair<int,int>> _path) :
            type(_type), id(_id), position(_position), direction(_direction), size(_size), alive(_alive), path(_path) {}

    // Function to display Bug information
    void display() {
        // Print bug information
        printf("%-5c %-6d %d,%-9d %-16s %-5d %-5s ",
               type, id, position.first, position.second, directionString(static_cast<int>(direction)).c_str(), size, alive ? "true" : "false");

        // Print path taken by the bug
        for (const auto& p : path)
        {
            printf("(%d,%d) ", p.first, p.second);
        }
        printf("\n");
    }
};

int main() {
    vector<Bug> bugs; // Vector to hold all bugs

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
    { // Check if file is successfully opened
        cout << "Cannot Open File!" << endl;
        return 1;
    }

    string line; // Variable to store each line read from file
    while (getline(file, line)) { // Read each line from file
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

    // Based on user's choice, perform appropriate action
    switch (userChoice) {
        case 1:
            // Initialize Bug Board
            break;
        case 2:
            //Headings
            printf("%-5s %-6s %s %12s %10s %7s\n",
                   "Type", "ID", "Position", "Direction", "Size", "Alive");
            // Display All Bugs
            for (Bug bug : bugs) {
                bug.display();
            }
            break;
        case 3:
            // Find Bug By ID
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
