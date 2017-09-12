#ifndef TICTACTOE_ACTION_H
#define TICTACTOE_ACTION_H


struct Action {
  int move;
};
typedef struct Action Action;

//Constructors
Action* newAction(int);

#endif
