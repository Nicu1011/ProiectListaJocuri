#ifndef JOC_H_
#define JOC_H_

#include "valuta.h"

typedef enum{
	SINGLEPLAYER,
	MULTIPLAYER,
	PVE,
	PVP,
	COOP,
	FIRST_PERSON,
	THIRD_PERSON,
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
const char *numeTag[NR_TAGURI] = {
		"SINGLEPLAYER",
		"MULTIPLAYER",
		"PVE",
		"PVP",
		"COOP",
		"FIRST_PERSON",
		"THIRD_PERSON",
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

typedef struct{
	int ore;
	int min;
	int sec;

} timp_t;

typedef struct{
	int an;
	int luna;
	int zi;
	timp_t timp;

} data_t;



typedef struct{
	char nume[50];
	char descriere[100];
	char dezvoltator[50], publicant[50];
	char taguri[NR_TAGURI];//index -> ENUM cu indexul tagului
	// valoare in sine e 0 daca nu are tag si 1 daca are acel tag

	int favorit: 1;// 0 1
	int clasament;// 0 ... N
	int nota; // 0 ... 10

	data_t dataLansare, dataPrimuJoc, dataUltimJoc;
	timp_t timpJucat;

	float spatiuNecesar; //GB

	pret_t pret, pretTimpJucat;

} jocvideo_t;


#endif /* JOC_H_ */
