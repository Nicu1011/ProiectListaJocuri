#include "fereastra_glut.h"

/* ferestre */
int fereastra_main = -1;
int fereastra_backup = -1;
int fereastra_add = -1;
int fereastra_graf = -1;

/* date randuri */
NODJOC* lista = NULL;
JOCROW* table = NULL;
int count;
MONEDA moneda_selectat = EUR;

/* scroll randuri */
int scrollY;
int maxscrollY;
int minscrollY;

/* selectie randuri */
int index_selectat = 0;

/* toast */
char text_toast[50];
int visibil;
int start;
int duration;

void drawText(int x, int y, const char* text, int ignore_max_len)
{
	if(text == NULL)
		return;

	glRasterPos2i(x, y);
	for(int i=0; text[i] != '\0'; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
		if(ignore_max_len == 0)
			if(i > MAX_DISPLAYTEXT_LEN && text[i+1] != '\0')
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '.');
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '.');
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '.');
				return;
			}
	}
}
void drawTable(JOCROW* rows, int count)
{
	if(rows == NULL || count <= 0)
		return;

	for(int i=0; i<count; i++)
		drawRow(rows[i], (i == index_selectat)? 1: 0);
}
void drawRow(JOCROW row, int selectat)
{
	int y = row.y - scrollY;
	int x = row.x;
	int width = row.width;
	int height = row.height;

	if(x < 0 || x > WINDOW_W || y + ROW_H < 0 || y > WINDOW_H)
		return;

	glColor3f(0.5f, 0.5f, 0.5f);

	if(selectat == 0)
	{
		glBegin(GL_LINE_LOOP);
			glVertex2i(x, y);
			glVertex2i(x + width, y);
			glVertex2i(x + width, y + height);
			glVertex2i(x, y + height);
		glEnd();
	}
	else
	{
		glBegin(GL_QUADS);
			glVertex2i(x, y);
			glVertex2i(x + width, y);
			glVertex2i(x + width, y + height);
			glVertex2i(x, y + height);
		glEnd();
	}

	/* TEXT */
	glColor3f(0.0f, 0.0f, 0.0f);

	char temp[50];
	sprintf(temp, "%d", row.joc->clasament);
	drawText(x + ROWTEXT_XOFFSET + CLASAMENT_XOFFSET,
			y + ROWTEXT_YOFFSET,
			temp,
			0);

	drawText(x + ROWTEXT_XOFFSET + NUME_XOFFSET,
			y + ROWTEXT_YOFFSET,
			row.joc->nume
			,0);

	sprintf(temp, "%d:%02d:%02d",
			row.joc->timp_jucat.ore,
			row.joc->timp_jucat.min,
			row.joc->timp_jucat.sec);

	drawText(row.x + ROWTEXT_XOFFSET + TIMP_XOFFSET,
			y + ROWTEXT_YOFFSET,
			temp,
			0);

	sprintf(temp, "%.2f %s", row.joc->pret[moneda_selectat], NUMEMONEDA[moneda_selectat]);
	drawText(x + ROWTEXT_XOFFSET + PRET_XOFFSET,
			y + ROWTEXT_YOFFSET,
			temp,
			0);

	sprintf(temp, "%d", row.joc->nota);
	drawText(x + ROWTEXT_XOFFSET + NOTA_XOFFSET,
			y + ROWTEXT_YOFFSET,
			temp,
			0);

	glColor3f((row.joc->favorit == 1)? 1.0f: 0.0f, 0.0f, 0.0f);
	drawText(x + ROWTEXT_XOFFSET + FAV_XOFFSET,
			y + ROWTEXT_YOFFSET,
			(row.joc->favorit == 1)? "F": "x",
			0);
}
void drawToast()
{
	if(visibil == 0)
		return;

	int timp_trecut = glutGet(GLUT_ELAPSED_TIME) - start;

	if(timp_trecut >= duration)
	{
		visibil = 0;
		return;
	}

	glColor3f(0.7f, 1.0f, 0.7f);
	glBegin(GL_QUADS);
		glVertex2i(0, 0);
		glVertex2i(TOAST_W, 0);
		glVertex2i(TOAST_W, TOAST_H);
		glVertex2i(0, TOAST_H);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
		glVertex2i(0, 0);
		glVertex2i(TOAST_W, 0);
		glVertex2i(TOAST_W, TOAST_H);
		glVertex2i(0, TOAST_H);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	drawText(TOAST_W/3, TOAST_H/2, text_toast, 1);
}
void setToast(const char* text, int timp)
{
	strcpy(text_toast, text);
	visibil = 1;
	start = glutGet(GLUT_ELAPSED_TIME);
	duration = timp;
}
void drawHeader()
{
	glColor3f(0.8f, 0.8f, 1.0f);
	glBegin(GL_QUADS);
		glVertex2i(0, WINDOW_H);
		glVertex2i(HEADER_W, WINDOW_H);
		glVertex2i(HEADER_W, WINDOW_H - HEADER_H);
		glVertex2i(0, WINDOW_H - HEADER_H);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
		glVertex2i(0, WINDOW_H);
		glVertex2i(WINDOW_W, WINDOW_H);
		glVertex2i(WINDOW_W, WINDOW_H - ROW_H);
		glVertex2i(0, WINDOW_H - ROW_H);
	glEnd();

	/* TEXT */

	glColor3f(0.0f, 0.0f, 0.0f);
	drawText(CLASAMENT_XOFFSET, WINDOW_H - (ROW_H - ROWTEXT_YOFFSET), "Nr.", 1);
	drawText(NUME_XOFFSET, WINDOW_H - (ROW_H - ROWTEXT_YOFFSET), "Nume", 1);
	drawText(TIMP_XOFFSET, WINDOW_H - (ROW_H - ROWTEXT_YOFFSET), "Timp", 1);
	drawText(PRET_XOFFSET, WINDOW_H - (ROW_H - ROWTEXT_YOFFSET), "Pret", 1);
	drawText(NOTA_XOFFSET - 6, WINDOW_H - (ROW_H - ROWTEXT_YOFFSET), "Nota", 1);
	drawText(FAV_XOFFSET - 8, WINDOW_H - (ROW_H - ROWTEXT_YOFFSET), "Fav", 1);
}
void drawFooter()
{
	if(count <= 0)
		return;

	glColor3f(0.8f, 0.8f, 1.0f);
	glBegin(GL_QUADS);
		glVertex2i(0, 0);
		glVertex2i(FOOTER_W, 0);
		glVertex2i(FOOTER_W, FOOTER_H);
		glVertex2i(0, FOOTER_H);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
		glVertex2i(0, 0);
		glVertex2i(FOOTER_W, 0);
		glVertex2i(FOOTER_W, FOOTER_H);
		glVertex2i(0, FOOTER_H);
	glEnd();

	glBegin(GL_LINES);
		glVertex2i(FOOTERROW_W, 2*FOOTERROW_H);
		glVertex2i(FOOTERROW_W, FOOTER_H);
	glEnd();
	glBegin(GL_LINES);
		glVertex2i(2*FOOTERROW_W, 2*FOOTERROW_H);
		glVertex2i(2*FOOTERROW_W, FOOTER_H);
	glEnd();

	glBegin(GL_LINES);
		glVertex2i(0, 2*FOOTERROW_H);
		glVertex2i(FOOTER_W, 2*FOOTERROW_H);
	glEnd();

	/* TEXT */

	char temp[150];
	char temp2[150];

	glColor3f(0.0f, 0.0f, 0.0f);
	sprintf(temp, "NUME: %s", table[index_selectat].joc->nume);
	drawText(0*FOOTERROW_W + FOOTERTEXT_XOFFSET,
			7*FOOTERROW_H + FOOTERTEXT_YOFFSET,
			temp, 0);

	sprintf(temp, "DEV: %s", table[index_selectat].joc->dezvoltator);
	drawText(0*FOOTERROW_W + FOOTERTEXT_XOFFSET,
			6*FOOTERROW_H + FOOTERTEXT_YOFFSET,
			temp, 0);

	sprintf(temp, "PUB: %s", table[index_selectat].joc->publicant);
	drawText(0*FOOTERROW_W + FOOTERTEXT_XOFFSET,
			5*FOOTERROW_H + FOOTERTEXT_YOFFSET,
			temp, 0);

	sprintf(temp, "LANSARE: %02d-%02d-%04d",
			table[index_selectat].joc->data_lansare.zi,
			table[index_selectat].joc->data_lansare.luna,
			table[index_selectat].joc->data_lansare.an);
	drawText(0*FOOTERROW_W + FOOTERTEXT_XOFFSET,
			4*FOOTERROW_H + FOOTERTEXT_YOFFSET,
			temp, 0);

	sprintf(temp, "SPATIU: %.2f GB", table[index_selectat].joc->spatiu_necesar);
	drawText(0*FOOTERROW_W + FOOTERTEXT_XOFFSET,
			3*FOOTERROW_H + FOOTERTEXT_YOFFSET,
			temp, 0);

	sprintf(temp, "PRET: %.2f %s", table[index_selectat].joc->pret[moneda_selectat], NUMEMONEDA[moneda_selectat]);
	drawText(0*FOOTERROW_W + FOOTERTEXT_XOFFSET,
			2*FOOTERROW_H + FOOTERTEXT_YOFFSET,
			temp, 0);


	sprintf(temp, "PRIMUL: %02d-%02d-%04d",
			table[index_selectat].joc->data_primu_joc.zi,
			table[index_selectat].joc->data_primu_joc.luna,
			table[index_selectat].joc->data_primu_joc.an);
	drawText(1*FOOTERROW_W + FOOTERTEXT_XOFFSET,
			7*FOOTERROW_H + FOOTERTEXT_YOFFSET,
			temp, 0);

	sprintf(temp, "ULTIMUL: %02d-%02d-%04d",
			table[index_selectat].joc->data_ultim_joc.zi,
			table[index_selectat].joc->data_ultim_joc.luna,
			table[index_selectat].joc->data_ultim_joc.an);
	drawText(1*FOOTERROW_W + FOOTERTEXT_XOFFSET,
			6*FOOTERROW_H + FOOTERTEXT_YOFFSET,
			temp, 0);


	sprintf(temp, "TIMP: %d:%02d:%02d",
				table[index_selectat].joc->timp_jucat.ore,
				table[index_selectat].joc->timp_jucat.min,
				table[index_selectat].joc->timp_jucat.sec);
	drawText(1*FOOTERROW_W + FOOTERTEXT_XOFFSET,
			5*FOOTERROW_H + FOOTERTEXT_YOFFSET,
			temp, 0);

	sprintf(temp, "NR: %d", table[index_selectat].joc->clasament);
	drawText(2*FOOTERROW_W + FOOTERTEXT_XOFFSET,
			7*FOOTERROW_H + FOOTERTEXT_YOFFSET,
			temp, 0);

	sprintf(temp, "FAV: %d",table[index_selectat].joc->favorit);
	drawText(2*FOOTERROW_W + FOOTERTEXT_XOFFSET,
			6*FOOTERROW_H + FOOTERTEXT_YOFFSET,
			temp, 0);

	sprintf(temp, "NOTA: %d", table[index_selectat].joc->nota);
	drawText(2*FOOTERROW_W + FOOTERTEXT_XOFFSET,
			5*FOOTERROW_H + FOOTERTEXT_YOFFSET,
			temp, 0);


	temp[0] = '\0';
	temp2[0] = '\0';
	int cnt = 0;
	for(int tag = 0; tag<NR_TAGURI; tag++)
		if(table[index_selectat].joc->taguri[tag] == 1)
		{
			cnt++;
			if(cnt <= NR_TAGURI/3)
			{
				strcat(temp, "[");
				strcat(temp, NUMETAG[tag]);
				strcat(temp, "] ");
			}
			else
			{
				strcat(temp2, "[");
				strcat(temp2, NUMETAG[tag]);
				strcat(temp2, "] ");
			}
		}

	temp[149] = '\0';
	temp2[149] = '\0';

	drawText(0*FOOTERROW_W + + FOOTERTEXT_XOFFSET,
			1*FOOTERROW_H + FOOTERTEXT_YOFFSET,
			temp, 1);
	drawText(0*FOOTERROW_W + + FOOTERTEXT_XOFFSET,
			0*FOOTERROW_H + FOOTERTEXT_YOFFSET,
			temp2, 1);
}


