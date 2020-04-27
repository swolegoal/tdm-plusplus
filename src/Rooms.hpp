#ifndef ROOMS_HPP
#define ROOMS_HPP

#include "Game.hpp"
#include "Item.hpp"
#include <functional>
#include <map>
#include <string>

using namespace std;

class Game;

class Room : public GameWumpus {
  public:
    Room();

    bool getItem(string key);
    void lookItem(string key);

  protected:
    map<string, Item*> items;
    //virtual const string txt[];
};


class MainRoom: public Room {
  public:
    using Room::Room;  // Useless use of the word using, thanks C++

  protected:
    map<string, Item*> items = {
      { "scroll", new Scroll() },
      { "flask", new Scroll() }
    };
    enum room_txt { MAIN_DESC, MAIN_L_SCROLL, MAIN_L_FLASK,
                    MAIN_GET_SCROLL, MAIN_GET2_SCROLL, MAIN_LOOK_SCROLL,
                    MAIN_GET_FLASK, MAIN_GET3_FLASK };
    const string txt[8];
};

#endif  // ROOMS_HPP
