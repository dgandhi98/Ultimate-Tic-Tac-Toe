#ifndef TICTACTOE_ACTION_H
#define TICTACTOE_ACTION_H

typedef Agent Agent;
struct Agent {
  int user;
  char mark;
};

Agent* newAgent(int, char);

#endif
