#ifndef VALUTA_H_
#define VALUTA_H_

typedef enum {
	RON,
	EUR,
	USD,
	GBP,

	NR_MONEDE
} MONEDA;

typedef struct{
	float RON;
	float EUR;
	float USD;
	float GBP;

} VALUTA;

VALUTA* citire_curs_valutar(char* str_file);
VALUTA convertire_valuta_p(VALUTA* curs_valutar, VALUTA val, MONEDA m_principal);
float convertire_valuta_f(VALUTA* curs_valutar, float val, MONEDA moneda_in, MONEDA moneda_out);

#endif /* VALUTA_H_ */
