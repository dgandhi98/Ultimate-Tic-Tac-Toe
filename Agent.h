#ifndef TICTACTOE_AGENT_H
#define TICTACTOE_AGENT_H

struct Agent {
  int user;
  char mark;
};
typedef struct Agent Agent;
// Constructor
Agent* newAgent(int, char);

// Gets the next Agent
Agent* toggleAgent(Agent*);
#endif
