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

// Protected bug class
class Bug {
protected:
    char type;
    int id;
    pair<int,int> position;
    Direction direction;
    int size;
    bool alive;
    list<pair<int,int>> path;

public:
    // Constructor to initialize variables
    Bug(char type, int id, pair<int,int> position, Direction direction, int size, bool alive, list<pair<int,int>> path) :
            type(type), id(id), position(position), direction(direction), size(size), alive(alive), path(path) {}

    // Function to display Bug information
    void display() {
        printf("%-5c %-6d %d, %-11d %-16s %-5d %-5d ",
               type, id, position.first, position.second, directionString(static_cast<int>(direction)).c_str(), size, alive);
        for (const auto& p : path) {
            printf("(%d, %d) ", p.first, p.second);
        }
        printf("\n\n");
    }
};


int main() {

    int userChoice;

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
    cin >> userChoice;

    ifstream file("Bugs.txt");

    if (!file.is_open()) {
        cout << "Cannot Open File!" << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        stringstream s(line);
        char type;
        int id, x, y, directionInt, size;
        list<pair<int, int>> path;

        s >> type >> id >> x >> y >> directionInt >> size;

        int tempX, tempY;
        while (s >> tempX >> tempY) {
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
        // Create Bug object and display information
        Bug bug(type, id, {x, y}, dir, size, true, path);
        bug.display();

        switch (userChoice) {
            case 1:
                break;
            case 2:
                bug.display();
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                cerr << "Invalid Option!" << endl;
               continue; // Skip this line
    }

       }
        // Close the file
        file.close();

        return 0;
    }
