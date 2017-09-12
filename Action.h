#ifndef TICTACTOE_ACTION_H
#define TICTACTOE_ACTION_H

typedef Action Action;
struct Action {
  int move;
};

Action* newAction(int);

#endif
