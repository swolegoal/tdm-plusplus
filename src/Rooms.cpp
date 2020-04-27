#include "Game.hpp"
#include "Item.hpp"
#include "Rooms.hpp"
#include <functional>
#include <string>

using namespace std;

Room::Room() {
  for (const auto &pair : items) {
    pair.second->gg(game);
  }
}

bool Room::getItem(string key) {
  Item *item = items[key];

  if (item)
    return item->itm_get();

  game->sayCmd(GET);
  return false;
}

void Room::lookItem(string key) {
  Item *item = items[key];

  if (item)
    item->itm_look();

  game->sayCmd(LOOK);
}

void Room::enter() { return; }

void Room::desc() { game->sayTxt(&room_desc); }

void SouthRoom::enter() { nonetheless = false; }

void SouthRoom::desc() {
  int tk_idx = items["trinket"]->getIdx('g');
  switch (tk_idx) {
    case 0: {
      nonetheless ? game->sayTxt(&lookies[0]) : game->sayTxt(&room_desc);
      break;
    }
    case 1: {
      bool _oof = items["trinket"]->getOof();
      _oof ? game->sayTxt(&lookies[2]) : game->sayTxt(&lookies[1]);
      break;
    }
  }
}
