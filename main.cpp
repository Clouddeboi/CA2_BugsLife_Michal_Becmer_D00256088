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
        printf("Type: %c\nID: %d\nPosition: (%d, %d)\nDirection: %s\nSize: %d\nAlive: %d\nPath: ",
               type, id, position.first, position.second, directionString(static_cast<int>(direction)).c_str(), size, alive);
        for (const auto& p : path) {
            printf("(%d, %d) ", p.first, p.second);
        }
        printf("\n\n");
    }
};


int main() {
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
        printf("Type: %c, ID: %d, X: %d, Y: %d, Direction Int: %d, Size: %d\n", type, id, x, y, directionInt, size);

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
    }

    // Close the file
    file.close();

    return 0;
}