/* ======================
 * FEREASTRA PRINCIPALA
 * ======================*/


void makeglut(int* argc, char** argv)
{
	free_lista(&lista);
	free(table);

	citeste_fisier(&lista, NULL);

	count = get_num(lista);
	table = (JOCROW*)malloc(sizeof(JOCROW) * count);
	formeaza_table(table, lista);

	glutInit(argc, argv);
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutInitWindowPosition((SCREEN_W - WINDOW_W)/2, (SCREEN_H - WINDOW_H)/2);
	fereastra_main = glutCreateWindow("Lista Jocuri Video");

	glutSetWindow(fereastra_main);

	gluOrtho2D(0, WINDOW_W, 0, WINDOW_H);

	glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
	atexit(exit_main);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutTimerFunc(REFRESH_MS, timer, 0);
}
void exit_main()
{
	creaza_fisier(lista, "quicksave_exit.txt");
	creaza_backup(lista);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawTable(table, count);

	drawHeader();
	drawFooter();

	drawToast();
	glFlush();
}
void keyboard(unsigned char key, int x, int y)
{
	if(key == KEY_ESC)
	{
		exit(0);
	}
	if(key == 'q' || key == 'Q')
	{
		free_lista(&lista);
		free(table);

		citeste_fisier(&lista, "quicksave_exit.txt");

		count = get_num(lista);
		table = (JOCROW*)malloc(sizeof(JOCROW) * count);
		formeaza_table(table, lista);

		setToast("LOADED quicksave_exit.txt", 1000);
	}
	if(key == 'w'|| key == 'W')
	{
		free_lista(&lista);
		free(table);

		citeste_fisier(&lista, NULL);

		count = get_num(lista);
		table = (JOCROW*)malloc(sizeof(JOCROW) * count);
		formeaza_table(table, lista);

		setToast("LOADED lista_jocuri_default.txt", 1000);
	}
	if(key == 's' || key == 'S')
	{
		creaza_fisier(lista, NULL);
		setToast("SAVED lista_jocuri_default.txt", 1000);
	}
	if(key == 'f' || key == 'F')
	{
		if(fereastra_backup == -1)
			makeglut_backup();
	}
	if((key == 'b' || key == 'B') && visibil == 0)
	{
		creaza_backup(lista);
		setToast("BACKUP CREAT", 1000);
	}
	if(key == 'n' || key == 'N')
	{
		if(fereastra_add == -1)
			makeglut_add();
	}
	if(key == 'm' || key == 'M')
	{
		if(fereastra_graf == -1)
			makeglut_graf();
	}
	if(key == 'k' || key == 'K')
	{
		if(count > 0)
		{
			delete_at(&lista, index_selectat);

			free(table);
			count = get_num(lista);
			table = (JOCROW*)malloc(sizeof(JOCROW) * count);
			formeaza_table(table, lista);

			setToast("JOC STERS", 1000);
		}
	}
	if(key == '1' && count > 0)
	{
		sortare(&lista, cmp_clasament);
		setToast("SORTAT (Clasament)", 500);
	}
	if(key == '2' && count > 0)
	{
		sortare(&lista, cmp_nume);
		setToast("SORTAT (Nume)", 500);
	}
	if(key == '3' && count > 0)
	{
		sortare(&lista, cmp_timpjucat);
		setToast("SORTAT (Timp)", 500);
	}
	if(key == '4' && count > 0)
	{
		sortare(&lista, cmp_pret);
		setToast("SORTAT (Pret)", 500);
	}
	if(key == '5' && count > 0)
	{
		sortare(&lista, cmp_nota);
		setToast("SORTAT (Nota)", 500);
	}
	if(key == '6' && count > 0)
	{
		sortare(&lista, cmp_favorit);
		setToast("SORTAT (Favorit)", 500);
	}

}
void special(int key, int x, int y)
{
	if(key == KEY_DOWN)
	{
		if(scrollY > minscrollY)
			scrollY -= SCROLL_SPEED;
		if(index_selectat < count - 1)
			index_selectat++;
	}
	if(key == KEY_UP)
	{
		if(scrollY < maxscrollY)
			scrollY += SCROLL_SPEED;
		if(index_selectat > 0)
			index_selectat--;
	}
	if(key == KEY_LEFT && moneda_selectat > 0)
	{
		moneda_selectat--;
	}
	if(key == KEY_RIGHT && moneda_selectat < NR_MONEDE - 1)
	{
		moneda_selectat++;
	}
}
void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(REFRESH_MS, timer, 0);
}


