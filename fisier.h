#ifndef FISIER_H_
#define FISIER_H_

#include "joc.h"
#include "timp.h"

//functii pentru fisiere
void creaza_fisier(NODJOC* start, const char* nume_fisier);
void citeste_fisier(NODJOC** start, const char* nume_fisier);
void creaza_backup(NODJOC* start);

#endif /* FISIER_H_ */
