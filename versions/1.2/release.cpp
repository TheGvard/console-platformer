#include<iostream>

bool isObstacle (int tile) {
	switch (tile) {
		case 3: return true;
		case 11: return true;
		case 12: return true;
		case 13: return true;
		case 14: return true;
		case 15: return true;
		default: return false;
	}
}

int main() {
    std::string input;
    std::cout << "Type in Â«startÂ»\n";
    while (input != "start") {
        std::getline(std::cin, input);
        if (input != "start") {
        	std::cout << "Sorry, must've been the wind...\nTry again:\n"; //lol idk why
        }
    }
    std::cout << "\n";
    /*
    px, py - player coordinates
    pxOld, pyOld - player coordinates from previous frame
    ex, ey - end coordinates
    */
    int px, py, pxOld = 0, pyOld = 0, ex, ey, gameOver = 0;
    // Start conditions
    	const int width = 8, height = 8;
    px = 1;
    py = 1;
    ex = 6;
    ey = 6;
    // Pre-processing
    int coords [width][height];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            coords[x][y] = 0;
    	}
    }
    coords[ex][ey] = 2;
    std::cout << "w, a, s, d for movement\n";
    // Editor
    coords[5][5] = 3;
    coords[7][5] = 3;
    coords[5][6] = 3;
    coords[7][6] = 3;
    coords[5][7] = 3;
    coords[6][7] = 3;
    coords[7][7] = 3;
    coords[6][4] = 11;
    coords[2][5] = 11;
    coords[6][5] = 12;
    coords[0][7] = 16;
    coords[7][0] = 17;
    /*
    Render images
    [  ] = empty tile (type 0)
    [()] = player (type 1)
    [<>] = end (type 2) 
    [##] = wall (type 3)
    Type 11 - 15 = doors A-E
    Type 16 - 20 = keys a-e
    */
    while (gameOver == 0) {
        // In-game calculations
        for (int checkForKey = 0; checkForKey < 4; checkForKey++) {
        	if (coords[px][py] == 16+checkForKey) {
        		for (int y = 0; y < height; y++) {
        			for (int x = 0; x < width; x++) {
            			if (coords[x][y] == 11+checkForKey) {
            				coords[x][y] = 0;
            			}
    				}
    			}
        	}
        }
        coords [pxOld][pyOld] = 0;
        coords [px][py] = 1;
        // Rendering
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                switch (coords[x][y]) {
                case 1: std::cout << "()"; break;
                case 2: std::cout << "<>"; break;
                case 3: std::cout << "##"; break;
                case 11: std::cout << "AA"; break;
                case 12: std::cout << "BB"; break;
                case 13: std::cout << "CC"; break;
                case 14: std::cout << "DD"; break;
                case 15: std::cout << "EE"; break;
                case 16: std::cout << "a-"; break;
                case 17: std::cout << "b-"; break;
                case 18: std::cout << "c-"; break;
                case 19: std::cout << "d-"; break;
                case 20: std::cout << "e-"; break;
                default: std::cout << "  "; break;
                    }
            }
            std::cout << "\n";
        }
        // Player movement
        std::getline(std::cin, input);
        pxOld = px;
        pyOld = py;
        if (input == "w" && py > 0 && isObstacle(coords[px][py-1]) == false) {
            py = py - 1;
        }
        if (input == "s" && py < (height - 1) && isObstacle(coords[px][py+1]) == false) {
            py = py + 1;
        }
        if (input == "a" && px > 0 && isObstacle(coords[px-1][py]) == false) {
            px = px - 1;
        }
        if (input == "d" && px < (width-1) && isObstacle(coords[px+1][py]) == false) {
            px = px + 1;
            }
    	if (px == ex && py == ey) {
        	gameOver = 1;
    	}
    }
    
    std::cout << "Game ended";
    return 0;
}
