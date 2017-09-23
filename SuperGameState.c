#include <stdio.h>
#include <stdlib.h>
#include "SuperAction.h"
#include "SuperGameState.h"
#include "Action.h"
#include "Agent.h"
#include "main.h"

SuperGameState* emptySuperGameState(Agent* a) {
  SuperGameState* sgs = malloc(sizeof(SuperGameState));
  sgs->superGameBoard = malloc(10*sizeof(char));
  sgs->numPossMovesPerBoard = malloc(10*sizeof(int));
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
  for(int i = 1; i <= 9; i++) {
    sgs->numPossMovesPerBoard[i] = 9;
  }
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
  sgs->numPossMovesPerBoard = malloc(10*sizeof(int));
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
  for(int i = 1; i <= 9; i++) {
    sgs->numPossMovesPerBoard[i] = tocpy->numPossMovesPerBoard[i];
  }
  sgs->boardToMove = tocpy->boardToMove;
  return sgs;
}

// returns 1 if terminal, else 0
int superTerminalState(SuperGameState* sgs) {
  if(sgs->numPossMoves==0) {
    return 1;
  }
  else {
    char winner = getSuperMarkWinner(sgs->superGameBoard);
    if(winner!='#') {
      return 1;
    }
  }
  return 0;
}

int freeSuperGameState(SuperGameState* sgs) {
  free(sgs->numPossMovesPerBoard);
  free(sgs->games);
  free(sgs->superGameBoard);
  free(sgs);
  return 1;
}

// return the winner
char getSuperMarkWinner(char* board) {
  // check rows
  for(int i = 0; i < 3;i++) {
    if(board[i*3+1]==board[i*3+2]
      && board[i*3+1]==board[i*3+3]
      && board[i*3+1]!='#'
      && board[i*3+1]!='-') {
        return board[i*3+1];
    }
  }
  // check columns
  for(int i = 0; i < 3;i++) {
    if(board[(i+1)]==board[(i+1)+3]
      && board[(i+1)]==board[(i+1)+6]
      && board[i+1]!='#'
      && board[i+1]!='-') {
        return board[(i+1)];
    }
  }
  // check diagonals
  if(board[1]==board[5] &&
     board[1]==board[9]
     && board[1]!='#'
     && board[1]!='-') {
       return board[1];
  }
  if(board[3]==board[5] &&
     board[3]==board[7]
     && board[3]!='#'
     && board[3]!='-') {
       return board[3];
  }
  return '#';
}

SuperGameState* superResult(SuperGameState* sgs, SuperAction* sAct) {
  // In Main, have to check if the move is legal--
  //check if that board isnt finished,
  // and check if are moving into sgs->boardToMove
  if(sgs->superGameBoard[sAct->superMove]=='#') {
    if(sgs->boardToMove == sAct->superMove || sgs->boardToMove==0) {
      SuperGameState* newSGS = newSuperGameState(toggleAgent(sgs->toMove), sgs);
      newSGS->games[10*(sAct->superMove)+(sAct->move)] = sgs->toMove->mark;
      newSGS->numPossMovesPerBoard[sAct->superMove]--;
      newSGS->numPossMoves--;
      char* boardToCheck = malloc(10*sizeof(char));

      for(int i=1; i<=9; i++) {
        boardToCheck[i] = newSGS->games[10*(sAct->superMove)+i];
      }
      if(getSuperMarkWinner(boardToCheck) == '#'
        && newSGS->numPossMovesPerBoard[sAct->superMove] == 0) {
          newSGS->superGameBoard[sAct->superMove] = '-';
      }
      else if(getSuperMarkWinner(boardToCheck) == 'X') {
        newSGS->superGameBoard[sAct->superMove] = 'X';
        newSGS->numPossMoves -= newSGS->numPossMovesPerBoard[sAct->superMove];
        newSGS->numPossMovesPerBoard[sAct->superMove] = 0;
      }
      else if(getSuperMarkWinner(boardToCheck) == 'O') {
        newSGS->superGameBoard[sAct->superMove] = 'O';
        newSGS->numPossMoves -= newSGS->numPossMovesPerBoard[sAct->superMove];
        newSGS->numPossMovesPerBoard[sAct->superMove] = 0;
      }

      if(newSGS->superGameBoard[sAct->move]=='#') {
        newSGS->boardToMove = sAct->move;
      }
      else {
        newSGS->boardToMove = 0;
      }

      free(boardToCheck);

      return newSGS;
    }
  }
  return sgs;
}

SuperAction* superSearch(SuperGameState* sgs) {
  int alp = -2000;
  int bet = 2000;
  int dep = 0;
  SuperAction* currAct = NULL;
  SuperAction* maxAct = NULL;
  SuperGameState* currSGS = NULL;
  int max = -2000;
  if(sgs->boardToMove == 0) {
    for(int i = 1; i <= 9; i++) {
      if(sgs->superGameBoard[i]=='#') {
        for(int j = 1; j <= 9; j++) {
          if(sgs->games[10*i+j]=='#') {
            currAct = newSuperAction(i,j);
            currSGS = superResult(sgs, currAct);
            int newV = superMinValue(currSGS, alp, bet, dep+1);
            if(newV > max) {
              max = newV;
              free(maxAct);
              maxAct = currAct;
            }
            else {
              free(currAct);
            }
            freeSuperGameState(currSGS);
            alp = alp > max ? alp:max;
          }
        }
      }
    }
  }
  else {
    for(int j = 1; j <= 9; j++) {
      if(sgs->games[10*sgs->boardToMove+j]=='#') {
        currAct = newSuperAction(sgs->boardToMove,j);
        currSGS = superResult(sgs, currAct);
        int newV = superMinValue(currSGS, alp, bet, dep+1);
        if(newV > max) {
          max = newV;
          free(maxAct);
          maxAct = currAct;
        }
        else {
          free(currAct);
        }
        freeSuperGameState(currSGS);
        alp = alp > max ? alp:max;
      }
    }
  }
  return maxAct;
}

