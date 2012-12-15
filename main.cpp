#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <../Memory_API/board.h>
#include <../Memory_API/player.h>
#include <stdlib.h>
using namespace std;

int main()
{
    ifstream file;
    std::string str;
    initscr();
//    getch();
//    while(!file.eof())
//    {
//        getline(file, str);
//        addstr(str.c_str());
//        printw("\n");
//    }
//    file.close();

    file.open("/home/tuxflo/workspace/QT/Memory_TUI/picures/X.txt");
    int y=0;
    int x=0;
    for(int i=0; i<6; i++)
    {
        for(int j=0; j<6; j++)
        {
            while(!file.eof())
            {
                getline(file, str);
                mvaddstr(y, x, str.c_str());
                printw("\n");
                y++;
            }
            y=i*9;
            x+=16;

        file.clear();
        file.seekg(0, ios::beg);
        getch();

        }
        y=(i+1)*9;
        x=0;
    }
    getch();
    endwin();

    return 0;
}

