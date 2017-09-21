#include <stdio.h>
#include <stdlib.h>
#include "GameState.h"
#include "Action.h"
#include "Agent.h"
#include "main.h"

// creates new initial state
GameState* emptyGameState(Agent* a) {
  GameState* gs = malloc(sizeof(GameState));
  gs->gameBoard = malloc(10*sizeof(char));
  for(int i = 1; i < 10; i++) {
    gs->gameBoard[i] = '#';
  }
  gs->numPossMoves = 9;
  gs->toMove = a;
  return gs;
}

// copies board into a gamestate
GameState* newGameState(Agent* a, char* board) {
  GameState* gs = malloc(sizeof(GameState));
  gs->gameBoard = malloc(10*sizeof(char));
  gs->numPossMoves = 0;
  for(int i = 1; i < 10; i++) {
    gs->gameBoard[i] = board[i];
    if(board[i]=='#') {
      gs->numPossMoves++;
    }
  }
  gs->toMove = a;
  return gs;
}

// returns 1 if terminal, else 0
int terminalState(GameState* gs) {
  if(gs->numPossMoves==0) {
    return 1;
  }
  else {
    char winner = getMarkWinner(gs);
    if(winner!='#') {
      return 1;
    }
  }
  return 0;
}

// returns 1 if win to agent, -1 if loss, 0 if draw
int utility(Agent* a, GameState* gs) {
  char winner = getMarkWinner(gs);
  if(winner!='#') {
    if(winner==a->mark) {
      return 1;
    }
    else {
      return -1;
    }
  }
  return 0;
}

// return the winner
char getMarkWinner(GameState* gs) {
  // check rows
  for(int i = 0; i < 3;i++) {
    if(gs->gameBoard[i*3+1]==gs->gameBoard[i*3+2]
      && gs->gameBoard[i*3+1]==gs->gameBoard[i*3+3]
      && gs->gameBoard[i*3+1]!='#') {
        return gs->gameBoard[i*3+1];
    }
  }
  // check columns
  for(int i = 0; i < 3;i++) {
    if(gs->gameBoard[(i+1)]==gs->gameBoard[(i+1)+3]
      && gs->gameBoard[(i+1)]==gs->gameBoard[(i+1)+6]
      && gs->gameBoard[i+1]!='#') {
        return gs->gameBoard[(i+1)];
    }
  }
  // check diagonals
  if(gs->gameBoard[1]==gs->gameBoard[5] &&
     gs->gameBoard[1]==gs->gameBoard[9]
     && gs->gameBoard[1]!='#') {
       return gs->gameBoard[1];
  }
  if(gs->gameBoard[3]==gs->gameBoard[5] &&
     gs->gameBoard[3]==gs->gameBoard[7]
     && gs->gameBoard[3]!='#') {
       return gs->gameBoard[3];
  }
  return '#';
}

//returns result with given action
GameState* result(GameState* gs, Action* act) {
  GameState* res = newGameState(toggleAgent(gs->toMove), gs->gameBoard);
  res->gameBoard[act->move] = gs->toMove->mark;
  res->numPossMoves--;
  return res;
}

// Minimax
Action* minimaxSearch(GameState* gs) {
  int max = -2; //serves as -inf
  Action* maxAct = newAction(0);
  for(int i = 1; i <= 9; i++) {
    if(gs->gameBoard[i]=='#') {
      Action* currAct = newAction(i);
      GameState* currState = result(gs, currAct);
      int util = minValue(currState);
      if(util > max) {
        max = util;
        free(maxAct);
        maxAct = currAct;
      }
      else {
        free(currAct);
      }
      free(currState->gameBoard);
      free(currState);
    }
  }
  return maxAct;
}
int maxValue(GameState* gs) {
  if(terminalState(gs)) {
    return utility(players[compIndex], gs);
  }
  int v = -2;
  for(int i = 1; i <= 9; i++) {
    if(gs->gameBoard[i]=='#') {
      Action* currAct = newAction(i);
      GameState* currState = result(gs, currAct);
      int currVal = minValue(currState);
      v = v > currVal? v:currVal; // get max
      free(currState->gameBoard);
      free(currState);
      free(currAct);
    }
  }
  return v;
}
int minValue(GameState* gs) {
  if(terminalState(gs)) {
    return utility(players[compIndex], gs);
  }
  int v = 2;
  for(int i = 1; i <= 9; i++) {
    if(gs->gameBoard[i]=='#') {
      Action* currAct = newAction(i);
      GameState* currState = result(gs, currAct);
      int currVal = maxValue(currState);
      v = v > currVal? currVal:v; // get min
      free(currState->gameBoard);
      free(currState);
      free(currAct);
    }
  }
  return v;
}

// Print
/**
+---+---+---+
| # | # | # |
----|---|----
| # | # | # |
----|---|----
| # | # | # |
+---+---+---+
**/
void printGameState(GameState* gs) {
  printf("+---+---+---+\n");
  for(int i = 0; i < 3; i++) {
    printf("| %c | %c | %c |\n", gs->gameBoard[(i*3)+1], gs->gameBoard[(i*3)+2],
      gs->gameBoard[(i*3)+3]);
    if(i!=2) {
      printf("----|---|----\n");
    }
    else {
      printf("+---+---+---+\n");
    }
  }
}
