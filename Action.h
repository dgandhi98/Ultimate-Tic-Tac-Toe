#ifndef TICTACTOE_ACTION_H
#define TICTACTOE_ACTION_H

typedef Action Action;
struct Action {
  int move;
};

//Constructors
Action* newAction(int);

#endif
