#ifndef PLAYERS_ARRAY_H
#define PLAYERS_ARRAY_H
#include "../Memory_API/player.h"
#include <vector>
#include <ncurses.h>

class Players_array
{
public:
    Players_array();
    void add_player();
    void remove_player();
    std::vector<Player> get_players();
private:
    std::vector<Player> _players;
};

#endif // PLAYERS_ARRAY_H
