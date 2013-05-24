#include <unistd.h>
#include <stdio.h>

#include "mm-base.h"
#include "mm-visual.h"

unsigned int prevmilk[MAXAGENTS];

int setup_bcb_vis(int numagents, struct agent_t *agents, int *argc, char ***argv)
{
	int i;
	for (i = 0; i < numagents; ++i)
		prevmilk[i] = 0;
	
	return 1;
};

int update_bcb_vis(int numagents, struct agent_t *agents, const int turn)
{
	int i; struct agent_t *a = agents;
	printf("Round #%d\n", turn);
	for (i = 0; i < numagents; ++a, ++i)
	{
		int gain = a->milk - prevmilk[i];
		printf(">> %24s, loc=%3u, milk=%8u(%+d)\n", a->name, a->loc, a->milk, gain);
		prevmilk[i] = a->milk;
	}
	
	return 1;
};

void close_bcb_vis()
{

};

