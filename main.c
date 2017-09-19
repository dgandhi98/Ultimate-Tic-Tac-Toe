#include <stdio.h>
#include <stdlib.h>
#include "GameState.h"
#include "SuperGameState.h"
#include "SuperAction.h"
#include "Agent.h"
#include "Action.h"

Agent* players[2];
int userIndex, compIndex;
int main(int argc, char* argv[]) {
  players[0] = newAgent(0, 'O');
  players[1] = newAgent(1, 'X');
  SuperGameState* sgs1 = emptySuperGameState(players[1]);
  printSuperGameState(sgs1);

  /*
  int playContinue = 1;
  int userChosen = 0;
  char userMark;
  while(playContinue) {
    // Setup players
    printf("Would you like to be X or O?\n");
    userChosen = 0;
    while(!userChosen) {
      scanf("%c", &userMark);
      while(getchar()!='\n');
      // O will be index 0
      // X will be index 1
      if(userMark=='o' || userMark=='O') {
        userIndex = 0;
        userChosen = 1;
      }
      else if(userMark=='x' || userMark=='X')  {
        userIndex = 1;
        userChosen = 1;
      }
      else {
        // bad input
        printf("Bad Input\n");
        userChosen = 0;
      }
    }
    compIndex = userIndex ^ (1<<0);
    if(userIndex == 0) {
      players[0] = newAgent(1, 'O');
      players[1] = newAgent(0, 'X');
    }
    else if(userIndex==1){
      players[0] = newAgent(0, 'O');
      players[1] = newAgent(1, 'X');
    }
    Agent* comp = players[compIndex];
    Agent* user = players[userIndex];


    GameState* newBoard = emptyGameState(players[1]);
    printGameState(newBoard);
    GameState** games = malloc(10*sizeof(GameState*));
    *(games) = newBoard;
    int userMove;
    int nextMoveIsUser;
    // Play Game
    while(!terminalState(*(games))) {
      nextMoveIsUser = (*(games))->toMove->user;
      //printf("%d\n", nextMoveIsUser);
      if(nextMoveIsUser) {
        userMove = 0;
        userChosen = 0;
        while(!userChosen) {
          printf("Type your move (1-9)\n");
          scanf("%d", &userMove);
          if(userMove <= 9 && userMove >= 1 &&
             (*(games))->gameBoard[userMove]=='#') {
               *(games+1) = result((*games), newAction(userMove));
               userChosen = 1;
          }
          else {
            //bad input
            printf("Bad Input\n");
            userChosen = 0;
          }
        }
      }
      else {
        Action* compMove = minimaxSearch(*(games));
        int compIntMove = compMove->move;
        if(compIntMove <= 9 && compIntMove >= 1 &&
           (*(games))->gameBoard[compIntMove]=='#') {
             printf("Computer Moves to %d\n", compIntMove);
             *(games+1) = result((*games), compMove);
        }
        else {
          printf("Computer Broke...\n");
          return 0;
        }
      }
      games++;
      printGameState(*(games));
    }

    // Give Results
    int utilRespectToUser = utility(user, *(games));
    if( utilRespectToUser == 1) {
      printf("You Won!\n");
    }
    else if(utilRespectToUser==0) {
      printf("Draw!\n");
    }
    else if(utilRespectToUser==-1) {
      printf("Game Over! Computer Won.\n");
    }
    while(getchar()!='\n');
  }
  */
}