/* ======================
 * FEREASTRA PENTRU ADAUGARE
 * ======================*/


JOCVIDEO* input_joc = NULL;
int index_parametru = 0;
char input_text[NR_PARAMETRI][100];

void drawAdaugare()
{
	int i, y;
	for(i = 0; i<NR_PARAMETRI; i++)
	{
		y = ADD_H - (i+1) * ADDROW_H;

		glColor3f(0.5f, 0.5f, 0.5f);
		if(i == index_parametru)
		{
			glBegin(GL_QUADS);
				glVertex2i(0, y);
				glVertex2i(ADD_W, y);
				glVertex2i(ADD_W, y + ADDROW_H);
				glVertex2i(0, y + ADDROW_H);
			glEnd();
		}

		glBegin(GL_LINES);
			glVertex2i(0, y);
			glVertex2i(ADD_W, y);
		glEnd();

		glColor3f(0.0f, 0.0f, 0.0f);
		drawText(ADDTEXT_XOFFSET, y + ADDROW_H/6, NUMEPARAMETRI[i], 1);
		drawText(ADD_W/3 + ADDTEXT_XOFFSET, y + ADDROW_H/6, input_text[i], 1);
	}

	y = ADD_H - (i+1) * ADDROW_H;
	drawText(5, y + ADDROW_H/2, "SINGLEPLAYER,MULTIPLAYER,PVE,PVP,COOP,1ST_PERSON,3TH_PERSON,ACTION,RPG,MMORPG,OPEN_WORLD", 1);
	drawText(5, y + ADDROW_H/6, "SOULS_LIKE,FANTASY,DIFFICULT,ATMOSPHERIC,SANDBOX,SHOOTER,FPS,SURVIVAL,STORY_RICH", 1);

}

