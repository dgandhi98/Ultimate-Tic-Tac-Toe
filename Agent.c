#include <stdlib.h>
#include "Agent.h"
#include "main.h"
/*
Global Variables Used: agents
*/

Agent* newAgent (int user, char mark) {
  Agent* a = malloc(sizeof(Agent));
  a->user = user;
  a->mark = mark;
  return a;
}

Agent* toggleAgent (Agent* curr) {
  if(curr->mark=='X') {
    return players[0];
  }
  else if(curr->mark=='O') {
    return players[1];
  }
  return newAgent(0, 'E');
}
