#ifndef ROOMS_HPP
#define ROOMS_HPP

#include "Game.hpp"
#include "Item.hpp"
#include <functional>
#include <string>
#include <unordered_map>

using namespace std;

enum room_key { MAIN_ROOM, NORTH, SOUTH, DENNIS };

class Room: public GameWumpus {
  friend class Game;

  public:
    void setupItemWumpii(void);
    virtual void setupRoomMaps(void);

    virtual void desc();
    virtual void enter();  // Allows setup of room-entering events

    bool getItem(string key);
    void lookItem(string key);

    void parseCmd(vector<string> &args);

  protected:
    unordered_map<string, Item*> items;
    string room_desc;
    //unordered_map<string, int> valid_rooms;
    unordered_map<string, Room*> valid_rooms;
};

// MAIN ROOM
class MainRoom: public Room {
  public:
    MainRoom();
    virtual void setupRoomMaps(void);
};

// NORTH OF MAIN ROOM
class NorthRoom: public Room {
  public:
    NorthRoom();
    virtual void setupRoomMaps(void);
};

// SOUTH OF MAIN ROOM
class SouthRoom: public Room {
  public:
    SouthRoom();
    virtual void setupRoomMaps(void);

    virtual void enter();
    virtual void desc();

  protected:
    bool nonetheless = false;
    string lookies[3];
};

// DENNIS
class DennisRoom: public Room {
  public:
    DennisRoom();
    virtual void setupRoomMaps(void);
};

#endif  // ROOMS_HPP
