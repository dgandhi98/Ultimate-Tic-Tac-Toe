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
int freeSuperGameState(SuperGameState*);

// Terminal Stuff
int superTerminalState(SuperGameState*);
char getSuperMarkWinner(char*);

// Find the result
SuperGameState* superResult(SuperGameState*, SuperAction*);

// Searching
SuperAction* superSearch(SuperGameState*);
int cutoffTest(SuperGameState*, int);
int heuristicEval(Agent*, SuperGameState* );
int superMaxValue(SuperGameState*, int, int, int);
int superMinValue(SuperGameState*, int, int, int);

// Print
void printSuperGameState(SuperGameState*);

#endif
