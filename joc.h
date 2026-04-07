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
extern const char *NUMETAG[NR_TAGURI];

typedef struct{
	int ore;
	int min;
	int sec;

} TIMP;

typedef struct{
	int an;
	int luna;
	int zi;

} DATA;

typedef struct{
	char nume[50];
	char dezvoltator[50], publicant[50];
	char taguri[NR_TAGURI];//index -> ENUM cu indexul tagului
	// valoare in sine e 0 daca nu are tag si 1 daca are acel tag

	int favorit;// 0 1
	int clasament;// 0 ... N
	int nota; // 0 ... 10

	DATA data_lansare, data_primu_joc, data_ultim_joc;
	TIMP timp_jucat;

	float spatiu_necesar; //GB

	PRET pret, pret_timp_jucat;

} JOCVIDEO;

#define MAX_LIST 50
extern JOCVIDEO lista_jocuri[MAX_LIST];
extern int lista_n;

void citire_lista_jocuri(char str_file[]);

#endif /* JOC_H_ */
