#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

// using namespace means we can call keywords within the
// "std" namespace without prefixing the namespace like std::
using namespace std;

// My map class
class Map {

// The private section encapsulates the variables and
// methods within the Map object.  They cannot be
// accessed outside of the Map object
private:
    static const int MAP_X = 9; // 0 - 8
    static const int MAP_Y = 9; // 0 - 8
    int mapArray[MAP_X][MAP_Y];
    string filename;
    ifstream mapFile;

    void initialiseMapArray(int val) {
        // Initialise the array to safe values
        for (int x = 0; x <= MAP_X - 1; x++) {
            for (int y = 0; y <= MAP_Y - 1; y++) {
                mapArray[x][y] = val;
            }
        }
    }

    void floodFill(int x, int y, int val) {

        cout << "Calculating flood for: " << x << "," << y << endl;

        // Down
        if (x - 1 >= 0 && mapArray[x][y] == 0) {
            int tempNumber = mapArray[x - 1][y];
            if (tempNumber <= val) {
                mapArray[x - 1][y] = 0;
                floodFill(x - 1, y, tempNumber);
            }
        }

        // Up
        if (x + 1 >= 0 && mapArray[x][y] == 0) {
            int tempNumber = mapArray[x + 1][y];
            if (tempNumber <= val) {
                mapArray[x + 1][y] = 0;
                floodFill(x + 1, y, tempNumber);
            }
        }

        // TBC

    }

// The public section contains all the properties and
// methods that are to be accessed from outside of the
// Map object.  Accessor methods allow controlled access
// to private properties.
public:

    // This is the default Map object constructor
    // I use it to initialise properties.  It gets run
    // every time a Map object is created.  This
    // constructor calls the overloaded constructor which
    // sets the filename.
    Map() {
        // Initialise the filename by calling the overload
        // constructor with an empty string
        Map("");

    }

    // Overloaded constructor to allow creation of
    // a map at the same time as setting the filename
    Map(string filename) {

        // Initialise the filename
        setFilename(filename);

        // Initialise the array
        initialiseMapArray(0);
    }

    // Class destructor - this is called everytime the object
    // is deleted
    ~Map() {

    }

    // The setFilename method is an accessor method that allows
    // the private filename to be set from outside of the Map object.
    void setFilename(string filename) {
        // Because we have a variables passed in to the method called
        // filename and a variable in the Map object called filename
        // we use the this-> keyword to distinguish between the two
        // and to ensure we set the correct variable.
        this->filename = filename;
    }

    // The setFilename method is an accessor method that allows
    // the private filename to be retrieved from outside of the
    // Map object.
    string getFilename() {
        return this->filename;
    }

    // This method displays the map in a visually correct
    // way, which is different to the way it is stored in the
    // array.
    void displayMap() {
        // Loop through the array on both the X and Y axis
        // but do it the wrong way around as we have stored
        // the map in the array according to the coordinate
        // system specified in the assignment.
        for (int x = MAP_X - 1; x >= 0; x--) {
            for (int y = MAP_Y - 1; y >= 0; y--) {
                // ...and display the output with a space
                cout << setfill('0') << setw(3) << mapArray[x][y] << " ";
            }
            // We've hit the end of the first axis, so add a
            // new line
            cout << endl;
        }
    }

