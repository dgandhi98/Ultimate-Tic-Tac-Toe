#ifndef TICTACTOE_GAMESTATE_H
#define TICTACTOE_GAMESTATE_H

typedef Node GameState;
struct Node {
  char* gameBoard;
  int numPossMoves;
  Agent* toMove;
  GameState* child;
};

// Constructors
GameState* emptyGameState();
GameState* newGameState(char*);

// Terminal Stuff
int terminalState(GameState*);
int utility(GameState*);

// Find the result
GameState* result(GameState*, Action*);

// Minimax
Action* minimaxSearch(GameState*);
int maxValue(GameState*);
int minValue(GameState*);

#endif
