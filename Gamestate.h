#ifndef TICTACTOE_GAMESTATE_H
#define TICTACTOE_GAMESTATE_H

#include "Action.h"
#include "Agent.h"

typedef struct Node GameState;
struct Node {
  char* gameBoard;
  int numPossMoves;
  Agent* toMove;
};

// Constructors
GameState* emptyGameState(Agent*);
GameState* newGameState(Agent*, char*);
int freeGameState(GameState*);

// Terminal Stuff
int terminalState(GameState*);
int utility(Agent*, GameState*);
char getMarkWinner(GameState*);

// Find the result
GameState* result(GameState*, Action*);

// Minimax
Action* minimaxSearch(GameState*);
int maxValue(GameState*);
int minValue(GameState*);

// Print
void printGameState(GameState*);

#endif
