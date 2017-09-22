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
  int playContinue = 1;
  int userChosen = 0;
  char userMark;
  if(argc==2 && argv[1][0]=='u' && argv[1][1]=='l' && argv[1][2]=='t'
&& argv[1][3]=='i' && argv[1][4]=='m' && argv[1][5]=='a'
&& argv[1][6]=='t' && argv[1][7]=='e') {
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
        while(getchar()!='\n');
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
    SuperGameState** sGames = malloc(2*sizeof(SuperGameState*));
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
          printf("Type 2 numbers for your moves: (1-9) and (1-9). ");
          if((*(sGames))->boardToMove!=0) {
            printf("You must move in board %d.\n", (*(sGames))->boardToMove);
          }
          else {
            printf("You can move in any board.\n");
          }
          scanf("%d %d", &userMove1, &userMove2);
          if(userMove1 <= 9 && userMove1 >= 1) {

               if(
                 ((*(sGames))->boardToMove == userMove1 || (*(sGames))->boardToMove == 0)
                 && (*(sGames))->superGameBoard[userMove1]=='#') {

                   if((*(sGames))->games[10*userMove1 + userMove2] == '#' ) {
                     //printf("wassup\n");
                     SuperAction* validAction = newSuperAction(userMove1, userMove2);
                     *(sGames+1) = superResult((*sGames),validAction);
                     freeSuperGameState(*(sGames));
                     *(sGames) = *(sGames+1);
                     userChosen = 1;
                     //free(validAction);
                   }
                   else {
                     printf("Move %d isn't available in board %d\n",userMove2,
                      userMove1);
                     userChosen = 0;
                   }
             }
             else {
               printf("Can't move in board %d\n", userMove1);
               userChosen = 0;
             }
          }
          else {
            //bad input
            printf("Bad Input\n");
            while(getchar()!='\n');
            userChosen = 0;
          }
        }
      }
      else {
        printf("computer searching...\n");
        SuperAction* compMove = superSearch(*(sGames));
        int compIntMove1 = compMove->superMove;
        int compIntMove2 = compMove->move;
        printf("Computer Moves to %d %d\n", compIntMove1, compIntMove2);
        *(sGames+1) = superResult((*sGames), compMove);
        freeSuperGameState(*(sGames));
        *(sGames) = *(sGames+1);
        free(compMove);
      }
      //sGames++;
      printSuperGameState(*(sGames));
    }

    // Give Results
    int utilRespectToUser = heuristicEval(user, *(sGames));
    if( utilRespectToUser == 1000) {
      printf("You Won!\n");
    }
    else if(utilRespectToUser==0) {
      printf("Draw!\n");
    }
    else if(utilRespectToUser==-1000) {
      printf("Game Over! Computer Won.\n");
    }
    freeSuperGameState(*(sGames));
    free(players[0]);
    free(players[1]);
    while(getchar()!='\n');

  }
  }
  else if(argc==1) {

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
        while(getchar()!='\n');
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

  }

  free(players);


}
