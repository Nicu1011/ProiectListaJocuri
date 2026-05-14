#include "fereastra_glut.h"

//ferestre
int fereastra_main = -1;
int fereastra_add = -1;
int fereastra_grafic = -1;

//date randuri
NODJOC* lista = NULL;
JOCROW* table = NULL;
int count;

//scroll randuri
int scrollY;
int maxscrollY;
int minscrollY;

//selectie randuri
int index_selectat = 0;

//toast
char text_toast[32];
int visibil;
int start;
int duration;

//fereastra input
JOCVIDEO* input_joc = NULL;
int index_parametru = 0;
char input_text[NR_PARAMETRI][50];

void drawText(int x, int y, const char* text, int ignore_max_len)
{
	glRasterPos2i(x, y);
	for(int i=0; text[i] != '\0'; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
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
//void drawButton(BUTTON b)
//{
//	glBegin(GL_QUADS);
//		glColor3f(0.0f, 0.0f, 0.0f);
//		glVertex2i(b.x, b.y);
//		glVertex2i(b.x + b.width, b.y);
//		glVertex2i(b.x + b.width, b.y + b.height);
//		glVertex2i(b.x, b.y + b.height);
//	glEnd();
//
//	glColor3f(0.0f, 0.0f, 1.0f);
//	drawText(b.x + (b.width/2) + b.textXOffset,
//			b.y + (b.height/2) + b.textYOffset,
//			b.text,
//			1);
//}
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

	//text
	glColor3f(0.0f, 0.0f, 0.0f);

	char temp[30];
	sprintf(temp, "%d", row.joc->clasament);
	drawText(row.x + row.textXOffset + CLASAMENT_XOFFSET,
			y + row.textYOffset,
			temp,
			0);

	drawText(row.x + row.textXOffset + NUME_XOFFSET,
			y + row.textYOffset,
			row.joc->nume
			,0);

	sprintf(temp, "%d:%02d:%02d",
			row.joc->timp_jucat.ore,
			row.joc->timp_jucat.min,
			row.joc->timp_jucat.sec);

	drawText(row.x + row.textXOffset + TIMP_XOFFSET,
			y + row.textYOffset,
			temp,
			0);

	sprintf(temp, "%.2f EUR", row.joc->pret[EUR]);
	drawText(row.x + row.textXOffset + PRET_XOFFSET,
			y + row.textYOffset,
			temp,
			0);

	sprintf(temp, "%d", row.joc->nota);
	drawText(row.x + row.textXOffset + NOTA_XOFFSET,
			y + row.textYOffset,
			temp,
			0);

	glColor3f((row.joc->favorit == 1)? 1.0f: 0.0f, 0.0f, 0.0f);
	drawText(row.x + row.textXOffset + FAV_XOFFSET,
			y + row.textYOffset,
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

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
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
	glColor3f(0.9f, 0.9f, 1.0f);
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

	glBegin(GL_LINE);
		glVertex2i(NUME_XOFFSET, WINDOW_H);
		glVertex2i(NUME_XOFFSET, WINDOW_H - ROW_H);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	drawText(CLASAMENT_XOFFSET, WINDOW_H - ROW_H/1.5, "Nr.", 1);
	drawText(NUME_XOFFSET, WINDOW_H - ROW_H/1.5, "Nume", 1);
	drawText(TIMP_XOFFSET, WINDOW_H - ROW_H/1.5, "Timp", 1);
	drawText(PRET_XOFFSET, WINDOW_H - ROW_H/1.5, "Pret", 1);
	drawText(NOTA_XOFFSET - 10, WINDOW_H - ROW_H/1.5, "Nota", 1);
	drawText(FAV_XOFFSET - 10, WINDOW_H - ROW_H/1.5, "Fav", 1);


}
void drawFooter()
{
	if(count <= 0)
		return;

	glColor3f(0.9f, 0.9f, 1.0f);
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

	if(count > 0)
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		drawText(10, 10, table[index_selectat].joc->nume, 1);
		drawText(10, 40, table[index_selectat].joc->dezvoltator, 1);
	}
}
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

	//schimbare la proiectie
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(0, WINDOW_W, 0, WINDOW_H);

	//schimbare la modele
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutReshapeFunc(resize);
	glutTimerFunc(REFRESH_MS, timer, 0);
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
		exit(0);
	if(key == 'l'|| key == 'L')
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
	if((key == 'k' || key == 'K') && count > 0)
	{
		delete_at(&lista, index_selectat);

		free(table);
		count = get_num(lista);
		table = (JOCROW*)malloc(sizeof(JOCROW) * count);
		formeaza_table(table, lista);
		setToast("JOC STERS", 1000);
	}
	if(key == '1')
	{
		sortare(&lista, cmp_clasament);
		setToast("SORTAT (Clasament)", 500);
	}
	if(key == '2')
	{
		sortare(&lista, cmp_nume);
		setToast("SORTAT (Nume)", 500);
	}
	if(key == '3')
	{
		sortare(&lista, cmp_timpjucat);
		setToast("SORTAT (Timp)", 500);
	}
	if(key == '4')
	{
		sortare(&lista, cmp_pret);
		setToast("SORTAT (Pret)", 500);
	}
	if(key == '5')
	{
		sortare(&lista, cmp_nota);
		setToast("SORTAT (Nota)", 500);
	}
	if(key == '6')
	{
		sortare(&lista, cmp_favorit);
		setToast("SORTAT (Favorit)", 500);
	}
}
void special(int key, int x, int y)
{
	if(key == KEY_DOWN && scrollY > minscrollY)
	{
		scrollY -= SCROLL_SPEED;
	}
	if(key == KEY_UP && scrollY < maxscrollY)
	{
		scrollY += SCROLL_SPEED;
	}
	if(key == KEY_DOWN && index_selectat < count - 1)
		index_selectat++;
	if(key == KEY_UP && index_selectat > 0)
		index_selectat--;
}
void resize(int width, int height)
{
	if(width != WINDOW_W || height != WINDOW_H)
        glutReshapeWindow(WINDOW_W, WINDOW_H);
}
void timer(int time)
{
	glutPostRedisplay();
	glutTimerFunc(REFRESH_MS, timer, 0);
}

