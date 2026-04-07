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

} pret_t;

pret_t citire_curs_valutar(const MONEDA monedaPrincipala);

#endif /* VALUTA_H_ */
