#include <stdlib.h>
#include "Action.h"

Action* newAction (int move) {
  Action* a = malloc(sizeof(Action));
  a->move = move;
  return a;
}
