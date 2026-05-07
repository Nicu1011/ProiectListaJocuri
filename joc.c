#include "joc.h"

void insert(NODJOC** start, JOCVIDEO joc)
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
		return ;

	NODJOC* curent = *start;
	int i;

	if(at_index==0)//caz special
	{
		insert(start, joc);
		return ;
	}

	for(i=0; i<at_index-1; i++)
	{
		curent = curent->next;
		if(curent == NULL)//index invalid
			return ;
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
		return ;

	NODJOC* curent = *start;
	int i;

	for(i=0; i<at_index; i++)
	{
		curent = curent->next;
		if(curent == NULL)//index invalid
			return ;
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
	NODJOC* curent = start;
	if(curent == NULL)
		return ;

	while(curent!=NULL)
	{
		printf("%s ", curent->joc.nume);
		curent = curent->next;
	}
}

void afisare_inv(NODJOC* start)
{
	NODJOC* curent = start;
	if(curent == NULL)
		return ;

	while(curent->next!=NULL)
		curent = curent->next;

	while(curent!=NULL)
	{
		printf("%s ", curent->joc.nume);
		curent = curent->prev;
	}
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
		return ;

	int i;
	NODJOC* curent = *start;
	for(i=0; i<at_index; i++)
	{
		curent = curent->next;
		if(curent == NULL)//index invalid
			return ;
	}
	curent->joc = joc;
}
int get_num(NODJOC* start)
{
	int n=0;

	NODJOC* curent = start;

	while(curent!=NULL)
	{
		n++;
		curent=curent->next;
	}

	return n;
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
