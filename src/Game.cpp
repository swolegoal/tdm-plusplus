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
  this_thread::sleep_for(chrono::milliseconds(1500));
  sayCmd(INTRO_TDM);

  for (Room *r : rooms) {
    r->gg(this);
  }
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
        // case ('s'):
        //   break;
      }
    } else {
      putchar(*c);
    }
  }
  putchar('\n');
}

inline void Game::lc(string *io) {
  transform(io->begin(), io->end(), io->begin(),
            [](unsigned char c){ return tolower(c); });
}

void Game::Over() { over = true; }

void Game::addToScore(int amt) { score += amt; }

void GameWumpus::gg(Game *g) { game = g; }
