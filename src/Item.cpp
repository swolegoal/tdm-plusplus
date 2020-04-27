#include "Game.hpp"
#include "Item.hpp"
#include "Rooms.hpp"
#include "ItemText.hpp"
#include <cstdarg>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Item::Item() { return; }

// Delet dis
Item::Item(const string item_fmt, ...) {
  va_list fmt_args;
  va_start(fmt_args, item_fmt);

  {
    int counter = 0;
    for (const char &fc : item_fmt) {
      switch (fc) {
        // Key for a "non-got" get message
        case 'g': {
          get_txt.push_back(va_arg(fmt_args, string));
          break;
        }
        // Key for a "got" get message
        // expects an integer of the amount to add to your score
        case 'G': {
          got_idx = counter;
          get_txt.push_back(va_arg(fmt_args, string));
          got_amt = va_arg(fmt_args, int);
          break;
        }
        // Key for a "got" get that kills you;
        // expects an integer of the amount to add to your score
        case 'K': {
          got_idx = counter;
          kill_idx = counter;
          get_txt.push_back(va_arg(fmt_args, string));
          kill_amt = va_arg(fmt_args, int);
          break;
        }
        // Key for a "non-got" get that adds to your score;
        // expects an integer of the amount to add to your score
        case 's': {
          score_mod_idx = counter;
          get_txt.push_back(va_arg(fmt_args, string));
          score_mod_amt = va_arg(fmt_args, int);
          break;
        }
        /* Key for look type flag (int)
         * 0: simple (go through each look string without a care in the world)
         * 1: got-based (iterator starts once item is gotten)
         */
        case 'L': {
          look_txt.push_back(va_arg(fmt_args, string));
          break;
        }
        // Key for look string
        case 'l': {
          look_txt.push_back(va_arg(fmt_args, string));
          break;
        }
      }
      counter++;
    }
  }
  va_end(fmt_args);
}

int Item::getIdx(char ikey) const {
  switch (ikey) {
    case 'g':
      return get_idx;
      break;
    case 'l':
      return look_idx;
      break;
  }
  return -1;
}

bool Item::itm_get(void) {
  bool got = (get_idx == got_idx) ? true : false;

  cout << get_txt.at(get_idx) << '\n';

  if (get_idx == kill_idx) {
      game->addToScore(kill_amt);
      game->Over();  // Sets the game over flag
  } else if (get_idx == score_mod_idx) {
      game->addToScore(score_mod_amt);
  }

  if ((get_idx + 1) < get_txt.size())
    get_idx++;

  return got;
}

void Item::itm_look(void) {
  cout << look_txt.at(look_idx) << '\n';

  if ((look_idx + 1) < look_txt.size())
    look_idx++;
}

// Scroll
Scroll::Scroll() {
  get_txt.push_back(MAIN_GOT_SCROLL);
  get_txt.push_back(MAIN_GET_GOT_SCROLL);

  look_txt.push_back(MAIN_LOOK_SCROLL);
  look_txt.push_back(MAIN_LOOK_GOT_SCROLL);
}

bool Scroll::itm_get(void) {
  game->sayTxt(&get_txt[get_idx]);

  switch (get_idx) {
    case 0:
      zap = true;
      score_mod_amt = 2;
      get_idx++;
      break;
    case 1:
      score_mod_amt = -1;
      break;
    default:
      game->sayCmd(GET);
      return false;
      break;
  }
  game->addToScore(score_mod_amt);
  return false;
}

void Scroll::itm_look(void) {
  look_idx = zap ? 1 : 0;
  game->sayTxt(&look_txt[look_idx]);
}

// Flask
Flask::Flask() {
  get_txt.push_back(MAIN_GET_FLASK);
  get_txt.push_back(MAIN_GOT_FLASK);

  look_txt.push_back(MAIN_LOOK_FLASK);
}

bool Flask::itm_get(void) {
  switch (get_idx) {
    case 2:
      game->Over();
      score_mod_amt = -1000;
    default:
      game->sayCmd(GET);
      return false;
      break;
  }
  game->sayTxt(&get_txt[get_idx]);
  game->addToScore(score_mod_amt);
  return false;
}

void Flask::itm_look(void) { game->sayTxt(&look_txt[look_idx]); }

// Parapets
Parapets::Parapets() { look_txt.push_back(N_LOOK_PARA); }

void Parapets::itm_look(void) { game->sayTxt(&look_txt[look_idx]); }

bool Parapets::itm_get(void) {
  game->sayCmd(GET);
  return false;
}

// Rope
Rope::Rope() {
  get_txt.push_back(N_GET_ROPE);
  look_txt.push_back(N_LOOK_ROPE);
}

void Rope::itm_look(void) { game->sayTxt(&look_txt[look_idx]); }

bool Rope::itm_get(void) {
  score_mod_amt = -1;
  game->sayTxt(&get_txt[get_idx]);
  game->addToScore(score_mod_amt);

  return false;
}

// Trinket
Trinket::Trinket() {
  get_txt.push_back(S_GET_TRINKT);
  get_txt.push_back(S_GET_GOT_TRINKT);

  look_txt.push_back(S_LOOK_TRINKT);
  look_txt.push_back(S_LOOK_GOT_TRINKT);
}

bool Item::getOof() const { return oof; }

bool Trinket::itm_get(void) {
  bool got = false;
  switch (get_idx) {
    case 0:
      get_idx++;
      look_idx++;
      score_mod_amt = 2;
      got = true;
    case 1:
      score_mod_amt = -1;
    default:
      game->sayCmd(GET);
      score_mod_amt = 0;
      return false;
      break;
  }
  game->sayTxt(&get_txt[get_idx]);
  game->addToScore(score_mod_amt);
  return got;
}

void Trinket::itm_look(void) { game->sayTxt(&look_txt[look_idx]); }
