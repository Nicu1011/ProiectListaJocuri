#include "joc.h"

const char* NUMEPARAMETRI[NR_PARAMETRI] = {
		"Nume:",
		"Dezvoltator:",
		"Publicant:",
		"Favorit:",
		"Clasament:",
		"Nota:",
		"Lansare (dd-mm-yyyy):",
		"Primu joc (dd-mm-yyyy):",
		"Ultimu joc (dd-mm-yyyy):",
		"Timp Jucat (hhhh_mm_ss):",
		"Spatiu Necesar (GB):",
		"Pret (EUR):",
		"Taguri (ex: RPG,ACTION,PVP):"
};

void insert(NODJOC** start, const JOCVIDEO joc)
{
	NODJOC* temp = (NODJOC*)malloc(sizeof(NODJOC));
	temp->joc = joc;
	temp->next = *start;
	temp->prev = NULL;

	if(*start != NULL)
		(*start)->prev = temp;

	*start = temp;
}

void insert_at(NODJOC** start, const JOCVIDEO joc, const int at_index)
{
	if(at_index < 0)
		return;

	NODJOC* curent = *start;
	int i;

	if(at_index==0)//caz special
	{
		insert(start, joc);
		return;
	}

	for(i=0; i<at_index-1; i++)
	{
		curent = curent->next;
		if(curent == NULL)//index invalid
			return;
	}

	NODJOC* temp = (NODJOC*)malloc(sizeof(NODJOC));
	temp->joc = joc;

	temp->next = curent->next;
	temp->prev = curent;

	if(curent->next != NULL)
		curent->next->prev = temp;

	curent->next = temp;
}

void delete_at(NODJOC** start, const int at_index)
{
	if(at_index < 0)
		return;

	NODJOC* curent = *start;
	int i;

	for(i=0; i<at_index; i++)
	{
		curent = curent->next;
		if(curent == NULL)//index invalid
			return;
	}

	if(curent->prev != NULL)
		curent->prev->next = curent->next;
	else
		*start = curent->next;

	if(curent->next != NULL)
		curent->next->prev = curent->prev;

	free(curent);
}

void afisare(NODJOC* start)
{
	if(start == NULL)
		return;

	NODJOC* curent = start;

	while(curent!=NULL)
	{
		printf("%s ", curent->joc.nume);
		curent = curent->next;
	}
}

void afisare_inv(NODJOC* start)
{
	if(start == NULL)
		return;

	NODJOC* curent = start;

	while(curent->next!=NULL)
		curent = curent->next;

	while(curent!=NULL)
	{
		printf("%s ", curent->joc.nume);
		curent = curent->prev;
	}
}

NODJOC* nodget_last(NODJOC* start)
{
	if(start == NULL)
		return NULL;

	NODJOC* curent = start;
	while(curent->next!=NULL)
		curent = curent->next;

	return curent;
}

JOCVIDEO* pget_at(NODJOC* start, const int at_index)
{
	if(at_index < 0)
		return NULL;

	NODJOC* curent = start;

	int i;
	for(i=0; i<at_index; i++)
	{
		curent = curent->next;
		if(curent == NULL)//index invalid
			return NULL;
	}

	return &curent->joc;
}
JOCVIDEO get_at(NODJOC* start, const int at_index)
{
	JOCVIDEO nimic = {0};

	if(at_index < 0)
		return nimic;

	int i;
	NODJOC* curent = start;
	for(i=0; i<at_index; i++)
	{
		curent = curent->next;
		if(curent == NULL)//index invalid
			return nimic;
	}

	return curent->joc;
}

void set_at(NODJOC** start, JOCVIDEO joc, const int at_index)
{
	if(at_index < 0)
		return;

	int i;
	NODJOC* curent = *start;
	for(i=0; i<at_index; i++)
	{
		curent = curent->next;
		if(curent == NULL)//index invalid
			return;
	}
	curent->joc = joc;
}
int get_num(NODJOC* start)
{
	int i=0;

	NODJOC* curent = start;

	while(curent!=NULL)
	{
		i++;
		curent=curent->next;
	}

	return i;
}
void free_lista(NODJOC** start)
{
	NODJOC* temp;
	NODJOC* curent = *start;

	while(curent!=NULL)
	{
		temp = curent;
		curent = curent->next;
		free(temp);
	}

	*start = NULL;
}

void sortare(NODJOC** start, int (*cmp)(JOCVIDEO, JOCVIDEO))
{
	NODJOC* nod1;
	NODJOC* nod2;
	for(nod1 = *start; nod1->next != NULL; nod1=nod1->next)
	{
		for(nod2 = nod1->next; nod2 != NULL; nod2=nod2->next)
		{
			if( cmp(nod1->joc, nod2->joc) > 0)
				swap_joc(&nod1->joc, &nod2->joc);
		}
	}
}
void swap_joc(JOCVIDEO* j1, JOCVIDEO* j2)
{
	JOCVIDEO temp = *j1;
	*j1 = *j2;
	*j2 = temp;
}
int cmp_nume(JOCVIDEO j1, JOCVIDEO j2)
{
	return strcmp(j1.nume, j2.nume);
}
int cmp_favorit(JOCVIDEO j1, JOCVIDEO j2)
{
	if(j1.favorit == 1 && j2.favorit == 1)
		return 0;
	if(j1.favorit != 1 && j2.favorit == 1)
		return 1;
	if(j1.favorit == 1 && j2.favorit != 1)
		return -1;
	return 0;
}
int cmp_nota(JOCVIDEO j1, JOCVIDEO j2)
{
	return j2.nota - j1.nota;
}
int cmp_clasament(JOCVIDEO j1, JOCVIDEO j2)
{
	return j1.clasament - j2.clasament;
}
int cmp_timpjucat(JOCVIDEO j1, JOCVIDEO j2)
{
	if(j1.timp_jucat.ore != j2.timp_jucat.ore)
		return j2.timp_jucat.ore - j1.timp_jucat.ore;
	if(j1.timp_jucat.min != j2.timp_jucat.min)
		return j2.timp_jucat.min - j1.timp_jucat.min;
	return j2.timp_jucat.sec - j1.timp_jucat.sec;
}
int cmp_pret(JOCVIDEO j1, JOCVIDEO j2)
{
	return j1.pret[EUR] - j2.pret[EUR];
}
