#include "players_array.h"

Players_array::Players_array()
{
}

void Players_array::add_player()
{
    Player p;
    char name[25];
    addstr("Enter the name for the new Player!");
    getstr(name);
    p.set_name(name);
    _players.push_back(p);
}

void Players_array::remove_player()
{
    //List all Players
    int i=0;
    for(std::vector<Player>::iterator it = _players.begin(); it != _players.end(); ++it)
    {
        printw("%d \t %s\n", i, it->get_name().c_str());
        i++;
    }
    addstr("Which Player do you want to remove?(Enter number)");
    unsigned int ch;
    scanw("%d", &ch);
    printw("\n");
    if(ch > _players.size())
    {
        addstr("Invalid number");
        return remove_player();
    }
    _players.erase(_players.begin()+ch);
    i=0;
    for(std::vector<Player>::iterator it = _players.begin(); it != _players.end(); ++it)
    {
        printw("%d \t %s\n", i, it->get_name().c_str());
        i++;
    }
    getch();
}


std::vector<Player> Players_array::get_players()
{
    return _players;
}
