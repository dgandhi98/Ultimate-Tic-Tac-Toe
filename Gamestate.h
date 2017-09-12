#ifndef TICTACTOE_GAMESTATE_H
#define TICTACTOE_GAMESTATE_H

typedef Node GameState;
struct Node {
  char* gameBoard;
  int numPossMoves;
  Agent* toMove;
  GameState* child;
};

GameState* emptyGameState();
GameState* newGameState(char*);

int terminalState(GameState*);

int utility(GameState*);

GameState* result(GameState*, Action*);

Action* minimaxSearch(GameState*);

int maxValue(GameState*);
int minValue(GameState*);

#endif