//FEREASTRA PENTRU ADAUGARE
//void drawCamp()
//{
//	int x = 0;
//	int y = 0;
//	int width = ADD_W;
//	int height = 50;
//
//	glColor3f(1.0f, 1.0f, 0.0f);
//	glBegin(GL_QUADS);
//		glVertex2i(x, y);
//		glVertex2i(x + width, y);
//		glVertex2i(x + width, y + height);
//		glVertex2i(x, y + height);
//	glEnd();
//}

void makeglut_add()
{
	free(input_joc);
	input_joc = (JOCVIDEO*)malloc(sizeof(JOCVIDEO));

	glutInitWindowSize(ADD_W, ADD_H);
	glutInitWindowPosition((SCREEN_W - ADD_W)/2, (SCREEN_H - ADD_H)/2);
	fereastra_add = glutCreateWindow("Adauga Joc");

	glutSetWindow(fereastra_add);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, ADD_W, 0, ADD_H);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.9f, 0.9f, 1.0f, 1.0f);

	glutDisplayFunc(display_add);
	glutKeyboardFunc(keyboard_add);
	glutReshapeFunc(resize_add);
	glutTimerFunc(REFRESH_MS, timer_add, 0);
}
void display_add()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	int i, offsetY;
	for(i = 0, offsetY = 25; i<NR_PARAMETRI; i++, offsetY += 25)
	{
		drawText(5, ADD_H - offsetY , NUMEPARAMETRI[i], 1);
		drawText(45 + 8*strlen(NUMEPARAMETRI[i]), ADD_H - offsetY, input_text[i], 1);
	}
	glFlush();
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

			for(int tag = 0; tag < NR_TAGURI; tag++)
				input_joc->taguri[tag] = 0;

			insert(&lista, *input_joc);

			count = get_num(lista);
		    free(table);
		    table = (JOCROW*)malloc(sizeof(JOCROW) * count);
		    formeaza_table(table, lista);

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
		while(input_text[index_parametru][i] != '\0' && i < 50)
			i++;

		input_text[index_parametru][i] = key;
		input_text[index_parametru][i+1] = '\0';
	}
}
void resize_add(int width, int height)
{
	if(width != ADD_W || height != ADD_H)
		glutReshapeWindow(ADD_W, ADD_H);
}
void timer_add(int time)
{
	glutPostRedisplay();
	glutTimerFunc(REFRESH_MS, timer_add, 0);
}



void formeaza_table(JOCROW* table, NODJOC* lista)
{
	if(lista == NULL || table == NULL)
		return;

	NODJOC* curent = lista;
	int i = 0, x = 0, y = WINDOW_H - ROW_H;

	scrollY = 0;
	maxscrollY = 0;
	minscrollY = y - ((count * ROW_H) + FOOTER_H);
	index_selectat = 0;

	while(curent != NULL)
	{
		y -= ROW_H;
		table[i].joc = &curent->joc;

		table[i].x = x;
		table[i].y = y;
		table[i].width = ROW_W;
		table[i].height = ROW_H;

		table[i].textXOffset = TEXT_XOFFSET;
		table[i].textYOffset = TEXT_YOFFSET;

		curent = curent->next;
		i++;
	}
}
