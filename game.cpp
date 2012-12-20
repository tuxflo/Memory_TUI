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

    _status_win = newwin(10, COLS, 0, 0);
    _first_card = 0;
    _second_card = 0;
}

Game::~Game()
{
    delete _board;
}

void Game::init_game(std::vector<Player> *players)
{
    _board->init_game(players, _picture_path, _cover);
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
    noecho();
    //Make the cursor invisible
    //curs_set(0);
    refresh();
    for(int i=0; i<_rows; i++)
    {
        for(int j=0; j<_columns; j++)
        {
            _win[i][j] = newwin(7, 10, i*7+10, j*10+5);
            mvwaddstr(_win[i][j], 2, 0, _cover.c_str());
            box(_win[i][j], 0, 0);
            wrefresh(_win[i][j]);
        }
    }
    //Move to the first card and set it active
    move(0,0);
    box(_win[0][0], '|', '-');
    wrefresh(_win[0][0]);
    _play();
}

void Game::_play()
{
    int y=0;
    int x=0;
    int ch=0;
    while((ch = getch())!= 'Q')
    {
        switch(ch)
        {
        case KEY_DOWN:
            if(y<_rows-1)
            {
                y+=1;
                _view_active(_win[y][x], _win[y-1][x], y, x);
                move(y,x);
            }
            wclear(_status_win);
            wrefresh(_status_win);
            break;

        case KEY_UP:
            if(y>=1)
            {
                y-=1;
                _view_active(_win[y][x], _win[y+1][x], y, x);
                move(y,x);
            }
            wclear(_status_win);
            wrefresh(_status_win);
            break;

        case KEY_RIGHT:
            if(x<_columns-1)
            {
                x+=1;
                _view_active(_win[y][x], _win[y][x-1], y, x);
                move(y,x);
            }
            wclear(_status_win);
            wrefresh(_status_win);
            break;

        case KEY_LEFT:
            if(x>=1)
            {
                x-=1;
                _view_active(_win[y][x], _win[y][x+1], y, x);
                move(y,x);
            }
            wclear(_status_win);
            wrefresh(_status_win);
            break;

        case ' ':
            if(_board->get_turned(y, x))
                break;
            _board->turn(y, x);

            if(_first_card == 0)//Test if this is the first selected card
                _first_card = _win[y][x];
            else
                _second_card = _win[y][x];
            wclear(_win[y][x]);
            mvwaddstr(_win[y][x], 2, 2, _cards[y][x].c_str());
            box(_win[y][x], '|', '-');
            wrefresh(_win[y][x]);
            if(_second_card != 0) //That was the second card so check if they match
            {
                int ret = _board->match();
                if(ret > 0)
                {
                    mvwaddstr(_status_win, 0,0, "Found a right pair!");
                    std::string str;
                    str.append("Player: ");
                    str.append(_board->get_actual_player_name());
                    str.append(" gets ");
                    std::ostringstream num;
                    num << ret;
                    str.append(num.str());
                    str.append(" points!");
                    mvwaddstr(_status_win, 1,0, str.c_str());
                    wrefresh(_status_win);
                    if(_board->check_game_over())
                        _game_over();
                    _board->end_round();
                }
                else
                {
                    _board->end_round();
                    wclear(_first_card);
                    usleep(1500000);
                    wclear(_second_card);
                    mvwaddstr(_first_card, 2, 0, _cover.c_str());
                    mvwaddstr(_second_card, 2, 0, _cover.c_str());
                    box(_first_card, 0, 0);
                    box(_second_card, '|', '-');
                    wrefresh(_first_card);
                    wrefresh(_second_card);
                }
                _first_card = 0;
                _second_card = 0;
            }
            break;
        }
    }

}

void Game::_view_active(WINDOW *new_win, WINDOW *old_win, int y, int x)
{
        wmove(new_win, 0, 0);
        box(old_win, 0, 0);
        wclear(new_win);
        if(_board->get_turned(y,x))
        {
            mvwaddstr(new_win, 2, 2, _cards[y][x].c_str());
            wrefresh(new_win);
        }
        else
        {
            mvwaddstr(new_win, 2, 0, _cover.c_str());
            wrefresh(new_win);
        }
        box(new_win, '|', '-');
        wrefresh(old_win);
        wrefresh(new_win);
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

void Game::_refresh_status_win()
{
    //Show the active player and score
    //Clean up if a card was found
}

void Game::_game_over()
{
    //Start funny animation
    //View Highscore
    clear();
    std::string str;
    str.append("Player: ");
    str.append(_board->get_actual_player_name());
    str.append(" finished the game\n");
    mvaddstr(0, 0, str.c_str());
    str.clear();
    refresh();
    getch();
    endwin();
    exit(0);
}
