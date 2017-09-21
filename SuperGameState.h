#ifndef TICTACTOE_SUPERGAMESTATE_H
#define TICTACTOE_SUPERGAMESTATE_H

#include "Action.h"
#include "Agent.h"
#include "SuperAction.h"

typedef struct SuperNode SuperGameState;
struct SuperNode {
  char* superGameBoard;
  char* games;
  int numPossMoves;
  int boardToMove;
  Agent* toMove;
  int* numPossMovesPerBoard;
};

// Constructors
SuperGameState* emptySuperGameState(Agent*);
SuperGameState* newSuperGameState(Agent*, SuperGameState*);

// Terminal Stuff
// TerminalState can be shared with old one if using single board
int superTerminalState(SuperGameState*);
// utility will be based on heuristic now
// int heuristic(Agent*, GameState);
// can be shared with other one if single board is terminal
char getSuperMarkWinner(char*);

// Find the result
SuperGameState* superResult(SuperGameState*, SuperAction*);

// Searching
SuperAction* superSearch(SuperGameState*);
//int maxValue(SuperGameState*);
//int minValue(SuperGameState*);

// Print
void printSuperGameState(SuperGameState*);

#endif
