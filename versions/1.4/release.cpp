#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>
#include <cctype>

// List of in-game tiles
enum basic {
	EMPTY,
	PLAYER,
	END,
	WALL,
};
enum doors {
	DOOR_A = 11,
	DOOR_B,
	DOOR_C,
	DOOR_D,
	DOOR_E,
};
enum keys {
	KEY_A = 16,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
};
// Finding middle number out of 3
int middle (int a, int b, int c) {
	int sum = a + b + c;
	int middle = sum - std::max(a, std::max(b, c)) - std::min(a, std::min(b, c));
	return middle;
}
// Tile rendering
void tileRender(int tile) {
	switch (tile) {
	case basic::PLAYER: std::cout << "()"; break;
	case basic::END:    std::cout << "<>"; break;
	case basic::WALL:   std::cout << "##"; break;
	case doors::DOOR_A: std::cout << "AA"; break;
	case doors::DOOR_B: std::cout << "BB"; break;
	case doors::DOOR_C: std::cout << "CC"; break;
	case doors::DOOR_D: std::cout << "DD"; break;
	case doors::DOOR_E: std::cout << "EE"; break;
	case keys::KEY_A:   std::cout << "a-"; break;
	case keys::KEY_B:   std::cout << "b-"; break;
	case keys::KEY_C:   std::cout << "c-"; break;
	case keys::KEY_D:   std::cout << "d-"; break;
	case keys::KEY_E:   std::cout << "e-"; break;
	default:            std::cout << "  "; break;
	}
}
// Checking for obstacles
bool isObstacle (int tile) {
	switch (tile) {
		case basic::WALL:
		case doors::DOOR_A:
		case doors::DOOR_B:
		case doors::DOOR_C:
		case doors::DOOR_D:
		case doors::DOOR_E:
		return true;
		default: return false;
	}
}

