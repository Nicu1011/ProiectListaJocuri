#include "fereastra_glut.h"

int fereastra_main = -1;
int fereastra_add = -1;

NODJOC* lista = NULL;
JOCROW* table = NULL;
int count;

int scrollY = 0;

//toast
char textToast[32];
int visibil;
int start;
int duration;

void drawText(int x, int y, const char* text, int ignore_max_len)
{
	glRasterPos2i(x, y);
	for(int i=0; text[i] != '\0'; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		if(ignore_max_len == 0)
			if(i > MAX_DISPLAYTEXT_LEN && text[i+1] != '\0')
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '.');
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '.');
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '.');
				return;
			}
	}
}
void drawButton(BUTTON b)
{
	glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2i(b.x, b.y);
		glVertex2i(b.x + b.width, b.y);
		glVertex2i(b.x + b.width, b.y + b.height);
		glVertex2i(b.x, b.y + b.height);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	drawText(b.x + (b.width/2) + b.textXOffset,
			b.y + (b.height/2) + b.textYOffset,
			b.text,
			1);
}
void drawTable(JOCROW* rows, int count)
{
	for(int i=0; i<count; i++)
		drawRow(rows[i]);
}
void drawRow(JOCROW row)
{
	int y = row.y - scrollY;
	int x = row.x;
	int width = row.width;
	int height = row.height;

	glColor3f(0.5f, 0.5f, 0.5f);

	if(row.selectat == 0)
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

	char n_str[25];
	int_to_text(row.joc->clasament, n_str);
	drawText(row.x + row.textXOffset + CLASAMENT_XOFFSET,
			y + row.textYOffset,
			n_str,
			0);

	drawText(row.x + row.textXOffset + NUME_XOFFSET,
			y + row.textYOffset,
			row.joc->nume
			,0);

	char timp_str[100];
	sprintf(timp_str, "%d:%02d:%02d",
			row.joc->timp_jucat.ore,
			row.joc->timp_jucat.min,
			row.joc->timp_jucat.sec);
	drawText(row.x + row.textXOffset + TIMP_XOFFSET,
			y + row.textYOffset,
			timp_str,
			0);

	char f_str[25];
	float_to_text(row.joc->pret[EUR], 2, f_str);
	strcat(f_str, "EUR");
	drawText(row.x + row.textXOffset + PRET_XOFFSET,
			y + row.textYOffset,
			f_str,
			0);

	if(row.joc->favorit == 1)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		drawText(row.x + row.textXOffset + FAV_XOFFSET,
				y + row.textYOffset,
				"F",
				0);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		drawText(row.x + row.textXOffset + FAV_XOFFSET,
				y + row.textYOffset,
				"x",
				0);
	}
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

	int x = 0;
	int y = 0;
	int width = TOAST_WIDTH;
	int height = TOAST_HEIGHT;

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glVertex2i(x, y);
		glVertex2i(x + width, y);
		glVertex2i(x + width, y + height);
		glVertex2i(x, y + height);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	drawText(x+width/3, y+height/2, textToast, 1);
}
void setToast(const char* text, int timp)
{
	strcpy(textToast, text);
	visibil = 1;
	start = glutGet(GLUT_ELAPSED_TIME);
	duration = timp;
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
	drawToast();

	glFlush();
}
void keyboard(unsigned char key, int x, int y)
{
	if(key == KEY_ESC)
		exit(0);
	if(key == KEY_LOAD)
	{
		free_lista(&lista);
		free(table);

		citeste_fisier(&lista, NULL);

		count = get_num(lista);

		table = (JOCROW*)malloc(sizeof(JOCROW) * count);
		formeaza_table(table, lista);
		setToast("LOADED lista_jocuri_default.txt", 1000);
	}
	if(key == KEY_SAVE)
	{
		creaza_fisier(lista, NULL);
		setToast("SAVED lista_jocuri_default.txt", 1000);
	}
	if(key == 't')
	{
		if(fereastra_add == -1)
			makeglut_add();
	}
	if(key == '1')
		sortare(&lista, cmp_nume);
	if(key == '2')
		sortare(&lista, cmp_fav);
	if(key == '3')
		sortare(&lista, cmp_nota);
	if(key == '4')
		sortare(&lista, cmp_clasament);
	if(key == '5')
		sortare(&lista, cmp_timpjucat);
	if(key == KEY_BACKUP)
	{
		creaza_backup(lista);
		setToast("BACKUP CREAT", 1000);
	}
}
void special(int key, int x, int y)
{
	if(key == KEY_UP)
	{
		scrollY -= SCROLL_SPEED;
	}
	if(key == KEY_DOWN)
	{
		scrollY += SCROLL_SPEED;
	}
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
void makeglut_add()
{
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
		drawText(15, ADD_H - offsetY , NUMEPARAMETRI[i], 1);

	glFlush();
}
void keyboard_add(unsigned char key, int x, int y)
{
	if(key == KEY_ESC)
	{
		glutDestroyWindow(fereastra_add);
		fereastra_add = -1;
		glutSetWindow(fereastra_main);
		return;
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
	int i = 0, x = 0, y = WINDOW_H;

	while(curent != NULL)
	{
		y -= ROW_HEIGHT;
		table[i].joc = &curent->joc;

		table[i].x = x;
		table[i].y = y;
		table[i].width = ROW_WIDTH;
		table[i].height = ROW_HEIGHT;

		table[i].textXOffset = 0;
		table[i].textYOffset = ROW_HEIGHT/2.5;

		table[i].selectat = 0;

		curent = curent->next;
		i++;
	}
}
