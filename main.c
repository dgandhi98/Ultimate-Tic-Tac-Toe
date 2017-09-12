#include <stdio.h>
#include "GameState.h"
#include "Agent.h"
#include "Action.h"
int main(int argc, char* argv[]) {
  Agent* user = newAgent(1, 'X');
  Agent* comp = newAgent(0, 'O');
  GameState* newBoard = emptyGameState(user);
  printGameState(newBoard);

  Action* firstMove = newAction(1);
  GameState* next = result(newBoard, firstMove);
  printf("\n");
  printGameState(next);

  Action* tMove = newAction(5);
  GameState* next2 = result(next, tMove);
  printf("\n");
  printGameState(next2);

}
