#include<iostream>

int main()
{
    std::string input;
    std::cout << "Впишите «start»\n";
    while (input != "start") {
        std::getline(std::cin, input);
    }
    /* Начало
    px, py - координаты игрока
    pxOld, pyOld - старые координаты игрока
    ex, ey - координаты финиша */
    
    int px, py, pxOld = 0, pyOld = 0, ex, ey, gameOver = 0, width, height;
    //Начальные условия
    width = 8;
    height = 8;
    px = 1;
    py = 1;
    ex = 6;
    ey = 6;
    //Обнулятор
    int coords [width][height];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            coords[x][y] = 0;
    	}
    }
    /* При каждом ходе игра проверяет клетку,
    на которую наступает игрок, на наличие финиша.
    Если он есть, игра завершается.
    Отсчет клеток слева сверху.
    [  ]-пустая клетка (тип 0)
    [()]-клетка с игроком (тип 1)
    [<>]-клетка с финишем (тип 2) 
    [##]-стена (тип 3) (WIP)
    []*/
    while (gameOver == 0) {
        coords [pxOld][pyOld] = 0;
        coords [px][py] = 1;
        coords [ex][ey] = 2;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                switch (coords[x][y]) {
                case 1: std::cout << "()"; break;
                case 2: std::cout << "<>"; break;
                default: std::cout << "  "; break;
                    }
            }
            std::cout << "\n";
        }        
        std::getline(std::cin, input);
        pxOld = px;
        pyOld = py;
        if (input == "w") {
            py = py - 1;
            if (py < 0) {
                py = 0;
            }
        }
        if (input == "s") {
            py = py + 1;
            if (py > (height - 1)) {
                py = (height - 1);
            }
        }
        if (input == "a") {
            px = px - 1;
            if (px < 0) {
                px = 0;
            }
        }
        if (input == "d") {
            px = px + 1;
            if (px > (width - 1)) {
                px = (width - 1);
            }
        }
    if ((px == ex) && (py == ey)) {
        gameOver = 1;
    }
    }
    std::cout << "Игра завершена";
    return 0;
}
