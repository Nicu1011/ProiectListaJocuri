#include "fereastra_glut.h"

NODJOC* lista = NULL;
JOCROW* table = NULL;
int count;
int selectedRow = -1;

int scrollY = 0;

char textToast[32];
int visibil;
int start;
int duration;


void drawText(int x, int y, const char* text)
{
	glRasterPos2i(x, y);
	for(int i=0; text[i] != '\0'; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		if(i > MAX_DISPLAYTEXT_LEN)
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
	drawText(b.x + (b.width/2) + b.textXOffset, b.y+(b.height/2)+b.textYOffset, b.text);
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
	glColor3f(0.0f, 0.0f, 1.0f);

	char n_str[25];
	int_to_text(row.joc->clasament, n_str);
	drawText(row.x + row.textXOffset + CLASAMENT_XOFFSET, y + row.textYOffset, n_str);

	drawText(row.x + row.textXOffset + NUME_XOFFSET, y + row.textYOffset, row.joc->nume);

	char timp_str[100];
	sprintf(timp_str, "%d:%02d:%02d", row.joc->timp_jucat.ore, row.joc->timp_jucat.min, row.joc->timp_jucat.sec);
	drawText(row.x + row.textXOffset + TIMP_XOFFSET, y + row.textYOffset, timp_str);

	char f_str[25];
	float_to_text(row.joc->pret[EUR], 2, f_str);
	drawText(row.x + row.textXOffset + PRET_XOFFSET, y + row.textYOffset, f_str);

	drawText(row.x + row.textXOffset + FAV_XOFFSET, y + row.textYOffset, (row.joc->favorit == 1)?"F":"x");
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
	drawText(x+width/3, y+height/2, textToast);
}
void setToast(const char* text, int timp)
{
	strcpy(textToast, text);
	visibil = 1;
	start = glutGet(GLUT_ELAPSED_TIME);
	duration = timp;
	glutPostRedisplay();
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
		setToast("LOADED", 1000);
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
	glutCreateWindow("Lista Jocuri Video");

	//schimbare la proiectie
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(0, WINDOW_W, 0, WINDOW_H);

	//schimbare la modele
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutTimerFunc(REFRESH_MS, timer, 0);

}
void formeaza_table(JOCROW* table, NODJOC* lista)
{
	if(lista == NULL || table == NULL)
		return;

//	int count = get_num(lista);

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

