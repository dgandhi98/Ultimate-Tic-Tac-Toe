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
    printf("Would you like to be X or O? Q to quit.\n");
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
      else if(userMark=='q' || userMark=='Q') {
        playContinue = 0;
        userChosen = 1;
      }
      else {
        // bad input
        printf("Bad Input\n");
        while(getchar()!='\n');
        userChosen = 0;
      }
    }
    if(userMark=='q' || userMark=='Q') {
      break;
    }
    compIndex = userIndex ^ (1<<0);
    if(userIndex == 0) {
      players[0] = newAgent(1, 'O');
      players[1] = newAgent(0, 'X');
    }
    else if(userIndex==1) {
      players[0] = newAgent(0, 'O');
      players[1] = newAgent(1, 'X');
    }
    Agent* user = players[userIndex];

    SuperGameState* board1 = emptySuperGameState(players[1]);
    SuperGameState* board2 = NULL;
    printSuperGameState(board1);
    int userMove1;
    int userMove2;
    int nextMoveIsUser;
    // Play Game
    while(!superTerminalState(board1)) {
      nextMoveIsUser = board1->toMove->user;
      //printf("%d\n", nextMoveIsUser);
      if(nextMoveIsUser) {
        userMove1 = 0;
        userMove2 = 0;
        userChosen = 0;
        while(!userChosen) {
          printf("Type 2 numbers for your moves: (1-9) and (1-9). ");
          if(board1->boardToMove!=0) {
            printf("You must move in board %d.\n", (board1)->boardToMove);
          }
          else {
            printf("You can move in any board.\n");
          }
          scanf("%d %d", &userMove1, &userMove2);
          if(userMove1 <= 9 && userMove1 >= 1) {

               if(
                 ((board1)->boardToMove == userMove1 || (board1)->boardToMove == 0)
                 && (board1)->superGameBoard[userMove1]=='#') {

                   if((board1)->games[10*userMove1 + userMove2] == '#' ) {
                     //printf("wassup\n");
                     SuperAction* validAction = newSuperAction(userMove1, userMove2);
                     board2 = superResult((board1),validAction);
                     freeSuperGameState(board1);
                     //free(board1);
                     free(validAction);
                     board1 = board2;
                     userChosen = 1;
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
        SuperAction* compMove = superSearch(board1);
        int compIntMove1 = compMove->superMove;
        int compIntMove2 = compMove->move;
        printf("Computer Moves to %d %d\n", compIntMove1, compIntMove2);
        board2 = superResult(board1, compMove);
        freeSuperGameState(board1);
        board1 = board2;
        //freeSuperGameState(board2);
        free(compMove);
      }
      printSuperGameState(board1);
    }

    // Give Results
    int utilRespectToUser = heuristicEval(user, board1);
    if( utilRespectToUser == 1000) {
      printf("You Won!\n");
    }
    else if(utilRespectToUser==0) {
      printf("Draw!\n");
    }
    else if(utilRespectToUser==-1000) {
      printf("Game Over! Computer Won.\n");
    }
    //freeSuperGameState(board1);
    freeSuperGameState(board2);
    free(players[0]);
    free(players[1]);
    while(getchar()!='\n');

  }
  }
  else if(argc==1) {

  while(playContinue) {
    // Setup players
    printf("Would you like to be X or O? Q to quit.\n");
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
      else if(userMark=='q' || userMark=='Q') {
        playContinue = 0;
        userChosen = 1;
      }
      else {
        // bad input
        printf("Bad Input\n");
        while(getchar()!='\n');
        userChosen = 0;
      }
    }
    if(userMark=='q' || userMark=='Q') {
      break;
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
    //Agent* comp = players[compIndex];
    Agent* user = players[userIndex];


    GameState* board1 = emptyGameState(players[1]);
    GameState* board2 = NULL;
    printGameState(board1);
    //GameState** games = malloc(10*sizeof(GameState*));
    //*(games) = newBoard;
    int userMove;
    int nextMoveIsUser;
    // Play Game
    while(!terminalState(board1)) {
      nextMoveIsUser = (board1)->toMove->user;
      //printf("%d\n", nextMoveIsUser);
      if(nextMoveIsUser) {
        userMove = 0;
        userChosen = 0;
        while(!userChosen) {
          printf("Type your move (1-9)\n");
          scanf("%d", &userMove);
          if(userMove <= 9 && userMove >= 1 &&
             (board1)->gameBoard[userMove]=='#') {
               Action* userMoveAct = newAction(userMove);
               board2 = result((board1), userMoveAct);
               freeGameState(board1);
               board1 = board2;
               free(userMoveAct);
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
        Action* compMove = minimaxSearch(board1);
        int compIntMove = compMove->move;
        if(compIntMove <= 9 && compIntMove >= 1 &&
           board1->gameBoard[compIntMove]=='#') {
             printf("Computer Moves to %d\n", compIntMove);
             board2 = result((board1), compMove);
             freeGameState(board1);
             board1 = board2;
             free(compMove);
        }
        else {
          printf("Computer Broke...\n");
          return 0;
        }
      }
      printGameState(board1);
    }

    // Give Results
    int utilRespectToUser = utility(user, board1);
    if( utilRespectToUser == 1) {
      printf("You Won!\n");
    }
    else if(utilRespectToUser==0) {
      printf("Draw!\n");
    }
    else if(utilRespectToUser==-1) {
      printf("Game Over! Computer Won.\n");
    }
    freeGameState(board2);
    free(players[0]);
    free(players[1]);
    while(getchar()!='\n');

  }
  }
  return 0;
}
