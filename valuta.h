#ifndef VALUTA_H_
#define VALUTA_H_

typedef enum {
	RON,
	EUR,
	USD,
	GBP,
	IMAGINAR,

	NR_MONEDE
} MONEDA;

typedef float VALUTA[NR_MONEDE];
typedef float CURS[NR_MONEDE][NR_MONEDE];

void fcitire_curs_valutar(const char* nume_fisier, float curs[NR_MONEDE][NR_MONEDE]);

void convertire_valuta_v(const CURS curs, const VALUTA val, VALUTA val_conv, const MONEDA m_principal);
float convertire_valuta_f(const CURS curs, const float val, const MONEDA moneda_in, const MONEDA moneda_out);

#endif /* VALUTA_H_ */
