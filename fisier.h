#ifndef FISIER_H_
#define FISIER_H_


#include "joc.h"
#include "timp.h"

#define FORMAT_LISTA_R "%s %s %s %d %d %d %d-%d-%d %d-%d-%d %d-%d-%d %d_%d_%d %f %f "
#define FORMAT_LISTA_W "%49s %49s %49s %1d %2d %2d %02d-%02d-%04d %02d-%02d-%04d %02d-%02d-%04d %4d_%02d_%02d %6.2f %6.2f "

#define MAX_BACKUPS 100

/* functii pentru fisiere */
void creaza_fisier(NODJOC* start, const char* nume_fisier);
void citeste_fisier(NODJOC** start, const char* nume_fisier);
void creaza_backup(NODJOC* start);
void scrie_backup(const char* nume_backup, const char* nume_fisier);
void sterge_backup(const char* nume_backup, const char* nume_fisier);
void citeste_lista_backup(int* count, char nume_backupuri[MAX_BACKUPS][100], const char* nume_fisier);

#endif /* FISIER_H_ */
