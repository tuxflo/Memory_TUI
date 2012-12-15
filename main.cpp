#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <../Memory_API/board.h>
#include <../Memory_API/player.h>
#include <stdlib.h>
using namespace std;
string** parse_board(Board *b, string **cards, string *cover, int rows, int columns);
void view_board(Board *b, string **cards, string *cover, int rows, int columns);

int main()
{
    Board board(4,4);
    std::vector<Player> players(2);
    string **cards = 0;
    string cover;
    players.at(0).set_name("tuxflo");
    players.at(1).set_name("anne");
    board.init_game(&players, "./pictures/", "./pictures/cover");
    initscr();
    cards = parse_board(&board, cards, &cover, 4, 4);

    view_board(&board, cards, &cover, 4, 4);
    getch();
    board.turn(0,0);
    board.turn(0,1);
    view_board(&board, cards, &cover, 4, 4);
    getch();
    if(!board.match())
    {
        board.end_round();
        cout << "Now it is your turn " << board.get_actual_player_name() << endl;
        cout << "You already have " << board.get_actual_player_score() << " points!" << endl;
    }
    else
    {
        cout << "Yeah! You found a right pair." << endl;
        if(board.check_game_over())
        {
            cout << "That was the last card. Game is over now!" << endl;
        }
    }
    view_board(&board, cards, &cover, 4, 4);
    getch();

    endwin();
    return 0;
}

string** parse_board(Board *b, string **cards, string *cover, int rows, int columns)
{
    ifstream file;
    //Set the cover first
    file.open(b->get_cover().c_str(), ios::in);
    getline(file, *cover);
    file.close();

    cards = new string*[rows];
    for(int i=0; i<rows; i++)
        cards[i] = new string[columns];

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<columns; j++)
        {
            file.open(b->get_picture(i, j).c_str(), ios::in);
            getline(file, cards[i][j]);
            //cout << cards[i][j];
            file.close();
        }
    }
    return cards;
}

void view_board(Board *b, string **cards, string *cover, int rows, int columns)
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j< columns; j++)
        {
            if(b->get_turned(i, j))
            {
                addstr(cards[i][j].c_str());
                addch(' ');
            }
            else
            {
                addstr(cover->c_str());
                addch(' ');
            }
        }
        printw("\n");
        //cout << endl;
    }
    //cout << endl;
    printw("\n");
}
