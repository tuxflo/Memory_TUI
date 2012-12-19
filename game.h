#ifndef GAME_H
#define GAME_H
#include "../Memory_API/board.h"
#include <iostream>
#include <fstream>
#include <ncurses.h>

class Game
{
public:
    Game(int rows, int columns, std::string pics, std::string cover);
    ~Game();
    void init_game(std::vector<Player> *players);
    void view_board();
private:
    void _play();
    void _view_active(WINDOW *new_win, WINDOW *old_win, int y, int x);
    void _set_cover();
    void _set_cards();
    void _refresh_status_win();
    void _game_over();
    Board *_board;
    //std::vector<std::string> _cards;
    std::string _picture_path;
    std::string _cover;
    std::string **_cards;
    int _rows;
    int _columns;
    WINDOW ***_win;
    WINDOW *_first_card;
    WINDOW *_second_card;
    WINDOW *_status_win;
};

#endif // GAME_H
