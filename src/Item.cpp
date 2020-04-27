#include "Game.hpp"
#include "Item.hpp"
#include "Rooms.hpp"
#include "RoomText.hpp"
#include <cstdarg>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Item::Item() { return; }
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

Scroll::Scroll() {
  get_txt.push_back(MAIN_GOT_SCROLL);
  get_txt.push_back(MAIN_GET_GOT_SCROLL);

  look_txt.push_back(MAIN_LOOK_SCROLL);
  look_txt.push_back(MAIN_LOOK_GOT_SCROLL);
}

bool Scroll::itm_get(void) {
  switch (get_idx) {
    case 0:
      zap = true;
      get_idx++;
      break;
    default:
      game->sayCmd(GET);
      break;
  }
  game->sayTxt(&get_txt[get_idx]);
  return false;
}


void Scroll::itm_look(void) {
  look_idx = zap ? 1 : 0;
  game->sayTxt(&look_txt[get_idx]);
}