void makeglut_add()
{
	free(input_joc);
	input_joc = (JOCVIDEO*)malloc(sizeof(JOCVIDEO));

	glutInitWindowSize(ADD_W, ADD_H);
	glutInitWindowPosition((SCREEN_W - ADD_W)/2, (SCREEN_H - ADD_H)/2);
	fereastra_add = glutCreateWindow("Adauga Joc");

	glutSetWindow(fereastra_add);

	gluOrtho2D(0, ADD_W, 0, ADD_H);

	glClearColor(0.9f, 0.9f, 1.0f, 1.0f);

	glutDisplayFunc(display_add);
	glutKeyboardFunc(keyboard_add);
	glutTimerFunc(REFRESH_MS, timer_add, 0);
}
void exit_add()
{
	free(input_joc);
	input_joc = NULL;

	index_parametru = 0;
	memset(input_text, 0, sizeof(input_text));

	glutDestroyWindow(fereastra_add);
	fereastra_add = -1;
	glutSetWindow(fereastra_main);
}
void display_add()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawAdaugare();

	glFlush();
}
void keyboard_add(unsigned char key, int x, int y)
{
	if(key == KEY_ESC)
	{
		exit_add();
		return;
	}
	if(index_parametru >= NR_PARAMETRI)
		if(key == '\r')
		{
			strcpy(input_joc->nume, input_text[NUME]);
			strcpy(input_joc->dezvoltator, input_text[DEZVOLTATOR]);
			strcpy(input_joc->publicant, input_text[PUBLICANT]);
			sscanf(input_text[FAVORIT], "%d", &input_joc->favorit);
			sscanf(input_text[CLASAMENT], "%d", &input_joc->clasament);
			sscanf(input_text[NOTA], "%d", &input_joc->nota);

			sscanf(input_text[DATA_LANSARE], "%d-%d-%d", &input_joc->data_lansare.zi, &input_joc->data_lansare.luna, &input_joc->data_lansare.an);
			sscanf(input_text[DATA_PRIMU_JOC], "%d-%d-%d", &input_joc->data_primu_joc.zi, &input_joc->data_primu_joc.luna, &input_joc->data_primu_joc.an);
			sscanf(input_text[DATA_ULTIM_JOC], "%d-%d-%d", &input_joc->data_ultim_joc.zi, &input_joc->data_ultim_joc.luna, &input_joc->data_ultim_joc.an);
			sscanf(input_text[TIMPJUCAT], "%d_%d_%d", &input_joc->timp_jucat.ore, &input_joc->timp_jucat.min, &input_joc->timp_jucat.sec);

			sscanf(input_text[SPATIU_NECESAR], "%f", &input_joc->spatiu_necesar);
			sscanf(input_text[PRET], "%f", &input_joc->pret[EUR]);

			preia_taguri_text(input_text[TAGURI], input_joc->taguri);

			insert(&lista, *input_joc);

			count = get_num(lista);
		    free(table);
		    table = (JOCROW*)malloc(sizeof(JOCROW) * count);
		    formeaza_table(table, lista);

		    setToast("JOC ADAUGAT", 1000);

			exit_add();
		}
	if(key == '\r' && input_text[index_parametru][0] != '\0')
	{
		index_parametru++;
		return;
	}
	if(key == '\b')
	{
		int i = 0;
		while(input_text[index_parametru][i+1] != '\0' && input_text[index_parametru][i] != '\0')
			i++;

		input_text[index_parametru][i] = '\0';
		return;
	}
	if(key >= '!' && key <= '~' && key != '\\' && key != '%')
	{
		int i = 0;
		while(input_text[index_parametru][i] != '\0' && i < 48)
			i++;

		input_text[index_parametru][i] = key;
		input_text[index_parametru][i+1] = '\0';
	}
}
void timer_add(int value)
{
	glutPostRedisplay();
	glutTimerFunc(REFRESH_MS, timer_add, 0);
}


