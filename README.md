Descriere

Lista Jocuri Video este o aplicație desktop realizată în limbajul C folosind biblioteca FREEGLUT/OpenGL. 
Programul permite gestionarea unei colecții personale de jocuri video printr-o interfață grafică controlată exclusiv din tastatură.

Programul oferă:

	afișarea unei liste de jocuri;
	sortare după mai multe criterii;
	adăugare și ștergere jocuri;
	sistem de backup;
	conversie valutară;
	afișarea statisticilor;
	grafic pentru timpul jucat;

Compilare:

Se vor folosi caile pentru FREEGLUT/OpenGL:

		Windows: -freeglut -glu32 -opengl32;
		Linux: -GL -GLU -glut;
	
Ex (WINDOWS): 

	gcc -o proiect_lista_personala_jocuri_video.exe fereastra_glut.o fisier.o joc.o main.o tag.o timp.o valuta.o -lfreeglut -lglu32 -lopengl32 

Fereastra principală afișează:	

	- clasamentul jocului;
	- numele;
	- timpul jucat;
	- prețul;
	- nota;
	- favorit;
Datele sunt încărcate din fișierul: "lista_jocuri_default.txt"

Navigarea:

	↑ - Selectare sus + derulare sus
	↓ - Selectare jos + derulare jos
	← - Monedă anterioară
	→ - Monedă următoare
monede: [RON] - **[EUR]** - [USD] - [GBP] 
		
Salvarea/Încărcarea:

	S - Salvare listă
	W - Încărcare listă: "lista_jocuri_default.txt"
	Q - Încărcare quicksave: "quicksave_exit.txt" salvată la închiderea programului
	ESC - Ieșire

Adăugarea:

	N - Creează joc nou
	
Ștergerea:

	K - Șterge jocul selectat
	
Sortarea:

	1 - Sortare după clasament
	2 - Sortare după nume
	3 - Sortare după timp jucat
	4 - Sortare după preț
	5 - Sortare după notă
	6 - Sortare favorite
	
Gestionarea Backupurilor:

	B - Creează backup
	F - Deschide interfață backup

Backup-urile sunt salvate automat sub forma: "backup_dd-mm-yyyy_hh_mm_ss.txt"
	
Grafic timp:

	M - Grafic Jocuri Timp Jucat

Observații:
		
	- Programul este controlat doar din tastatura;
    - Datele introduse nu sunt validate complet;
	- Numele și orice string nu trebuie să conțina spații;