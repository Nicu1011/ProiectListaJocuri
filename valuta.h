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

void fcitire_curs_valutar(const char* nume_fisier, float* curs[NR_MONEDE][NR_MONEDE]);

void convertire_valuta_v(const float curs[NR_MONEDE][NR_MONEDE], const float val[NR_MONEDE], float* val_conv[NR_MONEDE], const MONEDA m_principal);
float convertire_valuta_f(const float curs[NR_MONEDE][NR_MONEDE], const float val, const MONEDA moneda_in, const MONEDA moneda_out);


#endif /* VALUTA_H_ */
