#include <stdlib.h>
#include "Agent.h"

Agent* newAgent (int user, char mark) {
  Agent* a = malloc(sizeof(Agent));
  a->user = user;
  a->mark = mark;
  return a;
}

Agent* toggleAgent (Agent* curr) {
  Agent* res = malloc(sizeof(Agent));
  res->user = curr->user^(1<<0);
  if(curr->mark=='O') {
    res->mark = 'X';
  }
  else {
    res->mark = 'O';
  }
  return res;
}
