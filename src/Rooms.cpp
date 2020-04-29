#include "Game.hpp"
#include "Item.hpp"
#include "Rooms.hpp"
#include "RoomText.hpp"
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

bool Room::getItem(string key) {
  Item *item = items[key];

  if (item)
    return item->itm_get();

  game->sayCmd(GET);
  return false;
}

void Room::lookItem(string key) {
  Item *item = items[key];

  if (item) {
    item->itm_look();
    return;
  }

  game->sayCmd(LOOK);
}

void Room::setupItemWumpii(void) {
  for (const auto &pair : items) {
    pair.second->gg(game);
  }
}

void Room::parseCmd(vector<string> &args) {
  if (args.size() < 1)
    return;

  vector<string> myargs(args);
  for (string &arg : myargs) { game->lc(arg); }

  /* // DEBUG
   * for (string &arg : myargs) { cout << '"' << arg << "\" "; } // DEBUG
   * cout << '\n'; // DEBUG
   */

  enum cmd_ops { DESC_OP = 1, DIE_OP, DANCE_OP, GET_OP, GO_OP, LOOK_OP, TALK_OP, GIVE_OP, SMELL_OP };

  unordered_map<string, int> cmd_map = {
    {"help", DESC_OP},
    {"helpeth", DESC_OP},
    {"look", LOOK_OP},
    {"die", DIE_OP},
    {"dance", DANCE_OP},
    {"get", GET_OP},
    {"take", GET_OP},
    {"talk", TALK_OP},
    {"give", GIVE_OP},
    {"smell", SMELL_OP},
    {"sniff", SMELL_OP},
    {"go", GO_OP},
    {"not", GO_OP},
  };
  {
    auto cmd_id = cmd_map[myargs.at(0)];
    if (cmd_id > 1) {
      switch (cmd_id) {
        case DESC_OP:
          desc();
          break;
        case LOOK_OP:
          if (args.size() == 1) {
            desc();
          } else {
            Item *looker = items[myargs.at(1)];
            if (looker) {
              looker->itm_look();
            } else {
              game->sayCmd(LOOK);
            }
          }
          break;
        case DANCE_OP:
          game->sayCmd(DANCE);
          break;
        case GET_OP:
          if (args.size() > 1) {
            Item *getter = items[myargs.at(1)];
            if (getter) {
              getter->itm_get();
            } else {
              game->sayCmd(LOOK);
            }
          } else {
            game->sayCmd(UNKNOWN);
          }
          break;
        case GO_OP:
          if (args.size() > 1) {
            Room *r = valid_rooms[myargs.at(1)];
            if (r) {
              game->room = r;
            } else {
              game->sayCmd(GO);
            }
          } else {
            game->sayCmd(GO);
          }
          break;
        case TALK_OP:
          game->sayCmd(TALK);
          break;
        case GIVE_OP:
          break;
        case SMELL_OP:
          break;
        case DIE_OP:
          game->sayCmd(DIE);
          game->Over();
          break;
        default:
          break;
      }
    } else {
      game->sayCmd(UNKNOWN);
    }
  }
}

void Room::setupRoomMaps(void) { return; }

void Room::enter() { return; }

void Room::desc() {
  game->sayTxt(&room_desc);
}

MainRoom::MainRoom() {
  items["scroll"] = new Scroll();
  items["flask"] = new Flask();

  string room_desc = MAIN_DESC;
}

void MainRoom::setupRoomMaps(void) {
  valid_rooms["north"] = game->rooms.at(NORTH);
  valid_rooms["south"] = game->rooms.at(SOUTH);
  valid_rooms["dennis"] = game->rooms.at(DENNIS);
}

NorthRoom::NorthRoom() {
  items["parapets"] = new Parapets();
  items["rope"] = new Rope();

  string room_desc = N_DESC;

}

void NorthRoom::setupRoomMaps(void) {
  valid_rooms["south"] = game->rooms.at(MAIN_ROOM);
}

SouthRoom::SouthRoom() {
  items["trinket"] = new Trinket();

  string room_desc = S_DESC;

  lookies[0] = S_LOOK_HELP;
  lookies[1] = S_LOOK_HELP2;
  lookies[2] = S_LOOK_HELP3;
}

void SouthRoom::setupRoomMaps(void) {
  valid_rooms["north"] = game->rooms.at(MAIN_ROOM);
}

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

DennisRoom::DennisRoom() {
  items["jimberjam"] = new Jimberjam();

  string room_desc = DEN_DESC;
}

void DennisRoom::setupRoomMaps(void) {
  valid_rooms["dennis"] = game->rooms.at(MAIN_ROOM);
}
