#include<iostream>
#include<string>
#include<limits>
#include<vector>

// Checking for obstacles
bool isObstacle (int tile) {
	switch (tile) {
		enum obstacles {
			WALL = 3,
			DOOR_A = 11,
    		DOOR_B,
 	   	DOOR_C,
	    	DOOR_D,
   	 	DOOR_E,
		};
		case WALL: return true;
		case DOOR_A: return true;
		case DOOR_B: return true;
		case DOOR_C: return true;
		case DOOR_D: return true;
		case DOOR_E: return true;
		default: return false;
	}
}

int main() {
    std::string input;
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
    std::cout << "\n";
    // Start conditions
    int width = 8, height = 8;
    int px = 1, py = 1;
    int x, y, id;
    // Pre-processing
    int widthOld, heightOld;
    std::string firstChar;
    int pxOld = px, pyOld = py, gameOver = 0;
    std::vector<std::vector<int>> coords(width, std::vector<int>(height, 0));
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
    /*
    Render images
    [  ] = empty tile (type 0)
    [()] = player (type 1)
    [<>] = end (type 2) 
    [##] = wall block
    Type doors::DOOR_A - doors::DOOR_E = doors A-E
    Type KEY_A - 20 = keys a-e
    */
    while (gameOver == 0) {
        // In-game calculations
        for (int checkForKey = 0; checkForKey < KEY_E - KEY_A; checkForKey++) {
        	if (coords[px][py] == keys::KEY_A + checkForKey) {
        		for (int y = 0; y < height; y++) {
        			for (int x = 0; x < width; x++) {
            			if (coords[x][y] == doors::DOOR_A +checkForKey) {
            				coords[x][y] = 0;
            			}
    				}
    			}
        	}
        }
        coords [pxOld][pyOld] = 0;
        coords [px][py] = 1;
        pxOld = px;
        pyOld = py;
        // Rendering
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                switch (coords[x][y]) {
                	
                	case basic::PLAYER:  std::cout << "()"; break;
                	case basic::END:        std::cout << "<>"; break;
                	case basic::WALL:      std::cout << "##"; break;
               	 case doors::DOOR_A: std::cout << "AA"; break;
                	case doors::DOOR_B: std::cout << "BB"; break;
                	case doors::DOOR_C: std::cout << "CC"; break;
                	case doors::DOOR_D: std::cout << "DD"; break;
                	case doors::DOOR_E: std::cout << "EE"; break;
                	case keys::KEY_A:      std::cout << "a-"; break;
                	case keys::KEY_B:      std::cout << "b-"; break;
                	case keys::KEY_C:      std::cout << "c-"; break;
                	case keys::KEY_D:      std::cout << "d-"; break;
                	case keys::KEY_E:      std::cout << "e-"; break;
                	default:                         std::cout << "  "; break;
                    }
            }
            std::cout << "\n";
        }
        
        std::getline(std::cin, input);
        firstChar = input[0];
                
        //Player movement/Ending command
        if (firstChar == "w" && py > 0 && isObstacle(coords[px][py-1]) == false) {
            py = py - 1;
        }
        if (firstChar == "s" && py < (height - 1) && isObstacle(coords[px][py+1]) == false) {
            py = py + 1;
        }
        if (firstChar == "a" && px > 0 && isObstacle(coords[px-1][py]) == false) {
            px = px - 1;
        }
        if (firstChar == "d" && px < (width-1) && isObstacle(coords[px+1][py]) == false) {
            px = px + 1;
		}
        if (input == "end") {
        	gameOver = 3;
        }
        // Debug mode
        if (debugMode) {
        	// Tile replacing
        	if (input == "/set") {
        		std::cout << "Type in x, y, block ID: ";
        		std::cin >> x >> y >> id;
        		if (x < 0 || x > width-1 || y < 0 || y > height-1) {
        			std::cout << "Invalid coords!\n";
        		}
        		else {
        			coords[x][y] = id;
        			std::cout << "Success\n";
        		}
        		std::cin.ignore();
        	}
        	// Teleportation
        	else if (input == "/tp") {
        		std:: cout << "Type in x, y: ";
        		std::cin >> x >> y;
        		if (x < 0 || x > width-1 || y < 0 || y > height-1) {
        			std::cout << "Invalid coords!\n";
        		}
        		else {
        			px = x;
        			py = y;
        			std::cout << "Success\n";
        		}
        		std::cin.ignore();
        	}
        	//World resize (WIP)
        	else if (input == "/resize") {
        		widthOld = width;
        		heightOld = height;
        		std::cout << "Type in width, height: ";
        		std::cin >> width >> height;
        		coords.resize(width);
        		for(int i = 0; i < width; i++) {
        			coords[i].resize(height);
        		}
        		for(int x = widthOld; x < width; x++) {
        			for(int y = 0; y < height; y++) {
        				coords[x][y] = 0;
        			}
        		}
        		for(int x = 0; x < widthOld; x++) {
        			for(int y = heightOld; y < height; y++) {
        				coords[x][y] = 0;
        			}
        		}
        	}
        }
        // End conditions
    	if (coords[px][py] == 2) {
        	gameOver = 1;
    	}
    }
    // Post-processing
    switch (gameOver) {
    	case 1: std::cout << "Game finished"; break;
    	case 2: std::cout << "Player died";    break;
    	case 3: std::cout << "Ended by input"; break;
    }

    return 0;
}
