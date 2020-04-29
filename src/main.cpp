#include "Game.hpp"

using namespace std;

int main(void) {
  Game *game;
  bool play_again = true;

  while (play_again) {
    game = new Game();

    play_again = game->play();

    // delete game;
  }

  return 0;
}