    void displayMountainPassRoute(int mpStartingPoint) {
        int x = MAP_X - 1;
        // Invert the y coordinate so it matches up to the way
        // the map is stored in the array
        int y = MAP_Y - mpStartingPoint - 1;
        string path;

        while (x >= 0) {
            path += to_string(mapArray[y][x]) + " ";
            // Move to the next column(x) in the map
            x--;

            // Calculate which row(y) on the map is the easiest

            // This checks that the Y coordinates don't go outside of the array
            if ((y - 1 >= 0) && (y + 1 <= MAP_Y - 1)) {
                if (mapArray[y - 1][x] < mapArray[y][x] && mapArray[y - 1][x] < mapArray[y + 1][x]) {
                    y--;
                } else if (mapArray[y + 1][x] < mapArray[y][x] && mapArray[y + 1][x] < mapArray[y - 1][x]) {
                    y++;
                }
                // This if only check the adjacent block and the block underneath the
                // adjacent block.  It prevents going outside the top of the map
            } else if ((y - 1 >= 0) && ((y + 1 > MAP_Y - 1))) {
                if (mapArray[y - 1][x] < mapArray[y][x]) {
                    y--;
                }
                // This if only check the adjacent block and the block above the
                // adjacent block.  It prevents going outside the bottom of the map
            } else if ((y - 1 < 0) && (y + 1 <= MAP_Y - 1)) {
                if (mapArray[y + 1][x] < mapArray[y][x]) {
                    y++;
                }
            }
        }
        // Finally output the route
        cout << path << endl;
    }

    void displayRotatedMap() {
        // Loop through the array on both the X and Y axis
        // but do it from the Y axis first.  We need to
        // decrease the number on the Y axis while increasing
        // the number on the X axis so that
        for (int y = MAP_Y - 1; y >= 0; y--) {
            for (int x = 0; x <= MAP_X - 1; x++) {
                cout << mapArray[x][y] << " ";
            }
            // We've hit the end of the first axis, so add a
            // new line
            cout << endl;
        }
    }

    void displayReflectedMap() {
        for (int x = MAP_X - 1; x >= 0; x--) {
            for (int y = 0; y <= MAP_Y - 1; y++) {
                // ...and display the output with a space
                cout << mapArray[x][y] << " ";
            }
            // We've hit the end of the first axis, so add a
            // new line
            cout << endl;
        }
    }

    void displayTransposedMap() {
        for (int x = 0; x <= MAP_X - 1; x++) {
            for (int y = MAP_Y - 1; y >= 0; y--) {
                // ...and display the output with a space
                cout << mapArray[x][y] << " ";
            }
            // We've hit the end of the first axis, so add a
            // new line
            cout << endl;
        }
    }

    void createLake(int x, int y) {

        // Calculate the lake
        int tempNumber = mapArray[x][y];
        mapArray[x][y] = 0;
        floodFill(x, y, tempNumber);

    }

    void loadMap() {
        int val;
        string line;
        int x = MAP_X - 1;
        int y = MAP_Y - 1;

        // Open the file
        mapFile.open(filename);

        // Read each line at a time
        while (getline(mapFile, line)) { // This checks if the line was read okay
            // convert the stream into an Integer using istringstream
            istringstream tempInt(line);
            while (tempInt >> val) {
                mapArray[y][x] = val;
                x--;
            }
            x = MAP_X - 1;
            y--;
        }

        // Now we are done, close the file
        mapFile.close();
    }
};

class MenuItem {

private:
    string itemText;
    int itemNumber;

public:
    MenuItem() {

    }

    MenuItem(int itemNumber, string itemText) {
        setItemNumber(itemNumber);
        setItemText(itemText);
    }

    void setItemText(string itemText) {
        this->itemText = itemText;
    }

    string getItemText() {
        return this->itemText;
    }

    void setItemNumber(int itemNumber) {
        this->itemNumber = itemNumber;
    }

    int getItemNumber() {
        return this->itemNumber;
    }

};

