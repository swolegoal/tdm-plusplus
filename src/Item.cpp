#include "Game.hpp"
#include "Item.hpp"
#include "Rooms.hpp"
#include "ItemText.hpp"
#include <string>
#include <vector>

using namespace std;

Item::Item() { return; }

bool Item::getOof() const { return oof; }

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

void Item::itm_give(void) { game->sayCmd(UNKNOWN); }

void Item::itm_look(void) {
  game->sayTxt(&look_txt[look_idx]);

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
  int score_mod_amt = 0;

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
  {
    int txt_idx = 0;

    switch (get_idx) {
      case 0:
      case 1:
        txt_idx = 0;
        get_idx++;
        game->addToScore(1);
        break;
      case 2:
        txt_idx = 1;
        game->Over();
        game->addToScore(-1000);
        break;
      default:
        game->sayCmd(GET);
        break;
    }
    game->sayTxt(&get_txt[txt_idx]);
  }
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
  game->addToScore(-1);
  game->sayTxt(&get_txt[get_idx]);
  game->Over();

  return false;
}

// Trinket
Trinket::Trinket() {
  get_txt.push_back(S_GET_TRINKT);
  get_txt.push_back(S_GET_GOT_TRINKT);

  look_txt.push_back(S_LOOK_TRINKT);
  look_txt.push_back(S_LOOK_GOT_TRINKT);
}

void Trinket::itm_give(void) {
  if (game->room == game->rooms.at(DENNIS)) {
    string give_txt = DEN_GIVE_TKT;
    game->sayTxt(&give_txt);
    game->win();
    game->Over();
  } else {
    game->sayCmd(UNKNOWN);
  }
}

void Trinket::itm_look(void) { game->sayTxt(&get_txt[get_idx]); }

bool Trinket::itm_get(void) {
  bool got = false;
  int score_mod_amt = 0;

  game->sayTxt(&get_txt[get_idx]);

  switch (get_idx) {
    case 0:
      get_idx++;
      look_idx++;
      score_mod_amt = 2;
      game->has_trinket = true;
      game->trinket = this;
      got = true;
      break;
    case 1:
      score_mod_amt = -1;
      oof = true;
      break;
    default:
      game->sayCmd(GET);
      score_mod_amt = 0;
      return false;
      break;
  }
  game->addToScore(score_mod_amt);
  return got;
}

// Jimberjam
Jimberjam::Jimberjam() { look_txt.push_back(DEN_LOOK_JIM); }

bool Jimberjam::itm_get(void) { game->sayCmd(GET); return false; }

void Jimberjam::itm_look(void) { game->sayTxt(&look_txt[look_idx]); }
