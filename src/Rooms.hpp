#ifndef ROOMS_HPP
#define ROOMS_HPP

#include "Game.hpp"
#include "Item.hpp"
#include "RoomText.hpp"
#include <functional>
#include <map>
#include <string>

using namespace std;

class Room: public GameWumpus {
  public:
    Room();

    void desc();
    void enter();  // Allows setup of room-entering events

    bool getItem(string key);
    void lookItem(string key);

  protected:
    map<string, Item*> items;
    const string room_desc;
};

// MAIN ROOM
class MainRoom: public Room {
  public:
    using Room::Room;  // Useless use of the word using, thanks C++

  protected:
    map<string, Item*> items = {
      { "scroll", new Scroll() },
      { "flask", new Flask() }
    };
    const string room_desc = MAIN_DESC;
};

// NORTH OF MAIN ROOM
class NorthRoom: public Room {
  public:
    using Room::Room;  // Useless use of the word using, thanks C++

  protected:
    map<string, Item*> items = {
      { "parapets", new Parapets() },
      { "rope", new Rope() }
    };
    const string room_desc = N_DESC;
};

// SOUTH OF MAIN ROOM
class SouthRoom: public Room {
  public:
    using Room::Room;  // Useless use of the word using, thanks C++

    void enter();
    void desc();

  protected:
    map<string, Item*> items = {
      { "trinket", new Trinket() }
    };
    const string room_desc = S_DESC;

    // Special
    bool nonetheless = false;
    const string lookies[3] = { S_LOOK_HELP, S_LOOK_HELP2, S_LOOK_HELP3 };
};

// DENNIS

#endif  // ROOMS_HPP