/* ======================
 * FEREASTRA PENTRU BACKUP
 * ======================*/


char backup_list[MAX_BACKUPS][100];
int backup_count;
int index_backup = 0;

int backup_scrollY = 0;
int backupmax_scrollY;
int backupmin_scrollY;

void drawBackups()
{
	if(backup_count <= 0)
		return;

	int y = BACK_H - backup_scrollY;
	int x = 0;
	int width = BACKROW_W;
	int height = BACKROW_H;

	int i;

	for(i = 0; i < backup_count; i++)
	{
		y -= BACKROW_H;

		glColor3f(0.5f, 0.5f, 0.5f);

		if(i == index_backup)
		{
			glBegin(GL_QUADS);
				glVertex2i(x, y);
				glVertex2i(x + width, y);
				glVertex2i(x + width, y + height);
				glVertex2i(x, y + height);
			glEnd();
		}
		else
		{
			glBegin(GL_LINE_LOOP);
				glVertex2i(x, y);
				glVertex2i(x + width, y);
				glVertex2i(x + width, y + height);
				glVertex2i(x, y + height);
			glEnd();
		}

		glColor3f(0.0f, 0.0f, 0.0f);
		drawText(x + BACKTEXT_XOFFSET, y + BACKTEXT_YOFFSET, backup_list[i], 1);
	}
}
void load_backups()
{
	citeste_lista_backup(&backup_count, backup_list, NULL);
	index_backup = 0;
	backup_scrollY = 0;
	backupmax_scrollY = 0;
	backupmin_scrollY = BACK_H - (backup_count * BACKROW_H);
}
void makeglut_backup()
{
	load_backups();

	glutInitWindowSize(BACK_W, BACK_H);
	glutInitWindowPosition((SCREEN_W - BACK_W)/2, (SCREEN_H - BACK_H)/2);
	fereastra_backup = glutCreateWindow("Backupuri Jocuri");

	glutSetWindow(fereastra_backup);

	gluOrtho2D(0, BACK_W, 0, BACK_H);

	glClearColor(0.9f, 0.9f, 1.0f, 1.0f);

	glutDisplayFunc(display_backup);
	glutKeyboardFunc(keyboard_backup);
	glutSpecialFunc(special_backup);
	glutTimerFunc(REFRESH_MS, timer_backup, 0);
}
void exit_backup()
{
	memset(backup_list, 0, sizeof(backup_list));

	backup_count = 0;
	index_backup = 0;
	backup_scrollY = 0;
	backupmin_scrollY = 0;
	backupmax_scrollY = 0;

	glutDestroyWindow(fereastra_backup);
	fereastra_backup = -1;
	glutSetWindow(fereastra_main);
}
void display_backup()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawBackups();

	glFlush();
}
void keyboard_backup(unsigned char key, int x, int y)
{
	if(key == KEY_ESC)
	{
		exit_backup();
		return;
	}
	if(key == '\r')
	{
		if(backup_count > 0)
		{
			free_lista(&lista);
			free(table);

			citeste_fisier(&lista, backup_list[index_backup]);

			count = get_num(lista);

			table = (JOCROW*)malloc(sizeof(JOCROW) * count);

			formeaza_table(table, lista);
			exit_backup();
		}
	}
	if(key == 'k' || key == 'K')
	{
		if(backup_count > 0)
		{
			sterge_backup(backup_list[index_backup], NULL);
			load_backups();
		}
	}
}
void special_backup(int key, int x, int y)
{
	if(key == KEY_DOWN)
	{
		if(backup_scrollY > backupmin_scrollY)
			backup_scrollY -= BACK_SCROLL_SPEED;
		if(index_backup < backup_count - 1)
			index_backup++;
	}
	if(key == KEY_UP)
	{
		if(backup_scrollY < backupmax_scrollY)
			backup_scrollY += BACK_SCROLL_SPEED;
		if(index_backup > 0)
			index_backup--;
	}
}
void timer_backup(int value)
{
	glutPostRedisplay();
	glutTimerFunc(REFRESH_MS, timer_backup, 0);
}


