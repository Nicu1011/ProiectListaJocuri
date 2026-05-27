#include "tag.h"

const char* NUMETAG[NR_TAGURI] =
{
		"SINGLEPLAYER",
		"MULTIPLAYER",
		"PVE",
		"PVP",
		"COOP",
		"1ST_PERSON",
		"3TH_PERSON",
		"ACTION",
		"RPG",
		"MMORPG",
		"OPEN_WORLD",
		"SOULS_LIKE",
		"FANTASY",
		"DIFFICULT",
		"ATMOSPHERIC",
		"SANDBOX",
		"SHOOTER",
		"FPS",
		"SURVIVAL",
		"STORY_RICH"
};

void preia_taguri_text(const char* text, int taguri[NR_TAGURI])
{
	int i;
	for(i=0; i<NR_TAGURI; i++)
		taguri[i] = 0;

	char temp[100];
	strcpy(temp, text);

	char* cuv = strtok(temp, ",");

	while(cuv != NULL)
	{
		for(i=0; i<NR_TAGURI; i++)
		{
			if(strcmp(cuv, NUMETAG[i]) == 0)
				taguri[i] = 1;
		}

		cuv = strtok(NULL, ",");
	}
}
