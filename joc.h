#ifndef JOC_H_
#define JOC_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "valuta.h"
#include "tag.h"

typedef enum{
	NUME,
	DEZVOLTATOR,
	PUBLICANT,
	FAVORIT,
	CLASAMENT,
	NOTA,
	DATA_LANSARE,
	DATA_PRIMU_JOC,
	DATA_ULTIM_JOC,
	TIMPJUCAT,
	SPATIU_NECESAR,
	PRET,
	TAGURI,

	NR_PARAMETRI
} PARAMETRIJOC;
extern const char* NUMEPARAMETRI[NR_PARAMETRI];

struct timp{
	int ore;
	int min;
	int sec;
};
typedef struct timp TIMP;

struct data{
	int an;
	int luna;
	int zi;
};
typedef struct data DATA;

struct jocvideo{
	char nume[50];
	char dezvoltator[50], publicant[50];

	int favorit;
	int clasament;
	int nota;
	int taguri[NR_TAGURI];

	DATA data_lansare, data_primu_joc, data_ultim_joc;
	TIMP timp_jucat;

	float spatiu_necesar;

	float pret[NR_MONEDE];

};
typedef struct jocvideo JOCVIDEO;

struct nodjoc{
	JOCVIDEO joc;
	struct nodjoc* next;
	struct nodjoc* prev;

};
typedef struct nodjoc NODJOC;

/* functii lista */
void insert(NODJOC** start, const JOCVIDEO joc);
void insert_at(NODJOC** start, const JOCVIDEO joc, const int at_index);
void delete_at(NODJOC** start, const int at_index);
void afisare(NODJOC* start);
void afisare_inv(NODJOC* start);
NODJOC* nodget_last(NODJOC* start);
JOCVIDEO* pget_at(NODJOC* start, const int at_index);
JOCVIDEO get_at(NODJOC* start, const int at_index);
void set_at(NODJOC** start, JOCVIDEO joc, const int at_index);
int get_num(NODJOC* start);
void free_lista(NODJOC** start);

/* functii pentru sortare */
void sortare(NODJOC** start, int (*cmp)(JOCVIDEO, JOCVIDEO));
void swap_joc(JOCVIDEO* j1, JOCVIDEO* j2);

int cmp_clasament(JOCVIDEO j1, JOCVIDEO j2);
int cmp_nume(JOCVIDEO j1, JOCVIDEO j2);
int cmp_favorit(JOCVIDEO j1, JOCVIDEO j2);
int cmp_nota(JOCVIDEO j1, JOCVIDEO j2);
int cmp_timpjucat(JOCVIDEO j1, JOCVIDEO j2);
int cmp_pret(JOCVIDEO j1, JOCVIDEO j2);

#endif /* JOC_H_ */
