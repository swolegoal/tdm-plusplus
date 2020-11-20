#ifndef GAME_HPP
#define GAME_HPP

#include "Rooms.hpp"
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class GameWumpus;
class Room;
class Item;
class Trinket;

enum game_txt { TITLE_SCREEN, INTRO_YOU, INTRO_ARE, INTRO_TDM,
  DIE, DANCE, GET, GET_DAGGER, GO, LOOK, UNKNOWN, TALK, GIVE, SMELL, PWD
};

class Game {
  friend void Trinket::itm_give(void);
  friend bool Trinket::itm_get(void);
  friend void Room::parseCmd(vector<string> &args);
  friend void MainRoom::setupRoomMaps(void);
  friend void NorthRoom::setupRoomMaps(void);
  friend void SouthRoom::setupRoomMaps(void);
  friend void DennisRoom::setupRoomMaps(void);

  public:
    Game();
    ~Game();

    inline vector<string> getArgs(const string prompt);
    inline void sayArgs(vector<string> &args) const;
    inline void sayArgs(vector<string> &args, int start) const;
    inline void sayArgs(vector<string> &args, int start, int end) const;
    void sayCmd(int cmd) const;
    void sayCmd(int cmd, vector<string> &args) const;
    void sayTxt(const string *_txt) const;
    void sayTxt(const string *_txt, vector<string> &args) const;
    inline void sayAnA(vector<string> &args) const;
    int getScore() const;

    void uc(string &io);
    void lc(string &io);

    bool play(void);

    void addToScore(int amt);
    void Over();


  private:
    void win(void);

    int score;
    bool over = false;
    bool won = false;
    bool has_trinket = false;
    Trinket *trinket;

    vector<Room *> rooms = {
      new MainRoom(), new NorthRoom(), new SouthRoom(), new DennisRoom()
    };

    Room *room;  // Current room

    const string txt[15] = {
      // Title screen
      " \"#\" # # # #   #\"= # # #\"# #\"\" #\"\" #\"# #\"# #=# #\"# #\"#  .   .\n"
      "  #  #\"#  #    # # # # # # # # #\"\" # # # # # # #\"# # # =#= =#=\n"
      "  \"  \" \"  \"    \"\"  \"\"\" \" \" \"\"\" \"\"\" \"\"\" \" \" \" \" \" \" \" \"  \"   \"\n"
      "\n"
      "                    /\\      /\\      /\\\n"
      "                    ||/----\\||      ||\n"
      "                    \\_------_/      ||\n"
      "                     / o  o \\       ||\n"
      "                     /  ||  \\    o__||__o\n"
      "                     / ---- \\     \\____/\n"
      "                     /\\/\\/\\/\\       ||\n"
      "                                    oo\n"
      "\n"
      "         ~=Press the ENTER key to enter yon dungeon=~\n",
      // Intro sequence
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░  m   m   mmm   m   m  ░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░  \"m m\"  #\" \"#  #   #  ░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░   #m#   #   #  #   #  ░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░   \"#    \"#m#\"  \"mm\"#  ░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░   m\"                  ░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░ \"\"                    ░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░",

      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░   mmm    m mm   mmm   ░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░  \"   #   #\"  \" #\"  #  ░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░  m\"\"\"#   #     #\"\"\"\"  ░░░░░░░░░░░░░░░"
      "\n░░░░░░░░░░░░░░░  \"mm\"#   #     \"#mm\"  ░░░░░░░░░░░░░░░"
      "\n░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░",

      "░░░░░░░░░░░░░░░░░░░░░░\"#\"░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░#░░#░#░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░\"░░#\"#░#░#░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░\"░\"░░#░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\"░░░░░░░░░░░░░░░░░░░░░\n"
      "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n"
      "░#\"=░░░░░#\"#░░░░░#\"\"░░░░░░#\"#░░░░░░░░░░#\"#░░░░░#░"
      "░░#░\n░#░#░#░#░#░#░#\"\"░#\"\"░░#\"#░#░#░░░░░░#=#░#\"#░#\"#░"
      "\"░#░\"░\n░\"\"░░#░#░\"░\"░#░#░\"\"\"░░#░#░\"░\"░░░░░░#░#░\""
      "░\"░#░#░\"░\"░\"░\n░░░░░\"\"\"░░░░░\"\"\"░░░░░░\"\"\"░░░░░░░"
      "░░░\"░\"░░░░░\"░\"░░░\"░░░",
      // General commands
      "That wasn't very smart. Your score was: %s.",

      "Thou shaketh it a little, and it feeleth all right.",

      "Thou cannotst %v that. Quit making stuffeth up!",

      "Yeah, okay",

      "Thou cannotst go there. Who do you think thou art?\n"
      "A magistrate?!",

      "It looketh pretty awesome.",
      "That does not computeth. Type HELP is thou needs of it.",

      "Who is%a? Your new boyfriend? Somebody from work you\n"
      "don't want me to meeteth?",

      "Thou don'tst have %A%a to give. Go back to your\n"
      "tiny life.",

      "You smell a Wumpus.",

      "tuxlovesyou/shameless_ripoffs/videlectrix/Thy\\ Dungeonman++"
    };
};

#endif  // GAME_HPP
