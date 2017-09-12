#
# File: Makefile
# Creator: George Ferguson
# Created: Mon Nov 28 13:52:02 2016
# Time-stamp: <Mon Nov 28 14:31:03 EST 2016 ferguson>
# Edited by: Divyanshu Gandhi
# Edited: 9/11/17
#
CC = gcc
SRCS = Agent.c Action.c GameState.c main.c
HDRS = Agent.h Action.h GameState.h
OBJS = $(SRCS:.c=.o)
EXE = ttt

$(EXE): $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	-rm $(OBJS) $(EXE)
