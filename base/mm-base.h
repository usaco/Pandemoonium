#pragma once

#define READ 0
#define WRITE 1

#define RUNNING 0
#define ERROR -1

extern unsigned int starting_money;
extern unsigned int xrange;

struct agent_t
{
	char name[256];       // bot name
	unsigned int milk;   // how much milk does this player have?
	unsigned int loc;     // where was this agent last seen?

// META:
	int status;           // bot's current status
	int fds[2];           // file descriptors to communicate
	int pid;              // process id of agent
	int timeout;          // amount of time given to respond

// VISUALIZATION:
	void* vis;            // data for visualisation
};

