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
    void init_game(std::vector<Player> players);
    void view_board();
private:
    void _set_cover();
    void _set_cards();
    Board *_board;
    //std::vector<std::string> _cards;
    std::string _picture_path;
    std::string _cover;
    std::string **_cards;
    int _rows;
    int _columns;
    WINDOW ***_win;
};

#endif // GAME_H
