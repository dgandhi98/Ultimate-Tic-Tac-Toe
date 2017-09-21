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
  /*players[0] = newAgent(0, 'O');
  players[1] = newAgent(1, 'X');
  SuperGameState* sgs1 = emptySuperGameState(players[1]);
  printSuperGameState(sgs1);
  printf("\n");
  SuperAction* sAct1 = newSuperAction(5, 5);
  SuperGameState* sgs2 = superResult(sgs1, sAct1);
  printSuperGameState(sgs2);
  printf("\n");
  SuperAction* sAct2 = newSuperAction(5, 1);
  SuperGameState* sgs3 = superResult(sgs2, sAct2);
  printSuperGameState(sgs3);
  printf("\n");
  SuperAction* sAct3 = newSuperAction(1, 5);
  SuperGameState* sgs4 = superResult(sgs3, sAct3);
  printSuperGameState(sgs4);
*/
  int playContinue = 1;
  int userChosen = 0;
  char userMark;
  /*while(playContinue) {
    // Setup players
    printf("Would you like to be X or O?\n");
    userChosen = 0;
    while(!userChosen) {
      while(getchar()!='\n');
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

  }
  */

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


    SuperGameState* newBoard = emptySuperGameState(players[1]);
    printSuperGameState(newBoard);
    SuperGameState** sGames = malloc(10*sizeof(SuperGameState*));
    *(sGames) = newBoard;
    int userMove1;
    int userMove2;
    int nextMoveIsUser;
    // Play Game
    while(!superTerminalState(*(sGames))) {
      nextMoveIsUser = (*(sGames))->toMove->user;
      //printf("%d\n", nextMoveIsUser);
      if(nextMoveIsUser) {
        userMove1 = 0;
        userMove2 = 0;
        userChosen = 0;
        while(!userChosen) {
          printf("Type 2 numbers for your moves (1-9) and (1-9)\n");
          scanf("%d %d", &userMove1, &userMove2);
          if(userMove1 <= 9 && userMove1 >= 1 &&
            (*(sGames))->superGameBoard[userMove1]=='#') {
               if((*(sGames))->boardToMove == userMove1
                 || (*(sGames))->boardToMove==0) {
                   if((*(sGames))->games[10*userMove1 + userMove2] == '#' ) {
                     *(sGames+1) = superResult((*sGames),
                     newSuperAction(userMove1, userMove2));
                     userChosen = 1;
                }
                else {
                  printf("Not Available in move");
                }
             }
             else {
               printf("Bad Input");
             }
          }
          else {
            //bad input
            printf("Bad Input. Not Available in super moves\n");
            userChosen = 0;
          }
        }
      }
      else {
        SuperAction* compMove = superSearch(*(sGames));
        int compIntMove1 = compMove->superMove;
        int compIntMove2 = compMove->move;
        printf("Computer Moves to %d %d\n", compIntMove1, compIntMove2);
        *(sGames+1) = superResult((*sGames), compMove);
      }
      sGames++;
      printSuperGameState(*(sGames));
    }
    while(getchar()!='\n');
/*
    // Give Results
    int utilRespectToUser = utility(user, *(sGames));
    if( utilRespectToUser == 1) {
      printf("You Won!\n");
    }
    else if(utilRespectToUser==0) {
      printf("Draw!\n");
    }
    else if(utilRespectToUser==-1) {
      printf("Game Over! Computer Won.\n");
    }
*/
  }

}
