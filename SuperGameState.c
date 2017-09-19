#include <stdio.h>
#include <stdlib.h>
#include "SuperAction.h"
#include "SuperGameState.h"
#include "GameState.h"
#include "Action.h"
#include "Agent.h"
#include "main.h"

SuperGameState* emptySuperGameState(Agent* a) {
  SuperGameState* sgs = malloc(sizeof(SuperGameState));
  sgs->superGameBoard = malloc(10*sizeof(char));
  for(int i = 1; i <= 9; i++) {
    sgs->superGameBoard[i] = '#';
  }
  sgs->games = malloc(100*sizeof(char));
  for(int i = 1; i <= 9; i++) {
    for(int j = 1; j <= 9; j++) {
      sgs->games[i*10+j] = '#';
    }
  }
  sgs->numPossMoves = 81; // 9*9
  sgs->toMove = a;
  sgs->boardToMove = 0;
  return sgs;
}
SuperGameState* newSuperGameState(Agent* a, SuperGameState* tocpy) {
  //need to make copies
  char* superBoard = tocpy->superGameBoard;
  char* boards = tocpy->games;

  SuperGameState* sgs = malloc(sizeof(SuperGameState));
  sgs->superGameBoard = malloc(10* sizeof(char));
  for(int i = 1; i <= 9;i++) {
    sgs->superGameBoard[i] = superBoard[i];
  }
  sgs->games = malloc(100*sizeof(char));
  for(int i = 1; i<=9; i++) {
    for(int j = 1; j <= 9; j++) {
      sgs->games[i*10+j] = boards[i*10+j];
    }
  }
  sgs->toMove = a;
  sgs->numPossMoves = tocpy->numPossMoves;
  sgs->boardToMove = tocpy->boardToMove;
  return sgs;
}
SuperGameState* superResult(SuperGameState* sgs, SuperAction* sAct) {
  // In Main, have to check if the move is legal--
  //check if that board isnt finished,
  // and check if are moving into sgs->boardToMove
  if(sgs->superGameBoard[sAct->superMove]=='#') {
    if(sgs->boardToMove == sAct->superMove || sgs->boardToMove==0) {
      SuperGameState* newSGS = newSuperGameState(toggleAgent(sgs->toMove), sgs);
      newSGS->games[10*(sAct->superMove)+(sAct->move)] = sgs->toMove->mark;
      newSGS->numPossMoves--;
      return newSGS;
    }
  }
  return sgs;

}

// Print
/*
+---+---+---++++---+---+---++++---+---+---+
| # | # | # |++| # | # | # |++| # | # | # |
----|---|----++----|---|----++----|---|----
| # | # | # |++| # | # | # |++| # | # | # |
----|---|----++----|---|----++----|---|----
| # | # | # |++| # | # | # |++| # | # | # |
+---+---+---++++---+---+---++++---+---+---+
+++++++++++++++++++++++++++*+++++++++++++++
*/
void printSuperGameState(SuperGameState* sgs) {
  char* superBoard = sgs->superGameBoard;
  char* boards = sgs->games;
  printf("+---+---+---++++---+---+---++++---+---+---+\n");
  for(int i = 1; i <= 3; i++) {
    for(int k = 1; k<=3;k++) {
      for(int j = 1; j <= 3; j++) {
        if(superBoard[i*j]=='#') {
          printf("| %c | %c | %c |",boards[10*(i*j)+1*k],boards[10*(i*j)+2*k],
          boards[10*(i*j)+3*k]);
        }
        else {
          printf("|");
          for(int i = 0; i < 11; i++) {
            printf("%c", superBoard[i*j]);
          }
          printf("|");
        }
        if(j!=3) {
          printf("++");
        }
        else {
          printf("\n");
        }
      }
      if(k!=3) {
        printf("----|---|----++----|---|----++----|---|----\n");
      }
    }
    if(i!=3) {
      printf("+++++++++++++++++++++++++++++++++++++++++++\n");
      printf("+++++++++++++++++++++++++++++++++++++++++++\n");
    }
    else {
      printf("+---+---+---++++---+---+---++++---+---+---+\n");
    }
  }

}
