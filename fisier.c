#include "fisier.h"

void creaza_fisier(NODJOC* start, const char* nume_fisier)
{
	if(start == NULL)
		return ;
	if(nume_fisier == NULL)
		nume_fisier = "test.txt";

	FILE* file = fopen(nume_fisier, "w");
	if(!file)
		exit(1);

	NODJOC* curent = start;
	while(curent!=NULL)//for(curent = *start; curent!=NULL; curent=curent->next)
	{
		fprintf(file, FORMAT_LISTA_W,
				curent->joc.nume,
				curent->joc.dezvoltator,
				curent->joc.publicant,
				curent->joc.favorit,
				curent->joc.clasament,
				curent->joc.nota,
				curent->joc.data_lansare.zi,
				curent->joc.data_lansare.luna,
				curent->joc.data_lansare.an,
				curent->joc.data_primu_joc.zi,
				curent->joc.data_primu_joc.luna,
				curent->joc.data_primu_joc.an,
				curent->joc.data_ultim_joc.zi,
				curent->joc.data_ultim_joc.luna,
				curent->joc.data_ultim_joc.an,
				curent->joc.timp_jucat.ore,
				curent->joc.timp_jucat.min,
				curent->joc.timp_jucat.sec,
				curent->joc.spatiu_necesar,
				curent->joc.pret[EUR]);
		for(int tag=0; tag<NR_TAGURI; tag++)
		{
			if(tag+1 < NR_TAGURI)
				fprintf(file, FORMAT_TAG, curent->joc.taguri[tag]);
			else
			{
				fprintf(file, FORMAT_TAGLAST, curent->joc.taguri[tag]);

				if(curent->next != NULL)
					fprintf(file, "\n");
			}
		}

		curent = curent->next;
	}
	fclose(file);
}
void citeste_fisier(NODJOC** start, const char* nume_fisier)
{
	if(nume_fisier == NULL)
		nume_fisier = "lista_jocuri_default.txt";

	FILE* file = fopen(nume_fisier, "r");
	if(!file)
		exit(1);

	JOCVIDEO joc;

	int i=0;
	while(feof(file) == 0)
	{
	    fscanf(file, FORMAT_LISTA_R,
	    		joc.nume,
				joc.dezvoltator,
				joc.publicant,
				&joc.favorit,
				&joc.clasament,
				&joc.nota,
				&joc.data_lansare.zi,
				&joc.data_lansare.luna,
				&joc.data_lansare.an,
				&joc.data_primu_joc.zi,
				&joc.data_primu_joc.luna,
				&joc.data_primu_joc.an,
				&joc.data_ultim_joc.zi,
				&joc.data_ultim_joc.luna,
				&joc.data_ultim_joc.an,
				&joc.timp_jucat.ore,
				&joc.timp_jucat.min,
				&joc.timp_jucat.sec,
				&joc.spatiu_necesar,
				&joc.pret[EUR]);

		for(int tag=0; tag<NR_TAGURI; tag++)
			fscanf(file, FORMAT_TAG, &joc.taguri[tag]);

		insert_at(start, joc, i);
		i++;
	}
	fclose(file);
}
void creaza_backup(NODJOC* start)
{
	char data[32];
	char ora[32];
	creaza_timestamp_data(data, sizeof(data), FORMAT_DATA);
	creaza_timestamp_ora(ora, sizeof(ora), FORMAT_ORA);

	char timestamp[64];
	sprintf(timestamp, "%s_%s.txt", data, ora);
	creaza_fisier(start, timestamp);
}