/* ======================
 * FEREASTRA PENTRU GRAFIC
 * ======================*/


void drawGraf()
{
	if(count <= 0)
		return;

	int i;
	float val;
	float max_val = 0;
	for(i = 0; i<count; i++)
	{
		val = table[i].joc->timp_jucat.ore * 3600 +
				table[i].joc->timp_jucat.min * 60 +
				table[i].joc->timp_jucat.sec;

		if(max_val < val)
			max_val = val;
	}

	int bar_w = GRAF_W / (count+1);
	for(i = 0; i<count; i++)
	{
		val = table[i].joc->timp_jucat.ore * 3600 +
				table[i].joc->timp_jucat.min * 60 +
				table[i].joc->timp_jucat.sec;

		int bar_h = (int)((val / max_val) * (GRAF_H - GRAF_OFFSETY*2));
		int bar_x = (i+1) * bar_w;
		int bar_y = GRAF_OFFSETY;

		if(i == index_selectat)
			glColor3f(0.5f, 0.0f, 0.0f);
		else
			glColor3f(0.7f, 0.7f, 0.9f);

		if(bar_h > 0)
		{
			glBegin(GL_QUADS);
				glVertex2i(bar_x, bar_y);
				glVertex2i(bar_x + bar_w, bar_y);
				glVertex2i(bar_x + bar_w, bar_y + bar_h);
				glVertex2i(bar_x, bar_y + bar_h);
			glEnd();

			glColor3f(0.0f, 0.0f, 0.0f);
			glBegin(GL_LINE_LOOP);
				glVertex2i(bar_x, bar_y);
				glVertex2i(bar_x + bar_w, bar_y);
				glVertex2i(bar_x + bar_w, bar_y + bar_h);
				glVertex2i(bar_x, bar_y + bar_h);
			glEnd();
		}
		if(i == index_selectat)
			glColor3f(1.0f, 0.0f, 0.0f);
		else
			glColor3f(0.0f, 0.0f, 0.0f);

		char temp[12];
		sprintf(temp, "%d", table[i].joc->clasament);
		drawText(bar_x + bar_w/3, 5, temp, 1);
	}
}
void makeglut_graf()
{
	glutInitWindowSize(GRAF_W, GRAF_H);
	glutInitWindowPosition((SCREEN_W - GRAF_W)/2, (SCREEN_H - GRAF_H)/2);
	fereastra_graf = glutCreateWindow("Grafic Jocuri Timp Jucat");

	glutSetWindow(fereastra_graf);

	gluOrtho2D(0, GRAF_W, 0, GRAF_H);

	glClearColor(0.9f, 0.9f, 1.0f, 1.0f);

	glutDisplayFunc(display_graf);
	glutKeyboardFunc(keyboard_graf);
	glutSpecialFunc(special_graf);
	glutTimerFunc(REFRESH_MS, timer_graf, 0);
}
void graf_exit()
{
	glutDestroyWindow(fereastra_graf);
	fereastra_graf = -1;
	glutSetWindow(fereastra_main);
}
void display_graf()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawGraf();

	glFlush();
}
void keyboard_graf(unsigned char key, int x, int y)
{
	if(key == KEY_ESC)
	{
		graf_exit();
		return;
	}
}
void special_graf(int key, int x, int y)
{
	if(key == KEY_DOWN)
	{
		if(scrollY > minscrollY)
			scrollY -= SCROLL_SPEED;
		if(index_selectat < count - 1)
			index_selectat++;
	}
	if(key == KEY_UP)
	{
		if(scrollY < maxscrollY)
			scrollY += SCROLL_SPEED;
		if(index_selectat > 0)
			index_selectat--;
	}
	if(key == KEY_LEFT && moneda_selectat > 0)
	{
		moneda_selectat--;
	}
	if(key == KEY_RIGHT && moneda_selectat < NR_MONEDE - 1)
	{
		moneda_selectat++;
	}
}
void timer_graf(int value)
{
	glutPostRedisplay();
	glutTimerFunc(REFRESH_MS, timer_graf, 0);
}

/* diverse */
void formeaza_table(JOCROW* table, NODJOC* lista)
{
	if(lista == NULL || table == NULL)
		return;

	NODJOC* curent = lista;
	int i = 0, x = 0, y = WINDOW_H - HEADER_H; /* -HEADER_H pentru a nu le suprapune */

	scrollY = 0;
	maxscrollY = 0;
	minscrollY = y - ((count * ROW_H) + FOOTER_H); /* +FOOTER_H pentru a nu le suprapune */
	index_selectat = 0;

	while(curent != NULL)
	{
		y -= ROW_H;
		table[i].joc = &curent->joc;

		table[i].x = x;
		table[i].y = y;
		table[i].width = ROW_W;
		table[i].height = ROW_H;

		curent = curent->next;
		i++;
	}
}
