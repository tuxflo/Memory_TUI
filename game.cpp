#include "game.h"

Game::Game(int rows, int columns, std::string pics, std::string cover)
{
    _rows = rows;
    _columns = columns;
    _board = new Board(rows, columns);
    _picture_path = pics;
    _cover = cover;

    _win = new WINDOW**[rows];
    for(int i=0; i<_rows; i++)
        _win[i] = new WINDOW*[_columns];
}

Game::~Game()
{
    delete _board;
}

void Game::init_game(std::vector<Player> players)
{
    _board->init_game(&players, _picture_path, _cover);
    _set_cover();
    _set_cards();
    for(int i=0; i<_rows; i++)
    {
        for(int j=0; j<_columns; j++)
        {

        }
    }
}

void Game::view_board()
{
    //Initialise stdscr
    initscr();
    keypad(stdscr, TRUE);
    refresh();
    for(int i=0; i<_rows; i++)
    {
        for(int j=0; j<_columns; j++)
        {
            _win[i][j] = newwin(9, 17, i*9, j*17+1);
            mvwaddstr(_win[i][j], 3, 0, _cover.c_str());
            box(_win[i][j], 0, 0);
            wrefresh(_win[i][j]);
        }
    }
}

void Game::_set_cover()
{
    //Open the give cover file read only
    std::ifstream file(_cover.c_str(), std::ios::in);
    file.seekg(0, std::ios::end);
    _cover.resize(file.tellg());
    file.seekg(0, std::ios::beg);

    //Set the data from the file into _cover
    _cover.assign(std::istreambuf_iterator<char>(file),
                  std::istreambuf_iterator<char>());
    file.close();
}

void Game::_set_cards()
{
    //Init a 2d array of strings for the pictures on the cards
    _cards = new std::string*[_rows];
    for(int i=0; i<_rows; i++)
        _cards[i] = new std::string[_columns];

    std::ifstream file;
    //Open each picture file and put the data to _cards
    for(int i=0; i<_rows; i++)
    {
        for(int j=0; j<_columns; j++)
        {
            file.open(_board->get_picture(i, j).c_str(), std::ios::in);
            file.seekg(0, std::ios::end);
            _cards[i][j].reserve(file.tellg());
            file.seekg(0, std::ios::beg);
            _cards[i][j].assign(std::istreambuf_iterator<char>(file),
                                std::istreambuf_iterator<char>());
            file.close();
        }
    }
}
