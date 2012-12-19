#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <../Memory_API/board.h>
#include "players_array.h"
#include "game.h"
#include <stdlib.h>
using namespace std;
string **parse_board(Board *b, string **cards, string *cover, int rows, int columns);
void view_active(WINDOW *old_win, WINDOW *new_win, string cover_active, string cover2, Board *b, int y, int x, string **cards);

int main()
{
    initscr();

    vector<Player> players(2);
    players.at(0).set_name("tuxflo");
    players.at(1).set_name("anne");

    addstr("How much rows should the board have? ");
    int rows, columns;
    scanw("%d", &rows);
    printw("\n");
    addstr("How much columns should the board have? ");
    scanw("%d", &columns);
    printw("\n");
    clear();
    Game game(rows, columns, "/home/tuxflo/workspace/QT/Memory_TUI/picures/", "/home/tuxflo/workspace/QT/Memory_TUI/picures/X.txt");
    game.init_game(&players);
    game.view_board();
    getch();
    endwin();

}

//    string cover;
//    string cover2;
//    string cover_active;
//    string **cards = 0;
//    ifstream file;
//    file.open("/home/tuxflo/workspace/QT/Memory_TUI/picures/X.txt", ios::in);
//    file.seekg(0, ios::end);
//    cover.reserve(file.tellg());
//    file.seekg(0, ios::beg);

//    cover.assign(istreambuf_iterator<char>(file),
//                 istreambuf_iterator<char>());

//    file.close();

//    file.open("/home/tuxflo/workspace/QT/Memory_TUI/picures/o.txt", ios::in);
//    file.seekg(0, ios::end);
//    cover_active.reserve(file.tellg());
//    file.seekg(0, ios::beg);

//    cover_active.assign(istreambuf_iterator<char>(file),
//                 istreambuf_iterator<char>());
//    file.close();

//    Board board(4,4);
//    Player p1;
//    Player p2;
//    p1.set_name("tuxflo");
//    p2.set_name("anne");
//    vector<Player> players(2);
//    players.at(0) = p1;
//    players.at(1) = p1;
//    board.init_game(&players, "/home/tuxflo/workspace/QT/Memory_TUI/picures/", "/home/tuxflo/workspace/QT/Memory_TUI/picures/X.txt");

//    cards = parse_board(&board, cards, &cover2, 4, 4);


//    //Init ncurses

//    initscr();
//    keypad(stdscr, TRUE);
//    noecho();
//    //curs_set(0);
//    WINDOW *win[4][4];
//    WINDOW *_active = 0;
//    WINDOW *_second = 0;
//    refresh();

//    for(int i=0; i <4; i++)
//    {
//        for(int j=0; j<4; j++)
//        {
//            win[i][j] = newwin(9, 17, i*9, j*17+1);
//            mvwaddstr(win[i][j], 3, 0, cover2.c_str());
//            box(win[i][j], 0, 0);
//            wrefresh(win[i][j]);
//        }
//    }

//    box(win[0][0], '|', '-');
//    wrefresh(win[0][0]);

//    int y=0;
//    int x=0;

//    move(y,x);
//    int ch=0;
//    int count=0;
//    while((ch = getch())!= 'Q')
//    {
//        switch(ch)
//        {
//        case KEY_DOWN:
//            if(y<3)
//            {
//                y+=1;
//                view_active(win[y-1][x], win[y][x], cover_active, cover2, &board, y, x, cards);
//                move(y,x);
//            }
//            break;

//        case KEY_UP:
//            if(y>=1)
//            {
//                y-=1;
//                view_active(win[y+1][x], win[y][x], cover_active, cover2, &board, y, x, cards);
//                move(y,x);
//            }
//            break;

//        case KEY_RIGHT:
//            if(x<3)
//            {
//                x+=1;
//                view_active(win[y][x-1], win[y][x], cover_active, cover2, &board, y, x, cards);
//                move(y,x);
//            }
//            break;

//        case KEY_LEFT:
//            if(x>=1)
//            {
//                x-=1;
//                view_active(win[y][x+1], win[y][x], cover_active, cover2, &board, y, x, cards);
//                move(y,x);
//            }
//            break;

//        case ' ':
//            if(board.get_turned(y, x))
//                break;
//            board.turn(y, x);
//            if(_active == 0)
//                _active = win[y][x];
//            else
//                _second = win[y][x];
//            count++;
//            wclear(win[y][x]);
//            box(win[y][x], '|', '-');
//            mvwaddstr(win[y][x], 2, 2, cards[y][x].c_str());
//            wrefresh(win[y][x]);
//            refresh();
//            if(count == 2)
//            {

//                count = 0;
//                if(board.match())
//                {
//                    //Print found message
//                    mvwaddstr(stdscr, 40, 0, "Gefunden!");
//                    wrefresh(win[y][x]);
//                }
//                else
//                {
//                    board.end_round();
//                wclear(_active);
//                usleep(1500000);
//                wclear(_second);
//                mvwaddstr(_active, 3, 0, cover2.c_str());
//                mvwaddstr(_second, 3, 0, cover2.c_str());
//                box(_active, 0, 0);
//                box(_second, '|', '-');
//                wrefresh(_active);
//                wrefresh(_second);
//                }
//                _active = 0;
//                _second = 0;


//            }
//            refresh();
//            break;

//        }
//    }
//    endwin();

//    return 0;
//}

//string **parse_board(Board *b, string **cards, string *cover, int rows, int columns)
//{
//    ifstream file;
//    //Set the cover first
//    file.open(b->get_cover().c_str(), ios::in);
//    file.seekg(0, ios::end);
//    cover->reserve(file.tellg());
//    file.seekg(0, ios::beg);

//    cover->assign(istreambuf_iterator<char>(file),
//                 istreambuf_iterator<char>());
//    file.close();

//    //Initialise a string array for the card strings
//    cards = new string*[rows];
//    for(int i=0; i<rows; i++)
//        cards[i] = new string[columns];

//    for(int i=0; i<rows; i++)
//    {
//        for(int j=0; j<columns; j++)
//        {
//            file.open(b->get_picture(i, j).c_str(), ios::in);
//            file.seekg(0, ios::end);
//            cards[i][j].reserve(file.tellg());
//            file.seekg(0, ios::beg);
//            cards[i][j].assign(istreambuf_iterator<char>(file),
//                               istreambuf_iterator<char>());
//            file.close();
//        }
//    }
//    return cards;
//}

//void view_active(WINDOW *old_win, WINDOW *new_win, string cover_active, string cover2, Board *b, int y, int x,string **cards)
//{
//    wmove(new_win, 0, 0);
//    box(old_win, 0, 0);
//    wclear(new_win);
//    if(b->get_turned(y,x))
//    {
//        mvwaddstr(new_win, 2, 2, cards[y][x].c_str());
//        wrefresh(new_win);
//    }
//    else
//    {
//        mvwaddstr(new_win, 3, 0, cover2.c_str());
//        wrefresh(new_win);
//    }
//    box(new_win, '|', '-');
//    wrefresh(old_win);
//    wrefresh(new_win);
//}