int cutoffTest(SuperGameState* sgs, int dep) {
  if(superTerminalState(sgs) || dep==3) {
    return 1;
  }
  return 0;
}

int heuristicEval(Agent* a, SuperGameState* sgs) {
  // +1000 if wins entire thing
  // +20*(number of boards won - number of boards lost)
  // +10 if gets to choose any board
  // (not implemented)+5 if gets to use board with no other marks in it
  int h = 0;
  char winner = getSuperMarkWinner(sgs->superGameBoard);
  //draw
  if(sgs->numPossMoves==0 && winner=='#') {
    h = 0;
  }
  // agent won
  else if(winner==a->mark) {
    h = 1000;
  }
  // agent lost
  else if(winner!=a->mark && winner!='#') {
    h = -1000;
  }
  // Not a Terminal Case
  else if(winner=='#') {
    int numWins = 0;
    int numLoss = 0;
    for(int i = 1; i<=9; i++) {
      if(sgs->superGameBoard[i]==a->mark) {
        numWins++;
      }
      else if(sgs->superGameBoard[i]!=a->mark
      && sgs->superGameBoard[i]!='-'
      && sgs->superGameBoard[i]!='#') {
        numLoss++;
      }
      h += 20*(numWins-numLoss);
    }

    if(sgs->toMove==a && sgs->boardToMove==0) {
      h += 10;
    }
    else if(sgs->boardToMove==0) {
      h -= 10;
    }
  }
  //printf("h: %d\n", h);
  return h;
}
int superMaxValue(SuperGameState* sgs, int alp, int bet, int dep) {
  SuperAction* currAct = NULL;
  SuperGameState* currSGS = NULL;
  if(cutoffTest(sgs, dep)) {
    return heuristicEval(players[compIndex], sgs);
  }
  int currV = -2000;
  if(sgs->boardToMove == 0) {
    for(int i = 1; i <= 9; i++) {
      if(sgs->superGameBoard[i]=='#') {
        for(int j = 1; j <= 9; j++) {
          if(sgs->games[10*i+j]=='#') {
            currAct = newSuperAction(i,j);
            currSGS = superResult(sgs, currAct);
            int newV = superMinValue(currSGS, alp, bet, dep+1);
            freeSuperGameState(currSGS);
            free(currAct);
            currV = currV > newV ? currV:newV;
            if(currV >= bet) {
              return currV;
            }
            alp = alp > currV ? alp:currV;
          }
        }
      }
    }
  }
  else {
    for(int j = 1; j <= 9; j++) {
      if(sgs->games[10*sgs->boardToMove+j]=='#') {
        currAct = newSuperAction(sgs->boardToMove,j);
        currSGS = superResult(sgs, currAct);
        int newV = superMinValue(currSGS, alp, bet, dep+1);
        currV = currV > newV ? currV:newV;
        freeSuperGameState(currSGS);
        free(currAct);
        if(currV >= bet) {
          return currV;
        }
        alp = alp > currV ? alp:currV;
      }
    }
  }
  return currV;
}
int superMinValue(SuperGameState* sgs, int alp, int bet, int dep) {
  SuperAction* currAct = NULL;
  SuperGameState* currSGS = NULL;
  if(cutoffTest(sgs, dep)) {
    return heuristicEval(players[compIndex], sgs);
  }

  int currV = 2000;
  if(sgs->boardToMove == 0) {
    for(int i = 1; i <= 9; i++) {
      if(sgs->superGameBoard[i]=='#') {
        for(int j = 1; j <= 9; j++) {
          if(sgs->games[10*i+j]=='#') {
            currAct = newSuperAction(i,j);
            currSGS = superResult(sgs, currAct);
            int newV = superMaxValue(currSGS, alp, bet, dep+1);
            currV = currV < newV ? currV:newV;
            freeSuperGameState(currSGS);
            free(currAct);
            if(currV <= alp) {
              return currV;
            }
            bet = bet < currV ? bet:currV;
          }
        }
      }
    }
  }
  else {
    for(int j = 1; j <= 9; j++) {
      if(sgs->games[10*sgs->boardToMove+j]=='#') {
        currAct = newSuperAction(sgs->boardToMove,j);
        currSGS = superResult(sgs, currAct);
        int newV = superMaxValue(currSGS, alp, bet, dep+1);
        currV = currV < newV ? currV:newV;
        freeSuperGameState(currSGS);
        free(currAct);
        if(currV <= alp) {
          return currV;
        }
        bet = bet < currV ? bet:currV;
      }
    }
  }
  return currV;
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
  for(int i = 1; i <= 9; i++) {
    for(int j = 1; j <= 3; j++) {
      int bdNum = (j+3*((i-1)/3));
      if(superBoard[bdNum]=='#') {
        int one = 10*bdNum+1+((i-1)*3)%9;
        int two = 10*bdNum+2+((i-1)*3)%9;
        int three = 10*bdNum+3+((i-1)*3)%9;
        printf("| %c | %c | %c |",
        boards[one],
        boards[two],
        boards[three]);
      }
      else {
        printf("|");
        for(int k = 0; k < 11; k++) {
          printf("%c", superBoard[bdNum]);
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
    if(i%3!=0 || i==9) {
      printf("----|---|----++----|---|----++----|---|----\n");
    }
    else if(i%3==0 && i!=9){
      printf("+++++++++++++++++++++++++++++++++++++++++++\n");
      printf("+++++++++++++++++++++++++++++++++++++++++++\n");
    }
  }

}