int main() {
    std::string input = "";
    bool debugMode;
    
    std::cout << "Type in «start»\n";
    
    while (input != "start") {
        std::getline(std::cin, input);
		if (input == "start") {} 
		else if (input == "debug") {
			debugMode = true;
    		std::cout << "Debug mode activated";
		}
		else {
			std::cout << "Sorry, must've been the wind...\nTry again:";
		}
        std::cout << "\n\n";
    }
    // Start conditions
    bool noclip = false;
    bool renderEverything = false;
    int width = 8, height = 8;
    int px = 4, py = 4;
    int camDistX = 2, camDistY = 2;
    // Pre-processing
    int camPosX, camPosY;
    int camSideUp, camSideDown, camSideLeft, camSideRight;
    int x, y;
    std::string firstChar;
    int gameOver = 0;
    std::vector<std::vector<int>> coords(width, std::vector<int>(height, 0));

    std::cout << "w, a, s, d for movement\n";
    // Editor
    coords[6][6] = basic::END;
    coords[5][5] = basic::WALL;
    coords[7][5] = basic::WALL;
    coords[5][6] = basic::WALL;
    coords[7][6] = basic::WALL;
    coords[5][7] = basic::WALL;
    coords[6][7] = basic::WALL;
    coords[7][7] = basic::WALL;
    coords[6][4] = doors::DOOR_A;
    coords[0][5] = doors::DOOR_A;
    coords[1][5] = doors::DOOR_A;
    coords[2][5] = doors::DOOR_A;
    coords[3][5] = doors::DOOR_A;
    coords[6][5] = doors::DOOR_B;
    coords[0][7] = keys::KEY_A;
    coords[7][0] = keys::KEY_B;
    // In-game calculations
    while (gameOver == 0) {
        camPosX = px;
        camPosY = py;
        for (int checkForKey = 0; checkForKey < KEY_E - KEY_A; checkForKey++) {
        	if (coords[px][py] == keys::KEY_A + checkForKey && !noclip) {
        		for (int y = 0; y < height; y++) {
        			for (int x = 0; x < width; x++) {
        				int compareValue = coords[x][y] - checkForKey;
            			if (compareValue == doors::DOOR_A || compareValue == keys::KEY_A) {
            				coords[x][y] = 0;
            			}
    				}
    			}
        	}
        }
        
        // Render operations
        if (renderEverything == true) {
        	camSideDown = 0;
        	camSideUp = height;
        	camSideLeft = 0;
        	camSideRight = width;
        }
        else {
        camSideDown = middle(0, camPosY - camDistY, height - 2 * camDistY - 1);
        camSideUp = std::min(camSideDown + 2 * camDistY + 1, height);
        camSideLeft = middle(0, camPosX - camDistX, width - 2 * camDistX - 1);
        camSideRight = std::min(camSideLeft + 2 * camDistX + 1, width);
        }
        for (int x = camSideLeft - 1; x < camSideRight + 1; x++) std::cout << "==";
        std::cout << "\n";
        for (int y = camSideDown; y < camSideUp; y++) {
            std::cout << "||";
            for (int x = camSideLeft; x < camSideRight; x++) {
                if (x == px && y == py) {
                	std::cout << "()";
                }
                else tileRender(coords[x][y]);
            }
            std::cout << "||\n";
        }
        for (int x = camSideLeft - 1; x < camSideRight + 1; x++) std::cout << "==";
        std::cout << "\n";
        
        std::getline(std::cin, input);
        firstChar = input[0];
                
        // Player movement / Misc
        if (firstChar == "w" && py > 0) {
            if (noclip || !isObstacle(coords[px][py-1])) {
            	py = py - 1;
            }
        }
        else if (firstChar == "s" && py < (height - 1)) {
            if (noclip || !isObstacle(coords[px][py+1])) {
            py = py + 1;
            }
        }
        else if (firstChar == "a" && px > 0) {
            if (noclip || !isObstacle(coords[px-1][py])) {
            	px = px - 1;
            }
        }
        else if (firstChar == "d" && px < (width-1)) {
            if (noclip || !isObstacle(coords[px+1][py])) {
            	px = px + 1;
            }
		}
		else if (input == "uuddlrlrbastart") {
		      debugMode = !debugMode;
		      std::cout << "DebugMode " << debugMode << "\n";
		}
        else if (input == "end")   gameOver = 3;
        // Debug mode
        if (debugMode == true && firstChar == "/") {
        	// Tile replacing
        	if (input == "/set") {
        		std::cout << "Type in x, y, block ID: ";
        		int id;
        		std::cin >> x >> y >> id;
        		if (x < 0 || x > width-1 || y < 0 || y > height-1) {
        			std::cout << "Invalid coords";
        		}
        		else {
        			coords[x][y] = id;
        			std::cout << "Success";
        		}
        	}
        	// Teleportation
        	else if (input == "/tp") {
        		std:: cout << "Type in x, y: ";
        		std::cin >> x >> y;
        		if (x < 0 || x > width-1 || y < 0 || y > height-1) {
        			std::cout << "Invalid coords";
        		}
        		else {
        			px = x;
        			py = y;
        			std::cout << "Success";
        		}
        	}
        	// World resize
        	else if (input == "/resize") {
        		std::cout << "Type in width, height: ";
        		std::cin >> width >> height;
        		coords.resize(width);
        		for (int i = 0; i < width; i++) {
        			coords[i].resize(height);
        		}
        	}
        	// Camera settings
        	else if (input == "/rule") {
        		std::cout << "Type in rule, state: ";
        		std::getline(std::cin, input);
        		std::string rule = "";
        		int i;
        		bool argumentError = false;
        		for(i = 0; !std::isspace(input[i]); i++) {
        			if (i < input.size()) {
        				rule += input[i];
        			}
        			else {
        				std::cout << "No argument included";
        				break;
        			}
        		}
        		std::string stateString = "";
        		int state;
        		for(i += 1; i < input.size(); i++) {
        			if (std::isdigit(input[i])) {
        				stateString += input[i];
        			}
        			else {
        				argumentError = true;
        				break;
        			}		
        		}
        		if (argumentError = true) {
        			std::cout << "Invalid argument\n";
        			continue;
        		}
        		else state = std::stoi(stateString);
        		// Rules list
        		if (rule == "renderEverything") {
        			if (state >= 0 && state <= 1) {
        				renderEverything = state;
        			}
        			else std::cout << "Can only be 0 or 1";
        		}
        		else if (rule == "camDistance") {
        			if (state >= 0) {
        				camDistX = state;
        				camDistY = state;
        			}
        			else std::cout << "Cannot be lower than 0";
        		}
        		else if (rule == "camDistanceX") {
        			if (state >= 0) {
        				camDistX = state;
        			}
        			else std::cout << "Cannot be lower than 0";
        		}
        		else if (rule == "camDistanceY") {
        			if (state >= 0) {
        				camDistY = state;
        			}
        			else std::cout << "Cannot be lower than 0";
        		}
        		else std::cout << "Rule not found";
        	}
        	// Noclip
        	else if (input == "/noclip") {
        		noclip = !noclip;
        		std::cout << "Noclip " << noclip;
        	}
        	std::cout << "\n";
        }
        // End conditions
    	if (coords[px][py] == basic::END) {
        	gameOver = 1;
    	}
    }
    // Post-processing
    switch (gameOver) {
    	case 1: std::cout << "You Win!";       break;
    	case 2: std::cout << "Player died";    break;
    	case 3: std::cout << "Ended by input"; break;
    }

    return 0;
}
