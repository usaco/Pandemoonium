#pragma once

#define MAXPLAYERS 16
#define MAXCOWS 100

// player information
struct player_data
{
	unsigned int id;

	// information about the player
	unsigned int milk;
	int loc;
};

// my bot's data
extern struct player_data SELF;

extern unsigned int NUMCOWS, NUMROUNDS;
extern unsigned int *MILKVALUES;

// file descriptors
extern int _fdout, _fdin;

