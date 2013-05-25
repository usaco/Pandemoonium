#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include "mm-client.h"

#define MSG_BFR_SZ 128

// helper macro, sorry for the mess...
#define EXPECTED(m, s) { fprintf(stderr, "[%u] Expected command %s," \
	" received %s.\n", SELF.id, s, m); return EXIT_FAILURE; }
#define copyself() memcpy(&SELF, &players[SELF.id], sizeof SELF)

/* these functions should be defined by the bot author */

extern const char* BOT_NAME;

extern int client_setup(int* /*argc*/, char*** /*argv*/);

extern void game_setup(const struct player_data* /*players*/, 
	unsigned int /*player count*/);

extern int player_turn(unsigned int /*roundnum*/, 
	const struct player_data* /*players*/, unsigned int /*player count*/);

extern void game_end();

// ########################################################

unsigned int NUMPLAYERS = 0;

struct player_data players[MAXPLAYERS];

struct player_data SELF;

unsigned int NUMCOWS, NUMROUNDS;

unsigned int _MILKVALUES[MAXCOWS];
unsigned int *MILKVALUES = _MILKVALUES;

int _fdout = STDOUT_FILENO, _fdin = STDIN_FILENO;

int recv(char* msg)
{
	bzero(msg, MSG_BFR_SZ);

	// read message from file descriptor for a bot
	int bl, br; char* m = msg;
	for (bl = MSG_BFR_SZ; bl > 0; m += br)
		bl -= br = read(_fdin, m, bl);

	return br;
}

int send(char* msg)
{
	// write message to file descriptor for a bot
	int bl, br; char* m = msg;
	for (bl = MSG_BFR_SZ; bl > 0; m += br)
		bl -= br = write(_fdout, m, bl);

	return br;
}

int main(int argc, char **argv)
{
	int i, cc;
	char msg[MSG_BFR_SZ];
	char tag[MSG_BFR_SZ];

	struct player_data *p = NULL;

	--argc; ++argv;
	setbuf(stdout, NULL);
	setbuf(stdin , NULL);
	
	struct timeval tv;
	gettimeofday(&tv, NULL);
	srand(tv.tv_usec);

	if (!client_setup(&argc, &argv))
		return EXIT_FAILURE;

	recv(msg); sscanf(msg, "%*s %d", &SELF.id);
	sprintf(msg, "NAME %s", BOT_NAME); send(msg);

	while ((cc = recv(msg)))
	{
		sscanf(msg, "%s", tag);
		
		if (!strcmp(tag, "READY")) break;
		else if (!strcmp(tag, "PLAYERS"))
		{
			sscanf(msg, "%*s %u", &NUMPLAYERS);
			for (i = 0; i < NUMPLAYERS; ++i)
			{
				players[i].loc = -1;
				players[i].milk = 0;
				players[i].id = i;
			}
		}
		else if (!strcmp(tag, "COWS"))
		{
			sscanf(msg, "%*s %u", &NUMCOWS);
			for (i = 0; i < NUMCOWS; ++i)
			{
				unsigned int ii, value;
				cc = recv(msg);
				sscanf(msg, "%*s %u %u", &ii, &value);
				MILKVALUES[ii] = value;
			}
		}
		else if (!strcmp(tag, "ROUNDS"));
			sscanf(msg, "%*s %u", &NUMROUNDS);
	}

	copyself(); game_setup(players, NUMPLAYERS);

	while ((cc = recv(msg)))
	{
		sscanf(msg, "%s", tag);
		
		if (!strcmp(tag, "ENDGAME")) break;
		else if (!strcmp(tag, "ROUND"))
		{
			unsigned int rnum;
			sscanf(msg, "%*s %u", &rnum);
			
			while ((cc = recv(msg)))
			{
				sscanf(msg, "%s", tag);
				
				if (!strcmp(tag, "GO")) break;
				else if (!strcmp(tag, "PLAYER"))
				{
					unsigned int loc, milk;
					sscanf(msg, "%*s %u %u %u", &i, &loc, &milk);
					players[i].loc = loc;
					players[i].milk = milk;
				}
				else EXPECTED(tag, "PLAYER/GO");
			}

			rnum--; copyself();
			int k = player_turn(rnum, players, NUMPLAYERS);
			if (k < 0 || k >= NUMCOWS) goto quit;
			
			sprintf(msg, "MOVE %d", k);
			send(msg);
		}
		// got an unexpected message...
		else EXPECTED(tag, "ROUND/ENDGAME");
	}

	quit: game_end();
	return EXIT_SUCCESS;
}
