#include "Game.hpp"
#include "Rooms.hpp"
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdio>
#include <iostream>
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
  }
}

void Game::win(void) { won = true; }

inline vector<string> Game::getArgs(const string prompt) {
  vector<string> args;
  string line = "";

  while (line.length() == 0) {
    cout << prompt;
    getline(cin, line);

    if (cin.eof()) {
      cout << endl;
      exit(0);
    } else if (cin.bad()) {
      cout << endl;
      exit(1);
    }
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
    enum yes_no { YES = 1, NO };
    unordered_map<string, int> yn_map = {
      {"y", YES},
      {"ye", YES},
      {"yes", YES},
      {"n", NO},
      {"no", NO},
    };
    while (true) {
      vector<string> args = getArgs("Play again? [Y/N] ");
      for (string &arg : args) { lc(arg); }
      if (args.size() > 0) {
        int yn = yn_map[args.at(0)];
        if (yn && args.size() > 0) {
          switch (yn) {
            case YES:
              return true;
            case NO:
              return false;
          }
        }
      }
    }
  }

  return false;
}

int Game::getScore() const { return score; }

void Game::sayCmd(int cmd) const {
  sayTxt(&txt[cmd]);
}

void Game::sayCmd(int cmd, vector<string> &args) const {
  sayTxt(&txt[cmd], args);
}

inline void Game::sayArgs(vector<string> &args) const {
  for (auto &arg : args) { cout << arg; }
}

inline void Game::sayArgs(vector<string> &args, int start, int end) const {
  for_each(args.begin() + start, args.begin() + end,
           [](string &argp){ cout << argp << ' '; });
}

inline void Game::sayArgs(vector<string> &args, int start) const {
  for_each(args.begin() + start, args.end(),
           [](string &argp){ cout << ' ' << argp; });
}

void Game::sayTxt(const string *_txt) const {
  vector<string> args = { "", "" };
  sayTxt(_txt, args);
}

inline void Game::sayAnA(vector<string> &args) const {
  char cons_vowel = args.at(1).at(0);
  switch (cons_vowel) {
    case 'a': case 'A':
    case 'e': case 'E':
    case 'i': case 'I':
    case 'o': case 'O':
    case 'u': case 'U':
      cout << "an";
      return;
  }
  cout << 'a';
}

void Game::sayTxt(const string *_txt, vector<string> &args) const {
  for (auto c = _txt->begin(); c != _txt->end(); ++c) {
    if (*c == '%') {
      switch (*++c) {
        case ('%'):
          cout << '%';
          break;
        case ('s'):
          cout << score;
          break;
        case ('A'):
          sayAnA(args);
          break;
        case ('a'):
          sayArgs(args, 1);
          break;
        case ('v'): {
          string verb = args.at(0);
          if (verb == "gimme")
            verb = "get";

          cout << verb;
          break;
        }
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
