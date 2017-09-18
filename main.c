#include <stdio.h>
#include "GameState.h"
#include "Agent.h"
#include "Action.h"

Agent* players[2];
int main(int argc, char* argv[]) {

int playContinue = 1;
int userChosen = 0;
char userMark = '';
int userIndex, compIndex;
//while(playContinue) {
  printf("Would you like to be X or O?");
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
  GameState** games;
  *(games) = newBoard;
  int theMove;
  while(!terminalState(*(games))) {
    int nextMoveIsUser = *(games)->toMove->user;
    if(nextMoveIsUser) {
      theMove = 0;
      userChosen = 0;
      while(!userChosen) {
        scanf("%d", &theMove);
        if(theMove <= 9 && theMove >= 1 &&
           (*(games))->gameBoard[theMove]=='#') {
             *(games+1) = result((*games), newAction(theMove));
        }
        else {

        }
      }
    }
    else {

    }
    games++;
  }
  GameState* next = result(newBoard, newAction(1));
  printf("\n");
  printGameState(next);

  GameState* next2 = result(next, newAction(5));
  printf("\n");
  printGameState(next2);

//}
}
