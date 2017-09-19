#include <stdlib.h>
#include "SuperAction.h"

SuperAction* newSuperAction (int superMove, int move) {
  SuperAction* a = malloc(sizeof(SuperAction));
  a->superMove = superMove;
  a->move = move;
  return a;
}
