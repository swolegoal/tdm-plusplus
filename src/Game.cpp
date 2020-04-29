#include "Game.hpp"
//#include "Rooms.hpp"
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>

using namespace std;

Game::Game() {
  score = 0;

  sayCmd(TITLE_SCREEN);

  string line = "";
  getline(cin, line);

  sayCmd(INTRO_YOU);
  this_thread::sleep_for(chrono::milliseconds(1300));
  sayCmd(INTRO_ARE);
  this_thread::sleep_for(chrono::milliseconds(1500));
  sayCmd(INTRO_TDM);

  for (Room *r : rooms) {
    r->gg(this);
    r->setupItemWumpii();
    r->setupRoomMaps();
    /* // Testing code (to delete)
     * for (auto &valid : r->valid_rooms ) {
     *   cout << valid.first << ": " << valid.second << '\n';
     * }
     * for (auto &item: r->items) {
     *   r->lookItem(item.first);
     * }
     */

    r->desc();
    cout << r->room_desc << '\n';
  }
}

void Game::win(void) { won = true; }

inline vector<string> Game::getArgs(const string prompt) {
  vector<string> args;
  string line = "";

  while (line.length() == 0) {
    cout << prompt;
    getline(cin, line);
  }

  istringstream astream(line);
  while (true) {
    string arg;
    if (astream >> arg)
      args.push_back(arg);
    else
      break;
  }
  return args;
}

bool Game::play(void) {
  room = rooms.at(0);
  room->enter();
  room->desc();

  while (!over) {
    vector<string> args = getArgs("\nWhat wouldst thou deau?\n> ");
    room->parseCmd(args);
  }

  if (!won) {
    cout << "here\n";
    enum yes_no { YES = 1, NO };
    unordered_map<string, int> yn_map = {
      {"y", YES},
      {"ye", YES},
      {"yes", YES},
      {"n", NO},
      {"no", NO},
    };
    vector<string> args = getArgs("");
    int yn = yn_map[args.at(0)];
    if (yn) {
      switch (yn) {
        case YES:
          return true;
      }
    }
  }

  return false;
}

void Game::sayCmd(int cmd) const {
  sayTxt(&txt[cmd]);
}

inline void Game::sayArgs(vector<string> &args) const {
  for (auto &arg : args) { cout << arg; }
}

inline void Game::sayArgs(vector<string> &args, int start, int end) const {
  for_each(args.begin() + start, args.begin() + end,
           [](auto &argp){ cout << argp << ' '; });
}

void Game::sayTxt(const string *_txt) const {
  for (auto c = _txt->begin(); c != _txt->end(); ++c) {
    if (*c == '%') {
      switch (*++c) {
        case ('s'):
          cout << score;
          break;
        // case ('a'):
        //   break;
      }
    } else {
      putchar(*c);
    }
  }
  putchar('\n');
}

void Game::lc(string &io) {
  transform(io.begin(), io.end(), io.begin(),
            [](unsigned char c){ return tolower(c); });
}

void Game::Over() { over = true; }

void Game::addToScore(int amt) { score += amt; }

void GameWumpus::gg(Game *g) { game = g; }
