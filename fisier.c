#include "fisier.h"

void creaza_fisier(NODJOC* start, const char* nume_fisier)
{
	if(start == NULL)
		return;
	if(nume_fisier == NULL)
		nume_fisier = "lista_jocuri_default.txt";

	FILE* file = fopen(nume_fisier, "w");
	if(file == NULL)
	{
		printf("eroare la deschiderea fisierului 0 %s", nume_fisier);
		exit(1);
	}

	NODJOC* curent = start;
	while(curent!=NULL)/* for(curent = *start; curent!=NULL; curent=curent->next) */
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
				fprintf(file, "%d ", curent->joc.taguri[tag]);
			else
			{
				fprintf(file, "%d", curent->joc.taguri[tag]);

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
	if(file == NULL)
	{
		printf("eroare la deschiderea fisierului 1 %s", nume_fisier);
		exit(1);
	}

	JOCVIDEO joc;
	float curs[NR_MONEDE][NR_MONEDE];
	citeste_fisier_curs(curs, NULL);

	int i=0;
	while(fscanf(file, FORMAT_LISTA_R,
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
			&joc.pret[EUR]) == 20)
	{
		for(int tag=0; tag<NR_TAGURI; tag++)
			if(fscanf(file, "%d", &joc.taguri[tag]) != 1)
			{
				fclose(file);
				return;
			}

		convertire_valuta(curs, joc.pret, EUR);

		insert_at(start, joc, i);
		i++;
	}
	fclose(file);
}
void creaza_backup(NODJOC* start)
{
	char data[50];
	char ora[50];
	creaza_timestamp_data(data, sizeof(data), FORMAT_DATA);
	creaza_timestamp_ora(ora, sizeof(ora), FORMAT_ORA);

	char timestamp[100];
	sprintf(timestamp, "backup_%s_%s.txt", data, ora);
	creaza_fisier(start, timestamp);

	scrie_backup(timestamp, NULL);
}
void scrie_backup(const char* nume_backup, const char* nume_fisier)
{
	if(nume_fisier == NULL)
		nume_fisier = "lista_backupuri.txt";

	FILE* file = fopen(nume_fisier, "a");
	if(file == NULL)
	{
		printf("eroare la deschiderea fisierului 2 %s", nume_fisier);
		exit(1);
	}

	fprintf(file, "%s\n", nume_backup);
	fclose(file);
}
void sterge_backup(const char* nume_backup, const char* nume_fisier)
{
	if(nume_fisier == NULL)
		nume_fisier = "lista_backupuri.txt";

	FILE* file = fopen(nume_fisier, "r");
	if(file == NULL)
	{
		printf("eroare la deschiderea fisierului 3 %s", nume_fisier);
		exit(1);
	}

	remove(nume_backup);

	char backupuri[MAX_BACKUPS][100];
	int count = 0;

	while(count < MAX_BACKUPS)
	{
		if(fscanf(file, "%s", backupuri[count]) != 1)
		{
			break;
		}
		count++;
	}

	fclose(file);

	file = fopen(nume_fisier, "w");
	if(file == NULL)
	{
		printf("eroare la deschiderea fisierului 4 %s", nume_fisier);
		exit(1);
	}

	int i;
	for(i = 0; i<count; i++)
	{
		if(strcmp(backupuri[i], nume_backup) != 0)
			fprintf(file, "%s\n", backupuri[i]);
	}

	fclose(file);
}
void citeste_lista_backup(int* count, char nume_backupuri[MAX_BACKUPS][100], const char* nume_fisier)
{
	if(nume_fisier == NULL)
		nume_fisier = "lista_backupuri.txt";

	*count = 0;

	FILE* file = fopen(nume_fisier, "r");
	if(file == NULL)
	{
		printf("eroare la deschiderea fisierului 5 %s", nume_fisier);
		exit(1);
	}

	while((*count) < MAX_BACKUPS)
	{
		if(fscanf(file, "%s", nume_backupuri[(*count)]) != 1)
		{
			fclose(file);
			return;
		}
		if(strlen(nume_backupuri[(*count)]) >= 100)
		{
			fclose(file);
			return;
		}
		(*count)++;
	}
	fclose(file);
}
