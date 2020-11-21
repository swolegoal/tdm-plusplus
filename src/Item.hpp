#ifndef ITEM_HPP
#define ITEM_HPP

//#include "Game.hpp"
#include "Rooms.hpp"
#include <string>
#include <vector>

using namespace std;

class Game;

class GameWumpus {
  public:
    void gg(Game *);

  protected:
    Game *game;
};

class Item : public GameWumpus {
  public:
    virtual ~Item();

    virtual bool itm_get(void) = 0;
    virtual void itm_look(void);
    virtual void itm_give(void);

    int getIdx(char ikey) const;
    bool getOof() const;

  protected:
    int get_idx = 0;
    int look_idx = 0;

    bool oof = false;

    vector<string> get_txt;
    vector<string> look_txt;
};

// Main dungeon room
class Scroll: public Item {
  public:
    Scroll();

    virtual bool itm_get(void);
    virtual void itm_look(void);
};

class Flask: public Item {
  public:
    Flask();

    virtual bool itm_get(void);
    virtual void itm_look(void);
};

// North of main dungeon room
class Parapets: public Item {
  public:
    Parapets();

    virtual bool itm_get(void);
    virtual void itm_look(void);
};

class Rope: public Item {
  public:
    Rope();

    virtual bool itm_get(void);
    virtual void itm_look(void);
};

// South of main dungeon room
class Trinket: public Item {
  public:
    Trinket();

    virtual bool itm_get(void);
    virtual void itm_look(void);
    virtual void itm_give(void);
};

// Dennis
class Jimberjam: public Item {
  public:
    Jimberjam();

    virtual bool itm_get(void);
    virtual void itm_look(void);
};

#endif  // ITEM_HPP
