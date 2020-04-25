#include "Game.hpp"
//#include "Rooms.hpp"
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <regex>

using namespace std;

Game::Game() {
  score = 0;

  sayCmd(TITLE_SCREEN);

  string line = "";
  getline(cin, line);

  sayCmd(INTRO_YOU);
  this_thread::sleep_for(chrono::milliseconds(1300));
  sayCmd(INTRO_ARE);
  this_thread::sleep_for(chrono::milliseconds(1300));
  sayCmd(INTRO_TDM);
}

inline void Game::sayCmd(int cmd) const {
  sayTxt(&txt[cmd]);
}

inline void sayArgs(vector<string> &args) {
  for (auto &arg : args) { cout << arg; }
}

inline void sayArgs(vector<string> &args, int start, int end) {
  for_each(args.begin() + start, args.begin() + end,
           [](auto &argp){ cout << argp << ' '; });
}

inline void Game::sayTxt(const string *_txt) const {
  for (auto &c : *_txt) {
    if (c == '%') {
    } else {
      putchar(c);
    }
  }
  putchar('\n');
}

inline void lc(string *io) {
  transform(io->begin(), io->end(), io->begin(),
            [](unsigned char c){ return tolower(c); });
}
