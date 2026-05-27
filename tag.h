#ifndef TAG_H_
#define TAG_H_

#include <stdio.h>
#include <string.h>

typedef enum{
	SINGLEPLAYER,
	MULTIPLAYER,
	PVE,
	PVP,
	COOP,
	FIRST_PERSON,
	THIRD_PERSON,
	ACTION,
	RPG,
	MMORPG,
	OPEN_WORLD,
	SOULS_LIKE,
	FANTASY,
	DIFFICULT,
	ATMOSPHERIC,
	SANDBOX,
	SHOOTER,
	FPS,
	SURVIVAL,
	STORY_RICH,

	NR_TAGURI
} TAGURIJOC;
extern const char* NUMETAG[NR_TAGURI];

void preia_taguri_text(const char* text, int taguri[NR_TAGURI]);

#endif /* TAG_H_ */
