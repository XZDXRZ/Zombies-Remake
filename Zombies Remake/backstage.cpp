//back
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <cstring>
#include <cmath>
#include "map.h"
#define MAPN 0
using namespace std;
char ch;//Player's input
int px, py, health;
class Zombie {
public:
    int id, x, y;
    bool dead;
    void init(int arg_id) {//Generate Zombies
        srand((unsigned)time(NULL));
    a:x = rand() % 10;
        y = rand() % 10;
        id = arg_id;
        if (_map[MAPN][x][y] == ' ') {
            _map[MAPN][x][y] = 'Z';
            dead = false;
        }
        else
            goto a;
        Sleep(100);
        system("cls");
    }
    void move() {
        int tx, ty;
        //Zombie's Attack
        if (x + 1 == px && y == py)
            health--;
        if (x - 1 == px && y == py)
            health--;
        if (x == px && y + 1 == py)
            health--;
        if (x == px && y - 1 == py)
            health--;
        //Zombie's move
        srand((short)time(NULL));
        tx = rand() % 2;
        ty = rand() % 2;
        if (_map[MAPN][x + tx][y + ty] != ' ') {
            tx *= -1;
            ty *= -1;
        }
        if (_map[MAPN][x + tx][y + ty] == ' ') {
            _map[MAPN][x][y] = ' ';
            x += tx;
            y += ty;
            _map[MAPN][x][y] = 'Z';
            return;
        }
    }
    void close_attack() {//Attack closely
        if (abs(px - x) <= 5 && abs(py - y) <= 5) {//check the distance with Player
            if (px - x <= 0) {//up
                if (_map[MAPN][x - 1][y] == ' ') {
                    _map[MAPN][x][y] = ' ';
                    x--;
                    _map[MAPN][x][y] = 'Z';
                }
            }//or
            else {
                if (_map[MAPN][x + 1][y] == ' ') {
                    _map[MAPN][x][y] = ' ';
                    x++;
                    _map[MAPN][x][y] = 'Z';
                }
            }
            if (py - y >= 0) {//left
                if (_map[MAPN][x][y + 1] == ' ') {
                    _map[MAPN][x][y] = ' ';
                    y++;
                    _map[MAPN][x][y] = 'Z';
                }
            }//or
            else {
                if (_map[MAPN][x][y - 1] == ' ') {
                    _map[MAPN][x][y] = ' ';
                    y--;
                    _map[MAPN][x][y] = 'Z';
                }
            }
        }
    }
    void die()//Die
    {
        _map[MAPN][x][y] = ' ';
    }
}zombie[10];
int count_zombies() {//Count the zombies
    int z_count = 0;
    for (int i = 0; i < 10; i++) {//check every zombie
        if (!zombie[i].dead)
            z_count++;
    }
    return z_count;
}
bool is_win() {
    if (count_zombies())
        return false;
    return true;
}
void is_dead() {
    for (int i = 0; i <= 9; i++)
        if (zombie[i].x == px + 1 || zombie[i].x == px - 1 || zombie[i].y == py - 1 || zombie[i].y == py + 1)
        {
            zombie[i].dead = true;
            zombie[i].die();
        }
}
void move(int lines) {
    //玩家移动
    ch = _getch();
    if (ch == 'w' || ch == 'W') {
        if (_map[MAPN][px - 1][py] == ' ') {
            _map[MAPN][px][py] = ' ';
            px--;
            _map[MAPN][px][py] = 'I';
        }
    }
    if (ch == 'a' || ch == 'A') {
        if (_map[MAPN][px][py - 1] == ' ') {
            _map[MAPN][px][py] = ' ';
            py--;
            _map[MAPN][px][py] = 'I';
        }
    }
    if (ch == 's' || ch == 'S') {
        if (_map[MAPN][px + 1][py] == ' ') {
            _map[MAPN][px][py] = ' ';
            px++;
            _map[MAPN][px][py] = 'I';
        }
    }
    if (ch == 'd' || ch == 'D') {
        if (_map[MAPN][px][py + 1] == ' ') {
            _map[MAPN][px][py] = ' ';
            py++;
            _map[MAPN][px][py] = 'I';
        }
    }
    //这块地方是玩家的攻击机制
    if (ch == ' ') {
        if (_map[MAPN][px - 1][py] == 'Z') {
            _map[MAPN][px - 1][py] = ' ';
            is_dead();
        }
        if (_map[MAPN][px][py - 1] == 'Z') {
            _map[MAPN][px][py - 1] = ' ';
            is_dead();
        }
        if (_map[MAPN][px + 1][py] == 'Z') {
            _map[MAPN][px + 1][py] = ' ';
            is_dead();
        }
        if (_map[MAPN][px][py + 1] == 'Z') {
            _map[MAPN][px][py + 1] = ' ';
            is_dead();
        }
    }
    system("cls");
    for (int i = 0; i <= lines; i++)
        puts(_map[MAPN][i]);
}
void mode1(int lines)//模式
{
    HANDLE hConsole = NULL;
    SetConsoleTextAttribute(hConsole, 7);
    int t = 0, time = 0;
    cout << "Map Initing..." << endl;
    memcpy(_map, cmap, sizeof(cmap));
    Sleep(100);
    system("cls");
    for (int i = 0; i <= 9; i++)
    {
        zombie[i].init(i);
        printf("Zombies Initing: %d/10\n", i + 1);
    }
    system("cls");
    cout << "PLayer Initing..." << endl;
    health = 20;
    px = 3; py = 9;
    Sleep(100);
    system("cls");
    cout << "Ready?" << endl;
    Sleep(2000);
    cout << "Go!" << endl;
    Sleep(100);
    system("cls");
    for (int i = 0; i <= lines; i++)
        puts(_map[MAPN][i]);
    while (true)//游戏主循环
    {
        if (_kbhit())
            move(13);
        for (int i = 0; i <= 9; i++)
            if (!zombie[i].dead)
            {
                zombie[i].move();
                zombie[i].close_attack();
            }
        if (t >= 10)
        {
            t = 0;
            time++;
        }
        system("cls");
        for (int i = 0; i <= lines; i++)
            puts(_map[MAPN][i]);
        printf("Alive Time: %d\n", time);
        printf("Your Blood: %d\n", health);
        printf("Zombies Amounts: %d\n", count_zombies());
        Sleep(50);
        t++;
        if (health <= 0)
        {
            system("color 4f");
            printf("you lose!");
            Sleep(2000);
            return;
        }
        if (is_win())
        {
            system("color 6f");
            cout << "You Win!";
            Sleep(2000);
            return;
        }
    }
    return;
}