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
    //return item.get();
    return item->itm_get();

  game->sayCmd(GET);
  return false;
}

void Room::lookItem(string key) {
  Item *item = items[key];

  if (item)
    //item.look();
    item->itm_look();

  game->sayCmd(LOOK);
}
