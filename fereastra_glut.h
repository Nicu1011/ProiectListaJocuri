#ifndef FEREASTRA_GLUT_H_
#define FEREASTRA_GLUT_H_


//WINDOWS
#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glut.h>
#include "fisier.h"

#define WINDOW_W 1200
#define WINDOW_H 480
#define SCREEN_W 1920
#define SCREEN_H 1080

#define KEY_ESC 27
#define KEY_UP GLUT_KEY_UP
#define KEY_DOWN GLUT_KEY_DOWN
#define KEY_SELECT
#define KEY_SAVE 's'
#define KEY_LOAD 'l'
#define KEY_BACKUP 'b'
#define KEY_FAV 'f'

#define SCROLL_SPEED ROW_HEIGHT/2
#define REFRESH_MS 30 //15...16 -> 60fps, 32...33 -> 30 fps

#define TOAST_WIDTH WINDOW_W
#define TOAST_HEIGHT 100

#define ROW_WIDTH WINDOW_W
#define ROW_HEIGHT WINDOW_H/16

#define CLASAMENT_XOFFSET 5
#define NUME_XOFFSET 65
#define TIMP_XOFFSET 350
#define PRET_XOFFSET 450
#define FAV_XOFFSET 600
#define MAX_DISPLAYTEXT_LEN 16

struct button{
	int x, y;
	int width, height;
	char* text;
	int textXOffset, textYOffset;
	int isPressed;
};
typedef struct button BUTTON;

struct jocrow{
	JOCVIDEO* joc;
	int x, y;
	int width, height;
	int textXOffset, textYOffset;
	int selectat;
};
typedef struct jocrow JOCROW;

void drawText(int x, int y, const char* text);
void drawButton(BUTTON b);
void drawTable(JOCROW rows[], int count);
void drawRow(JOCROW row);
void drawToast();
void setToast(const char* text, int timp);
void drawDetails();

void display();
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void resize(int width, int height);
void timer(int time);

void makeglut(int* argc, char** argv);

void formeaza_table(JOCROW* table, NODJOC* lista);

#endif /* FEREASTRA_GLUT_H_ */
