#ifndef FISIER_H_
#define FISIER_H_


#include "joc.h"
#include "timp.h"

#define FORMAT_LISTA_R "%49s %49s %49s %d %d %d %d-%d-%d %d-%d-%d %d-%d-%d %d_%d_%d %f %f "
#define FORMAT_LISTA_W "%49s %49s %49s %1d %2d %2d %02d-%02d-%04d %02d-%02d-%04d %02d-%02d-%04d %04d_%02d_%02d %6.2f %6.2f "

//functii pentru fisiere
void creaza_fisier(NODJOC* start, const char* nume_fisier);
void citeste_fisier(NODJOC** start, const char* nume_fisier);
void creaza_backup(NODJOC* start);

#endif /* FISIER_H_ */
