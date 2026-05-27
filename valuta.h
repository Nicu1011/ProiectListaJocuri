#ifndef VALUTA_H_
#define VALUTA_H_


#include <stdlib.h>
#include <stdio.h>

typedef enum {
	RON,
	EUR,
	USD,
	GBP,

	NR_MONEDE
} MONEDA;

extern const char* NUMEMONEDA[NR_MONEDE];

void citeste_fisier_curs(float curs[NR_MONEDE][NR_MONEDE], const char* nume_fisier);

void convertire_valuta(const float curs[NR_MONEDE][NR_MONEDE], float val[NR_MONEDE], const MONEDA moneda_principala);

#endif /* VALUTA_H_ */