int main() {

    // Menu constants
    const int CONTINUE_OPTION = 0;
    const int SPECIFY_AND_LOAD_MAP = 1;
    const int DISPLAY_MAP = 2;
    const int MOUNTAIN_PASS = 3;
    const int ROTATE_MAP = 4;
    const int REFLECT_MAP = 5;
    const int TRANSPOSE_MAP = 6;
    const int CREATE_LAKE = 7;
    const int EXIT = 9;

    // Mountain pass constants
    const int MOUNTAIN_PASS_STARTING_POINT = 4;

    // Variables
    int choice = CONTINUE_OPTION;
    int mpStartingPoint = MOUNTAIN_PASS_STARTING_POINT;
    string filename = "";
    Map myMap;
    bool mapLoaded = false;
    int lakeX=0;
    int lakeY=0;

    // The main program loop, keep displaying the menu and
    // asking what the user wants to do until the user chooses
    // to exit from the program
    while (choice != EXIT) {

        // Display Menu
        cout << "Welcome to Maps Assignment" << endl;
        cout << "==========================" << endl;
        cout << endl;
        cout << "Operation Menu" << endl;
        cout << "1 : Specify and load the map file" << endl;
        cout << "2 : Display the map" << endl;
        cout << "3 : Mountain pass" << endl;
        cout << "4 : Display rotated map" << endl;
        cout << "5 : Display reflected map" << endl;
        cout << "6 : Display transposed map" << endl;
        cout << "7 : Create lake - NOT DONE" << endl;
        cout << "9 : Quit" << endl;
        cout << endl;
        cout << "Selected map file: " << filename;
        cout << endl;
        cout << "Enter operation and press return" << endl;
        cout << "> ";

        // Get user choice
        cin >> choice;

        // Act on user choice
        switch (choice) {
            case SPECIFY_AND_LOAD_MAP:
                cout << "Please enter the path to the map file" << endl;
                cout << "> ";
                // Get the filename
                cin >> filename;
                // Set the filename
                myMap.setFilename(filename);
                // Load the map from the file into my map object
                myMap.loadMap();
                mapLoaded = true;
                cout << "Filename set to " << myMap.getFilename() << endl;
                break;
            case DISPLAY_MAP:
                if (mapLoaded) {
                    cout << "Displaying map" << endl << endl;
                    myMap.displayMap();
                    cout << endl;
                } else { cout << "No map loaded!" << endl << endl; }
                break;
            case MOUNTAIN_PASS:
                if (mapLoaded) {
                    cout << "Please enter the starting point on the left side of the map, from 0 - 8" << endl;
                    cout << "> ";
                    cin >> mpStartingPoint;
                    if ((mpStartingPoint > 8) || (mpStartingPoint < 0)) {
                        cout << "Invalid starting point!" << endl;
                    } else {
                        myMap.displayMountainPassRoute(mpStartingPoint);
                    }
                } else { cout << "No map loaded!" << endl << endl; }
                break;
            case ROTATE_MAP:
                if (mapLoaded) {
                    cout << "Displaying rotated map" << endl << endl;
                    myMap.displayRotatedMap();
                    cout << endl;
                } else { cout << "No map loaded!" << endl << endl; }
                break;
            case REFLECT_MAP:
                if (mapLoaded) {
                    cout << "Displaying reflected map" << endl << endl;
                    myMap.displayReflectedMap();
                    cout << endl;
                } else { cout << "No map loaded!" << endl << endl; }
                break;
            case TRANSPOSE_MAP:
                if (mapLoaded) {
                    cout << "Displaying transposed map" << endl << endl;
                    myMap.displayTransposedMap();
                    cout << endl;
                } else { cout << "No map loaded!" << endl << endl; }
                break;
            case CREATE_LAKE:
                if (mapLoaded) {
                    cout << "Please enter X coordinate" << endl;
                    cout << "> ";
                    cin >> lakeX;
                    cout << "Please enter Y coordinate" << endl;
                    cout << "> ";
                    cin >> lakeY;
                    cout << "Creating lake at " << lakeX << "," << lakeY << endl;
                    myMap.createLake(lakeX, lakeY);
                    cout << endl;
                } else { cout << "No map loaded!" << endl << endl; }
            case EXIT:
                cout << "Exiting Maps Assignment!" << endl;
                break;
            default:
                cout << "Not a valid operation!" << endl;
                break;
        }
        // Reset the users choice
        if (choice != EXIT) {
            choice = CONTINUE_OPTION;
        }
        cout << endl;
    }

//Exit the program
    return 0;
}