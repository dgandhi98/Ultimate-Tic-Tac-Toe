#ifndef TICTACTOE_SUPERACTION_H
#define TICTACTOE_SUPERACTION_H

struct SuperAction {
  int superMove;
  int move;
};
typedef struct SuperAction SuperAction;

// Constructor
SuperAction* newSuperAction(int, int);

#endif
