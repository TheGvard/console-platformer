#include<iostream>
using namespace std;

int main()
{
    string input;
    int special = 0;
    cout << "Впишите «start»\n";
    while (special == 0) {
        getline(cin, input);
        special = (input == "start");
    }
    /* Начало
    px, py - координаты игрока
    pxOld, pyOld - старые координаты игрока
    ex, ey - координаты финиша */
    
    int x, y, px, py, pxOld, pyOld, ex, ey, gameOver, width, height, tile;
    pxOld = pyOld = 0;
    //Редактор
    width = 8;
    height = 8;
    px = 1;
    py = 1;
    ex = 6;
    ey = 6;
    //Обнулятор (без него не работает)
    int coords [width][height];
    x = y = 0;
        while (y < height) {
            x = 0;
            while (x < width) {
            coords [x][y] = 0;
            x = x + 1;
        }
        y = y + 1;
    }
    gameOver = 0;
    /* При каждом ходе игра проверяет клетку,
    на которую наступает игрок, на наличие финиша.
    Если он есть, игра завершается.
    Отсчет клеток слева сверху.
    [  ]-пустая клетка (тип 0)
    [()]-клетка с игроком (тип 1)
    [<>]клетка с финишем (тип 2) 
    []*/
    while (gameOver == 0) {
        special = 0;
        coords [pxOld][pyOld] = 0;
        coords [px][py] = 1;
        coords [ex][ey] = 2;
        x = y = 0;
        while (y < height) {
            x = 0;
            while (x < width) {
                cout << "[";
                if (coords [x][y] == 0) {
                    cout << "  ";
                } else if (coords [x][y] == 1) {
                    cout << "()";
                } else if ( coords [x][y] == 2) {
                    cout << "<>";
                } else {
                    //Unused00
                    coords[x][y] = 0;
                    cout << "  ";
                }
                cout << "]";
                x = x + 1;
            }
            cout << "\n";
            y = y + 1;
        }        
        y = 0;
        cout << "\nW,A,S,D для управления\n";
        getline(cin, input);
        pxOld = px;
        pyOld = py;
        special = (input == "w");
        if (special == 1) {
            py = py - 1;
            if (py < 0) {
                py = 0;
            }
        }
        special = (input == "s");
        if (special == 1) {
            py = py + 1;
            if (py > (height - 1)) {
                py = (height - 1);
            }
        }
        special = (input == "a");
        if (special == 1) {
            px = px - 1;
            if (px < 0) {
                px = 0;
            }
        }
        special = (input == "d");
        if (special == 1) {
            px = px + 1;
            if (px > (width - 1)) {
                px = (width - 1);
            }
        }
    if ((px == ex) & (py == ey)) {
        gameOver = 1;
    }
    }
    cout << "Игра завершена";
    return 0;
}
